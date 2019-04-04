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

class DatabaseServer: public QObject
{
	Q_OBJECT
public:
	DatabaseServer();
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

	// to questionWidget.cpp
	void sendAddedWords(int count, int expGained);

public slots:
	// from loginDialog.cpp
	void receiveLoginPackage(LoginPackage loginPackage);

	// from registerDialog.cpp
	void receiveRegisterPackage(RegisterPackage registerPackage);

	// from ranklistWidget.cpp
	void receiveRanklistRequest(SortMethod sortMethod);
	void receiveDetailInfoRequest(SortMethod sortMethod, int index);

	// from gameWidget.cpp
	void receiveWordListRequest(GameLevel level);
	void receiveUpdatedExp(QString playerName, int expGained, int problemNum);

	// from questionWidget.cpp
	void receiveQuestionWordList(QVector<Word> words, QString questioner);

private:
	void initDataBase();
	static bool isLevelup(int curLevel, int &exp);



	QSqlDatabase db;
	QSqlQuery query;

};

#endif // DATABASESERVER_H
