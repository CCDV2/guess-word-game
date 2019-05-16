#include "tcpserver.h"
#include<QTime>
#include<QStringList>
#include<algorithm>
using std::random_shuffle;

TcpServer::TcpServer(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent)
{
	Q_UNUSED(f)


	port = 8010;
	setWindowState(Qt::WindowMaximized);
	createWidget();
	createLayout();
	createConnection();
}

TcpServer::~TcpServer()
{
}

void TcpServer::sendMessage(qintptr socketDescriptor, QString message)
{
	server->sendMessageToClient(socketDescriptor, message);
}



void TcpServer::slotCreateServer()
{
	port = portLineEdit->text().toInt();
	server = new Server(*contentListWidget, this, port);
	DBServer = new DatabaseServer(*server, this);
	connect(server, &Server::sendUpdateServer, this, &TcpServer::receiveUpdateServer);
	connect(DBServer, &DatabaseServer::sendStartMatch, this, &TcpServer::startMatch);

	createButton->setEnabled(false);

}

void TcpServer::receiveUpdateServer(QString message, int length, qintptr socketDescriptor)
{
	writeLog(Server::getCurrentTimeStamp() + ' ' + QString::number(socketDescriptor) + ": " + message.left(length));
	QStringList messages = message.left(length).split('\n');
	for(auto toHandleMessage : messages)
	{
		if(toHandleMessage.isEmpty()) continue;
		messageQueue.push_back({toHandleMessage, socketDescriptor});
	}
	handleMessage();
}


void TcpServer::receiveDeleteRequest(MatchModule *module)
{
	writeLog(server->getCurrentTimeStamp() + " host: game end between " + module->getTwoPlayerName(" and "));
	for(int i = 0; i < matches.size(); ++i)
	{
		if(matches[i] == module)
		{
			matches[i]->deleteLater();
			matches.removeAt(i);
			return;
		}
	}
}

void TcpServer::handleMessage()
{
	static bool isBusy = false;
	if(isBusy) return;
	isBusy = true;
	while(!messageQueue.empty())
	{
		auto item = messageQueue.front();
		messageQueue.pop_front();
		QString message = item.message;
		qintptr socketDescriptor = item.socketDescriptor;

		QStringList function = message.split(',');
		bool ok;
		int functionCode = function[0].toInt(&ok);
		if(!ok)
		{
			writeLog(Server::getCurrentTimeStamp() + ' ' + "host: ERROR converting function code. Origin string is " + function[0]);
			continue;
		}
		switch(functionCode)
		{
		case LOGIN_FUNCTION:
			DBServer->receiveLoginPackage(LoginPackage::fromString(function[1]), socketDescriptor);
			break;
		case REGISTER_FUNCTION:
			DBServer->receiveRegisterPackage(RegisterPackage::fromString(function[1]), socketDescriptor);
			break;
		case USERINFO_FUNCTION:
			break;
		case RANKLIST_FUNCTION:
			DBServer->receiveRanklistRequest(static_cast<SortMethod>(function[1].toInt()), socketDescriptor);
			break;
		case DETAILINFO_FUNCTION:
			DBServer->receiveDetailInfoRequest(static_cast<SortMethod>(function[1].toInt()), function[2].toInt(), socketDescriptor);
			break;
		case WORDLIST_FUNCTION:
		{
			GameStatus status = static_cast<GameStatus>(function[2].toInt());
			int level = function[1].toInt();
			if(status == GAME_SINGLE)
			{
				DBServer->receiveWordListRequest(static_cast<GameLevel>(level), socketDescriptor);
			}
			else
			{
				assert(status == GAME_DUO);
				server->setUserStatus(socketDescriptor, STATUS_WAITING_MATCH);
				waitingMatchList[level].push_back(socketDescriptor);
				checkWaitingList();
			}
		}
			break;
		case UPDATE_EXP_FUNCTION:
		{
			EndGamePacket packet = EndGamePacket::fromString(function[1]);
			if(!sendToMatch(packet, socketDescriptor)) // belong to DUO game
			{
				// this belong to single game
				DBServer->receiveEndGamePacket(packet, socketDescriptor);
			}
		}
			break;
		case ADDWORD_FUNCTION:
		{
			Word word = Word::fromString(function[1]);
			QString questioner = function[2];
			if(word.getWord() == "__start")
			{
				addWordCache.words.clear();
				addWordCache.questioner = questioner;
			}
			else if(word.getWord() == "__end")
			{
				qDebug() << (addWordCache.questioner == questioner);
				DBServer->receiveQuestionWordList(addWordCache.words, addWordCache.questioner, socketDescriptor);
			}
			else if(word.getWord() == "__wait")
			{
				qDebug() << "too many words. waiting";
			}
			else
			{
				addWordCache.words.push_back(word);
			}
		}
			break;
		case ONLINE_USERS_FUNCTION:
		{
			DBServer->receiveOnlineUserRequest(socketDescriptor);
		}
			break;
		case ONLINE_USER_DETAIL_FUNCTION:
		{
			DBServer->receiveOnlineUserDetailInfoRequest(function[1], socketDescriptor);
		}
			break;
		case REQUEST_BATTLE_FUNCTION:
		{
			BattlePacket packet = BattlePacket::fromString(function[1]);
			waitingBattlePair[socketDescriptor] = server->getOnlineSocket(packet.enemy);
			DBServer->receiveBattleRequest(packet, socketDescriptor);
		}
			break;
		case RESPOND_BATTLE_FUNCTION:
		{
			BattlePacket packet = BattlePacket::fromString(function[1]);
			if(waitingBattlePair.remove(server->getOnlineSocket(packet.enemy)))
				DBServer->receiveBattelRespond(packet, socketDescriptor);
		}
			break;
		case GAME_CANCEL_FUNCTION:
		{
			switch(server->getUserStatus(socketDescriptor))
			{
			case STATUS_WAITING_MATCH:
				if(removeFromWaitingMacthList(socketDescriptor))
				{
					server->setUserStatus(socketDescriptor, STATUS_FREE);
				}
				else
				{
					server->writeLog(server->getCurrentTimeStamp() +
									 " host: ERROR cannot find queueing player " +
									 server->getOnlineUsername(socketDescriptor));
				}
				break;
			case STATUS_WAITING_BATTLE:
				DBServer->sendEnemyGameCancel(waitingBattlePair[socketDescriptor]);
				waitingBattlePair.remove(socketDescriptor);
				break;
			default:
				break;
			}
		}
			break;
		default:
			writeLog(Server::getCurrentTimeStamp() + ' ' + tr("host: unexpected function code %1").arg(functionCode));
			break;
		}
	}
	isBusy = false;
}

