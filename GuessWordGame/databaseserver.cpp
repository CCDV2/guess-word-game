#include "databaseserver.h"
#include<QTime>

DatabaseServer::DatabaseServer()
{
	qsrand(static_cast<unsigned int>(QTime(0, 0, 0).secsTo(QTime::currentTime())));
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

void DatabaseServer::receiveWordListRequest(GameLevel level)
{
	QVector<Word> words;
	QString levelRange;
	switch(level)
	{
	case EASY:
		levelRange = tr("level between 1 and 3");
		break;
	case NORMAL:
		levelRange = tr("level between 4 and 6");
		break;
	case HARD:
		levelRange = tr("level between 7 and 9");
		break;
	case EXPERT:
		levelRange = tr("level between 8 and 10");
		break;
	}
	if(query.exec(tr("select * from wordlist where %1 order by random() limit 5").arg(levelRange)))
	{
		while(query.next())
		{
			words.push_back(Word(query.value(0).toString(), query.value(1).toInt()));
		}
		qDebug() << "Receive " << words.size() << "words";
		emit sendWordList(words);
	}
	else
		qDebug() << query.lastError() << "get wordlist failed";
}

void DatabaseServer::receiveUpdatedExp(QString playerName, int expGained, int problemNum)
{
	if(query.exec(tr("select playerlevel, playerexp, playernum from user where username='%1'").arg(playerName)))
	{
		if(query.next())
		{
			// calculating update
			qDebug() << "update " << playerName;
			int preLevel = query.value(0).toInt();
			int preExp = query.value(1).toInt();
			int preNum = query.value(2).toInt();
			qDebug() << "preLevel: " << preLevel << " preExp: " << preExp << " preNum: " << preNum;
			int curExp = preExp + expGained;
			int curNum = preNum + problemNum;
			int curLevel = preLevel;
			bool isLvup;
			// it's an assignment !!
			while((isLvup = isLevelup(preLevel, curExp)))
			{
				++curLevel;
			}
			qDebug() << "curExp: " << curExp << " curNum: " << curNum << " curLevel: " << curLevel;

			// update database
			if(query.exec(tr("update user set playerlevel=%1, playerexp=%2, playernum=%3 where username='%4'")
					   .arg(curLevel).arg(curExp).arg(curNum).arg(playerName)))
			{
				qDebug() << "updatelevel success";

				// after update the database, send it to the mainwindow
				if(query.exec(tr("select * from user where username='%1'").arg(playerName)))
				{
					if(query.next())
					{
						emit sendUserInfo(Player(playerName, query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
										  Questioner(playerName, query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
					}
					else
						qDebug() << "unfound username in update exp";
				}
				else
					qDebug() << query.lastError() << "query for login package failed";
			}
			else
				qDebug() << query.lastError() << "update userlevel failed";
		}
		else
			qDebug() << "update username not found error";
	}
	else
		qDebug() << query.lastError() << "update exp failed";
}



void DatabaseServer::receiveQuestionWordList(QVector<Word> words, QString questioner)
{
	int cnt = 0;
	double expGained = 0.0;
	// insert into wordlist
	for(auto word: words)
	{
		if(query.exec(tr("select * from wordlist where word='%1'").arg(word.getWord())))
		{
			if(!query.next())
			{
				query.prepare(tr("insert into wordlist values(?,?)"));
				query.bindValue(0, word.getWord());
				query.bindValue(1, word.getLevel());
				if(query.exec())
				{
					++cnt;
					expGained += LEVEL_SCALE_TABLE[word.getLevel()];
				}
				else
					qDebug() << query.lastError() << "question word insert failed";
			}
		}
		else
			qDebug() << query.lastError() << "qeustion wordlist search failed";
	}
	double randomBonus = static_cast<double>(qrand() % 21) / 100.0 + 1.00;
	expGained *= randomBonus * 50.0;
	int expGained_int = static_cast<int>(expGained);
	if(query.exec(tr("select questionerlevel, questionerexp, questionernum from user where username='%1'").arg(questioner)))
	{
		if(query.next())
		{
			// calculating update
			qDebug() << "update questioner" << questioner;
			int preLevel = query.value(0).toInt();
			int preExp = query.value(1).toInt();
			int preNum = query.value(2).toInt();
			qDebug() << "preLevel: " << preLevel << " preExp: " << preExp << " preNum: " << preNum;
			int curExp = preExp + expGained_int;
			int curNum = preNum + cnt;
			int curLevel = preLevel;
			bool isLvup;
			// it's an assignment!!
			while((isLvup = isLevelup(preLevel, curExp)))
			{
				++curLevel;
			}
			qDebug() << "curExp: " << curExp << " curNum: " << curNum << " curLevel: " << curLevel;

			// update database
			if(query.exec(tr("update user set questionerlevel=%1, questionerexp=%2, questionernum=%3 where username='%4'")
					   .arg(curLevel).arg(curExp).arg(curNum).arg(questioner)))
			{
				qDebug() << "updatelevel success";

				// after update the database, send it to the mainwindow
				if(query.exec(tr("select * from user where username='%1'").arg(questioner)))
				{
					if(query.next())
					{
						emit sendUserInfo(Player(questioner, query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
										  Questioner(questioner, query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
					}
					else
						qDebug() << "unfound username in update exp";
				}
				else
					qDebug() << query.lastError() << "query for login package failed";
			}
			else
				qDebug() << query.lastError() << "update userlevel failed";
		}
		else
			qDebug() << "update username not found error";
	}
	else
		qDebug() << query.lastError() << "update exp failed";

	emit sendAddedWords(cnt, expGained_int);
}

void DatabaseServer::initDataBase()
{
	// init user
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
		qDebug() << query.lastError() << "init user database failed";
	// init wordlist
	if(query.exec(tr("select * from wordlist where word='%1'").arg(tr("apple"))))
	{
		if(!query.next())
		{
			query.prepare(tr("insert into wordlist values(?,?)"));
			for(auto word : initWords)
			{
				query.bindValue(0, word.getWord());
				query.bindValue(1, word.getLevel());
				if(query.exec())
				{
					qDebug() << "init insert into wordlist success!";
				}
				else
					qDebug() << query.lastError() << "insert into init wordlist failed";
			}
		}
		else
			qDebug() << "wordlist already existed";
	}
	else
		qDebug() << query.lastError() << "init wordlist database failed";

}

bool DatabaseServer::isLevelup(int curLevel, int &exp)
{
	int maxExp = getLevelMaxExp(curLevel);
//	qDebug() << "curlevel: " << curLevel << " curExp: " << exp;
	if(exp >= maxExp)
	{
		exp -= maxExp;
		return true;
	}
	else return false;
}
