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

void DatabaseServer::receiveRanklistRequest(SortMethod sortMethod)
{
	QVector<Player> players;
	QVector<Questioner> questioners;
	switch(sortMethod)
	{
	// initial state, should not be received
	case NULL_SORT:
		qDebug() << "error receiving NULL_SORT";
		break;
	// player part
	case PLAYER_LEVEL_DESC:
		if(query.exec(tr("select * from user order by playerlevel desc, playerexp desc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for player ranklist failed: level desc";
		break;
	case PLAYER_LEVEL_ASC:
		if(query.exec(tr("select * from user order by playerlevel asc, playerexp asc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for player ranklist failed: level asc";
		break;
	case PLAYER_NAME_DESC:
		if(query.exec(tr("select * from user order by username desc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for player ranklist failed: username desc";
		break;
	case PLAYER_NAME_ASC:
		if(query.exec(tr("select * from user order by username asc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for player ranklist failed: username asc";
		break;
	case PLAYER_NUM_DESC:
		if(query.exec(tr("select * from user order by playernum desc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for player ranklist failed: playernum desc";
		break;
	case PLAYER_NUM_ASC:
		if(query.exec(tr("select * from user order by playernum asc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for player ranklist failed: playernum asc";
		break;
	// questioner part
	case QUESTIONER_LEVEL_DESC:
		if(query.exec(tr("select * from user order by questionerlevel desc, questionerexp desc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for questioner ranklist failed: level desc";
		break;
	case QUESTIONER_LEVEL_ASC:
		if(query.exec(tr("select * from user order by questionerlevel asc, questionerexp asc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for questioner ranklist failed: level asc";
		break;
	case QUESTIONER_NAME_DESC:
		if(query.exec(tr("select * from user order by username desc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for questioner ranklist failed: username desc";
		break;
	case QUESTIONER_NAME_ASC:
		if(query.exec(tr("select * from user order by username asc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for questioner ranklist failed: username asc";
		break;
	case QUESTIONER_NUM_DESC:
		if(query.exec(tr("select * from user order by questionernum desc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for qeustioner ranklist failed: questionernum desc";
		break;
	case QUESTIONER_NUM_ASC:
		if(query.exec(tr("select * from user order by questionernum asc")))
		{
			while(query.next())
			{
				players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
				questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			emit sendRanklist(players, questioners, sortMethod);
		}
		else
			qDebug() << query.lastError() << "query for qeustioner ranklist failed: questionernum asc";
		break;
	}
}

void DatabaseServer::receiveDetailInfoRequest(SortMethod sortMethod, int index)
{
	switch(sortMethod)
	{
	case NULL_SORT:
		qDebug() << "error: receive NULL_SORT";
		break;
	case PLAYER_LEVEL_DESC:
		if(query.exec(tr("select * from user order by playerlevel desc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for player level";
		break;
	case PLAYER_LEVEL_ASC:
		if(query.exec(tr("select * from user order by playerlevel asc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for player level";
		break;
	case PLAYER_NAME_DESC:
		if(query.exec(tr("select * from user order by username desc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for username";
		break;
	case PLAYER_NAME_ASC:
		if(query.exec(tr("select * from user order by username asc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for username";
		break;
	case PLAYER_NUM_DESC:
		if(query.exec(tr("select * from user order by playernum desc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for player num";
		break;
	case PLAYER_NUM_ASC:
		if(query.exec(tr("select * from user order by playernum asc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for player num";
		break;
	case QUESTIONER_LEVEL_DESC:
		if(query.exec(tr("select * from user order by questionerlevel desc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for questioner level";
		break;
	case QUESTIONER_LEVEL_ASC:
		if(query.exec(tr("select * from user order by questionerlevel asc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for questioner level";
		break;
	case QUESTIONER_NAME_DESC:
		if(query.exec(tr("select * from user order by username desc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for username";
		break;
	case QUESTIONER_NAME_ASC:
		if(query.exec(tr("select * from user order by username asc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for username";
		break;
	case QUESTIONER_NUM_DESC:
		if(query.exec(tr("select * from user order by questionernum desc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for questioner num";
		break;
	case QUESTIONER_NUM_ASC:
		if(query.exec(tr("select * from user order by questionernum asc limit %1, 1").arg(index)))
		{
			if(query.next())
			{
				emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
			}
			else
				qDebug() << query.lastError() << "no detail user info... error";
		}
		else
			qDebug() << query.lastError() << "get detail failed for questioner num";
		break;
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