void TcpServer::checkWaitingList()
{
	qDebug() << "waiting";
	for(int i = 0; i < 4; ++i)
	{
		if(waitingMatchList[i].size() >= 2)
		{
			random_shuffle(waitingMatchList[i].begin(), waitingMatchList[i].end());
			while(waitingMatchList[i].size() >= 2)
			{
				qintptr p1 = waitingMatchList[i].back();
				waitingMatchList[i].pop_back();
				qintptr p2 = waitingMatchList[i].back();
				waitingMatchList[i].pop_back();
				startMatch(i, p1, p2, 5);
			}
		}
	}

}

void TcpServer::startMatch(int level, qintptr p1, qintptr p2, int wordNum)
{
	writeLog(server->getCurrentTimeStamp() +
			 " host: game start between " +
			 server->getOnlineUsername(p1) + " and "
			 + server->getOnlineUsername(p2));
	MatchModule *match = new MatchModule(p1, p2, static_cast<GameLevel>(level), wordNum, *DBServer, *server, this);
	connect(match, &MatchModule::requestDelete, this, &TcpServer::receiveDeleteRequest);
	matches.push_back(match);
	match->startMatch();
}

void TcpServer::writeLog(QString message)
{
	server->writeLog(message);
}

bool TcpServer::sendToMatch(EndGamePacket packet, qintptr socketDescriptor)
{
	for(auto match : matches)
	{
		if(match->contain(socketDescriptor))
		{
			match->setOnePacket(packet, socketDescriptor);
			return true;
		}
	}
	return false;
}

bool TcpServer::removeFromWaitingMacthList(qintptr socketDescriptor)
{
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < waitingMatchList[i].size(); ++j)
		{
			if(waitingMatchList[i][j] == socketDescriptor)
			{
				waitingMatchList[i].removeAt(j);
				return true;
			}
		}
	}
	return false;
}


void TcpServer::createWidget()
{
	setWindowTitle(tr("TCP Server"));
	contentListWidget = new QListWidget();
	portLabel = new QLabel(tr("端口："));
	portLineEdit = new QLineEdit();
	portLineEdit->setValidator(new QIntValidator(this));
	portLineEdit->setText(QString::number(port));
	createButton = new QPushButton(tr("创建服务器"));
}

void TcpServer::createLayout()
{
	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(contentListWidget, 0, 0, 1, 2);
	mainLayout->addWidget(portLabel, 1, 0);
	mainLayout->addWidget(portLineEdit, 1, 1);
	mainLayout->addWidget(createButton, 2, 0, 1, 2);
}

void TcpServer::createConnection()
{
	connect(createButton, &QPushButton::clicked, this, &TcpServer::slotCreateServer);
}

