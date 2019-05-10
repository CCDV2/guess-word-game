#ifndef MATCHMODULE_H
#define MATCHMODULE_H

#include <QObject>
#include<QTimer>
#include"datastructure.h"
#include"databaseserver.h"

const int SINGLE_WORD_TIME = 6000;
const int WAIT_ANOTER_TIME = 20000;

class MatchModule: public QObject
{
	Q_OBJECT
public:
	MatchModule(qintptr pt1, qintptr pt2, GameLevel _level, int _wordNum, DatabaseServer &_DBserver, Server &_server, QObject *parent = nullptr);

	bool contain(qintptr _socketDescriptor);
	void setOnePacket(EndGamePacket packet, qintptr _socketDescriptor);
	void startMatch();
	void sendEndGamePacket(EndGamePacket packet, qintptr socketDescriptor);
	QString getTwoPlayerName(QString sep = tr(" "));
signals:
	void requestDelete(MatchModule *matchModule);

private slots:
	void noPacketArrived();
	void onePacketArrived();

private:
	void dealTwoPackets();

	GameLevel level;
	int wordNum;
	int arrivePacketCount;
	EndGamePacket playerPacket[2];
	qintptr socketDescriptor[2];
	QTimer waitForOneArrivedTimer, waitForAnotherArrivedTimer;
	DatabaseServer &DBserver;
	Server &server;
};

#endif // MATCHMODULE_H
