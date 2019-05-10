#include "matchmodule.h"
using std::max;

MatchModule::MatchModule(qintptr pt1, qintptr pt2, GameLevel _level, int _wordNum, DatabaseServer &_DBserver, Server &_server ,QObject *parent):
	QObject(parent), level(_level), wordNum(_wordNum), DBserver(_DBserver), server(_server)
{
	arrivePacketCount = 0;
	playerPacket[0].playerName = server.getOnlineUsername(pt1);
	playerPacket[1].playerName = server.getOnlineUsername(pt2);
	socketDescriptor[0] = pt1;
	socketDescriptor[1] = pt2;
	connect(&waitForOneArrivedTimer, &QTimer::timeout, this, &MatchModule::noPacketArrived);
	connect(&waitForAnotherArrivedTimer, &QTimer::timeout, this, &MatchModule::onePacketArrived);
}

bool MatchModule::contain(qintptr _socketDescriptor)
{
	return ((socketDescriptor[0] == _socketDescriptor) || socketDescriptor[1] == _socketDescriptor);
}

void MatchModule::setOnePacket(EndGamePacket packet, qintptr _socketDescriptor)
{
	for(int i = 0; i < 2; ++i)
	{
		if(socketDescriptor[i] == _socketDescriptor)
		{
			playerPacket[i] = packet;
			break;
		}
	}
	++arrivePacketCount;
	if(arrivePacketCount == 1)
	{
		waitForOneArrivedTimer.stop();
		waitForAnotherArrivedTimer.start(WAIT_ANOTER_TIME);
	}
	else
	{
		waitForAnotherArrivedTimer.stop();
		dealTwoPackets();
		emit requestDelete(this);
	}
}

void MatchModule::startMatch()
{
	DBserver.receiveWordListRequest(level, socketDescriptor[0], socketDescriptor[1], wordNum);
	waitForOneArrivedTimer.start(SINGLE_WORD_TIME * 5);
}

void MatchModule::sendEndGamePacket(EndGamePacket packet, qintptr socketDescriptor)
{
	DBserver.receiveEndGamePacket(packet, socketDescriptor);
}

QString MatchModule::getTwoPlayerName(QString sep)
{
	return playerPacket[0].playerName + sep + playerPacket[1].playerName;
}

void MatchModule::noPacketArrived()
{
	server.setUserStatus(socketDescriptor[0], STATUS_FREE);
	server.setUserStatus(socketDescriptor[1], STATUS_FREE);
	emit requestDelete(this);
}

void MatchModule::onePacketArrived()
{
	int arrived = playerPacket[1].totalTime != 0;
	EndGamePacket &pwin = playerPacket[arrived], &plose = playerPacket[arrived ^ 1];


	double difficultyScale = DIFFICULTY_SCALE_TABLE[pwin.level];

	pwin.isWin = GAME_WIN;
	pwin.expGained = static_cast<int>(50 * (max(pwin.correctNum - pwin.wrongNum, 0))
										 * difficultyScale) * 2;
	plose.isWin = GAME_LOSE;
	plose.expGained = -200;

	sendEndGamePacket(pwin, socketDescriptor[arrived]);
	sendEndGamePacket(plose, socketDescriptor[arrived ^ 1]);

	emit requestDelete(this);
}

void MatchModule::dealTwoPackets()
{
	assert(playerPacket[0].isWin == GAME_DUO);
	assert(playerPacket[1].isWin == GAME_DUO);
	EndGamePacket &p0 = playerPacket[0], &p1 = playerPacket[1];

	double difficultyScale = DIFFICULTY_SCALE_TABLE[p0.level];
	int p0Exp = static_cast<int>(50 * (max(p0.correctNum - p0.wrongNum, 0))
									 * difficultyScale);
	int p1Exp = static_cast<int>(50 * (max(p1.correctNum - p1.wrongNum, 0))
								 * difficultyScale);

	p0.enemyCorrectNum = p1.correctNum;
	p0.enemyTotalTime = p1.totalTime;

	p1.enemyCorrectNum = p0.correctNum;
	p1.enemyTotalTime = p0.totalTime;

	if(p0.correctNum != p1.correctNum)
	{
		if(p0.correctNum > p1.correctNum)
		{
			p0.isWin = GAME_WIN;
			p0Exp = p0Exp * 2;
			p0.expGained = p0Exp;


			p1.isWin = GAME_LOSE;
			p1Exp = -p1Exp / 2;
			p1.expGained = p1Exp;
		}
		else
		{
			p0.isWin = GAME_LOSE;
			p0Exp = -p0Exp / 2;
			p0.expGained = p0Exp;

			p1.isWin = GAME_WIN;
			p1Exp = p1Exp * 2;
			p1.expGained = p1Exp;
		}
	}
	else if(p0.totalTime / 100 != p1.totalTime / 100)
	{
		if(p0.totalTime / 100 > p1.totalTime / 100)
		{
			p0.isWin = GAME_LOSE;
			p0Exp = -p0Exp / 2;
			p0.expGained = p0Exp;

			p1.isWin = GAME_WIN;
			p1Exp = p1Exp * 2;
			p1.expGained = p1Exp;
		}
		else
		{
			p0.isWin = GAME_WIN;
			p0Exp = p0Exp * 2;
			p0.expGained = p0Exp;


			p1.isWin = GAME_LOSE;
			p1Exp = -p1Exp / 2;
			p1.expGained = p1Exp;
		}
	}
	else
	{
		p0.isWin = GAME_TIE;
		p0Exp = p0Exp * 3 / 2;
		p0.expGained = p0Exp;

		p1.isWin = GAME_TIE;
		p1Exp = p1Exp * 3 / 2;
		p1.expGained = p1Exp;
	}

	sendEndGamePacket(p0, socketDescriptor[0]);
	sendEndGamePacket(p1, socketDescriptor[1]);
	emit requestDelete(this);
}

