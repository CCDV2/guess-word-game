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
	void sendUserInfo(Player player, Questioner questioner);
public slots:
	void receiveLoginPackage(LoginPackage loginPackage);
	void receiveRegisterPackage(RegisterPackage registerPackage);
private:
	void initDataBase();

	QSqlDatabase db;
	QSqlQuery query;

};

#endif // DATABASESERVER_H