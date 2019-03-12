#include "databaseserver.h"

DatabaseServer::DatabaseServer()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("qtDB.db");
	db.open();

	query = QSqlQuery(db);

	bool success = query.exec("create table if not exists user\
							  (username varchar primary key,\
							   password varchar,\
							   playerlevel int,\
							   playerexp int,\
							   playernum int,\
							   questionerlevel int,\
							   questionerexp int,\
							   questionernum int)");
	if(success)
		qDebug() << "create uesr table success";
	else
		qDebug() << "create user table failed";
	success = query.exec("create table if not exists wordlist\
						 (word varchar primary key,\
						  level int)");
	if(success)
		qDebug() << "create wordlist table success";
	else
		qDebug() << "create wordlist table failed";
	initDataBase();
}

DatabaseServer::~DatabaseServer()
{
	db.close();
}

LoginState DatabaseServer::checkLoginState(const LoginPackage &loginPackage)
{
	if(loginPackage.userName == QObject::tr("CCDV2"))
	{
		return LOGIN_SUCCESS;
	}
	else
	{
		return UNFOUND_USERNAME;
	}
}

void DatabaseServer::receiveLoginPackage(LoginPackage loginPackage)
{
	const QString &userName = loginPackage.userName;
	const QString &password = loginPackage.passWord;
	if(query.exec(tr("select * from user where username='%1'").arg(userName)))
	{
		if(query.next())
		{
			QString pwdInDB = query.value(1).toString();
			if(pwdInDB == password)
			{
				emit sendLoginState(LOGIN_SUCCESS);
				emit sendUserInfo(Player(userName, query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(userName, query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				emit sendLoginState(WRONG_PASSWORD);
		}
		else
		{
			emit sendLoginState(UNFOUND_USERNAME);
		}
	}
	else
	{
		qDebug() << query.lastError() << "query for login package failed";
	}
}

void DatabaseServer::receiveRegisterPackage(RegisterPackage registerPackage)
{
	const QString &userName = registerPackage.userName;
	const QString &password = registerPackage.passWord;
	if(query.exec(tr("select * from user where username='%1'").arg(userName)))
	{
		if(query.next())
		{
			emit sendRegisterState(USER_EXISTED);
		}
		else
		{
			query.prepare((tr("insert into user values(?,?,?,?,?,?,?,?)")));
			query.bindValue(0, userName);
			query.bindValue(1, password);
			query.bindValue(2, 1);
			query.bindValue(3, 0);
			query.bindValue(4, 0);
			query.bindValue(5, 1);
			query.bindValue(6, 0);
			query.bindValue(7, 0);
			if(query.exec())
			{
				emit sendRegisterState(REGISTER_SUCCESS);
				emit sendUserInfo(Player(userName, 1, 0, 0), Questioner(userName, 1, 0, 0));
			}
			else
				qDebug() << query.lastError() << "query for register package failed";
		}
	}
	else
	{
		qDebug() << query.lastError() << "query for register package failed";
	}
}

void DatabaseServer::receiveRanklistRequest(bool isPlayer)
{
	if(isPlayer)
	{
		qDebug() << "search for player ranklist";
//		emit sendRanklist(NULL, NULL, isPlayer);
	}
	else
	{
		qDebug() << "search for questioner ranklist";
//		emit sendRanklist(NULL, NULL, isPlayer);
	}
}

void DatabaseServer::initDataBase()
{
	if(query.exec(tr("select * from user where username='%1'").arg(tr("CCDV2"))))
	{
		if(!query.next())
		{
			query.prepare(tr("insert into user values(?,?,?,?,?,?,?,?)"));
			query.bindValue(0, tr("CCDV2"));
			query.bindValue(1, tr("123456"));
			query.bindValue(2, 99);
			query.bindValue(3, 99);
			query.bindValue(4, 99);
			query.bindValue(5, 99);
			query.bindValue(6, 99);
			query.bindValue(7, 99);

			if(query.exec())
			{
				qDebug() << "init insert success!";
			}
			else
				qDebug() << query.lastError() << "init insert failed";
		}
	}
	else
		qDebug() << query.lastError() << "init database failed";
}
