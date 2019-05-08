#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include <QObject>
#include"datastructure.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlDriver>
#include<QSqlRecord>
#include<QSqlError>
#include<QtDebug>
#include<QVector>
#include"user.h"
#include"word.h"
#include"server.h"


class DatabaseServer: public QObject
{
	Q_OBJECT
public:

#ifdef USE_NETWORK
	DatabaseServer(TcpClient &_tcpClient);
#else
	DatabaseServer(Server &_server, QObject *parent = nullptr);
#endif

	~DatabaseServer();
	static LoginState checkLoginState(const LoginPackage &loginPackage);
public:
	// to loginDialog.cpp
	void sendLoginState(LoginState state, qintptr socketDescriptor);

	// to registerDialog.cpp
	void sendRegisterState(RegisterState state, qintptr socketDescriptor);

	// to mainwindow.cpp
	void sendUserInfo(Player player, Questioner questioner, qintptr socketDescriptor); // this function is used to send info after login/register to MainWindow.

	// to ranklistWidget.cpp
	void sendRanklist(QVector<Player> players, QVector<Questioner> questioners,
					  SortMethod sortMethod, qintptr socketDescriptor);
	void sendDetailInfo(Player player, Questioner questioner, qintptr socketDescriptor); // this function is used to send info to RanklistWidget.

	// to gameWidget.cpp
	void sendWordList(QVector<Word> words, qintptr socketDescriptor);
	void sendEndGamePacket(EndGamePacket packet, qintptr socketDescriptor);

	// to questionWidget.cpp
	void sendAddedWords(int count, int expGained, qintptr socketDescriptor);

public:
	// from loginDialog.cpp
	void receiveLoginPackage(LoginPackage loginPackage, qintptr socketDescriptor);

	// from registerDialog.cpp
	void receiveRegisterPackage(RegisterPackage registerPackage, qintptr socketDescriptor);

	// from ranklistWidget.cpp
	void receiveRanklistRequest(SortMethod sortMethod, qintptr socketDescriptor);
	void receiveDetailInfoRequest(SortMethod sortMethod, int index, qintptr socketDescriptor);

	// from gameWidget.cpp
	void receiveWordListRequest(GameLevel level, qintptr socketDescriptor);
	void receiveEndGamePacket(EndGamePacket packet, qintptr socketDescriptor);

	// from questionWidget.cpp
	void receiveQuestionWordList(QVector<Word> words, QString questioner, qintptr socketDescriptor);

private:
	void initDataBase();
	static bool isLevelup(int curLevel, int &exp);


	QSqlDatabase db;
	QSqlQuery query;
	Server &server;
#ifdef USE_NETWORK
	TcpClient &tcpClient;
#endif
};

#endif // DATABASESERVER_H
