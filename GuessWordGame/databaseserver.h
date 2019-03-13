#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include <QObject>
#include"datastructure.h"
#include"user.h"
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
	void sendLoginState(LoginState state);
	void sendRegisterState(RegisterState state);
	void sendUserInfo(Player player, Questioner questioner); // this function is used to send info after login/register to MainWindow.
	void sendRanklist(QVector<Player> players, QVector<Questioner> questioners, SortMethod sortMethod);
	void sendDetailInfo(Player player, Questioner questioner); // this function is used to send info to RanklistWidget.
public slots:
	void receiveLoginPackage(LoginPackage loginPackage);
	void receiveRegisterPackage(RegisterPackage registerPackage);
	void receiveRanklistRequest(SortMethod sortMethod);
	void receiveDetailInfoRequest(SortMethod sortMethod, int index);
private:
	void initDataBase();

	QSqlDatabase db;
	QSqlQuery query;

};

#endif // DATABASESERVER_H
