#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include <QObject>
#include"datastructure.h"
#include"user.h"
#include"word.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlDriver>
#include<QSqlRecord>
#include<QSqlError>
#include<QtDebug>
#include<QVector>
#include"tcpclient.h"

class DatabaseServer: public QObject
{
	Q_OBJECT
public:

#ifdef USE_NETWORK
	DatabaseServer(TcpClient &_tcpClient);
#else
	DatabaseServer();
#endif

	~DatabaseServer();
	static LoginState checkLoginState(const LoginPackage &loginPackage);
signals:
	// to loginDialog.cpp
	void sendLoginState(LoginState state);

	// to registerDialog.cpp
	void sendRegisterState(RegisterState state);

	// to mainwindow.cpp
	void sendUserInfo(Player player, Questioner questioner); // this function is used to send info after login/register to MainWindow.

	// to ranklistWidget.cpp
	void sendRanklist(QVector<Player> players, QVector<Questioner> questioners, SortMethod sortMethod);	
	void sendDetailInfo(Player player, Questioner questioner); // this function is used to send info to RanklistWidget.

	// to gameWidget.cpp
	void sendWordList(QVector<Word> words);
	void sendShowEndGameDialog(EndGamePacket packet);

	// to questionWidget.cpp
	void sendAddedWords(int count, int expGained);
#ifdef USE_NETWORK
	// to OnlinUserWidget.cpp
	void sendOnlineUsers(QVector<QString> users);
	void sendOnlineUserDetail(Player player, Questioner questioner);

	// to mainWindow
	void sendBattleRequest(BattlePacket packet);
	void sendBattleRespond(BattlePacket packet);
	void sendWaitSignal();
	void sendEnemyGameCancel();
#endif


public slots:
	// from loginDialog.cpp
	void receiveLoginPackage(LoginPackage loginPackage);

	// from registerDialog.cpp
	void receiveRegisterPackage(RegisterPackage registerPackage);

	// from ranklistWidget.cpp
	void receiveRanklistRequest(SortMethod sortMethod);
	void receiveDetailInfoRequest(SortMethod sortMethod, int index);

	// from gameWidget.cpp
	void receiveWordListRequest(GameLevel level, GameStatus status);
	void receiveEndGamePacket(EndGamePacket packet);

	// from questionWidget.cpp
	void receiveQuestionWordList(QVector<Word> words, QString questioner);

#ifdef USE_NETWORK
	// from TcpClient.cpp
	void handleMessages();

	// from OnlineUserWidget.cpp
	void receiveOnlineUserRequest();
	void receiveOnlineUserDetailInfoRequest(QString user);

	// from DetailedUserInfoDialog.cpp
	void receiveBattleRequest(BattlePacket packet);
	void receiveBattelRespond(BattlePacket packet); // from mainwindow

	void receiveGameCancel();
#endif

private:
	void initDataBase();
	static bool isLevelup(int curLevel, int &exp);


	QSqlDatabase db;
	QSqlQuery query;
#ifdef USE_NETWORK
	TcpClient &tcpClient;
	struct
	{
		QVector<Player> players;
		QVector<Questioner> questioners;
		SortMethod method;
	} ranklistCache;
	QVector<Word> wordsCache;

#endif
};

#endif // DATABASESERVER_H
