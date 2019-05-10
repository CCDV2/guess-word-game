#include "databaseserver.h"
#include<QTime>
#include<QThread>
#include<QApplication>
using std::max;

#ifndef USE_NETWORK
DatabaseServer::DatabaseServer(Server &_server, QObject *parent):
	QObject(parent), server(_server)
#else
DatabaseServer::DatabaseServer(TcpClient &_tcpClient):
	tcpClient(_tcpClient)
#endif
{
#ifndef USE_NETWORK
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
#endif
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

void DatabaseServer::sendLoginState(LoginState state, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor, QString::number(LOGIN_FUNCTION) + ',' + QString::number(state));
}

void DatabaseServer::sendRegisterState(RegisterState state, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor, QString::number(REGISTER_FUNCTION) + ',' + QString::number(state));
}

void DatabaseServer::sendUserInfo(Player player, Questioner questioner, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(USERINFO_FUNCTION) +
							   ',' + player.toString() +
							   ',' + questioner.toString());
}

void DatabaseServer::sendRanklist(QVector<Player> players, QVector<Questioner> questioners, SortMethod sortMethod, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(RANKLIST_FUNCTION) + ',' +
							   Player::specialPlayer(sortMethod) + ',' +
							   Questioner::specialQuestioner(sortMethod)
							   );
	for(int i = 0; i < players.size(); ++i)
	{
		server.sendMessageToClient(socketDescriptor,
								   QString::number(RANKLIST_FUNCTION) + ',' +
								   players[i].toString() + ',' +
								   questioners[i].toString());
	}
	server.sendMessageToClient(socketDescriptor,
							   QString::number(RANKLIST_FUNCTION) + ',' +
							   Player::specialPlayer(sortMethod, false) + ',' +
							   Questioner::specialQuestioner(sortMethod, false));
}

void DatabaseServer::sendDetailInfo(Player player, Questioner questioner, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(DETAILINFO_FUNCTION) + ',' +
							   player.toString() + ',' +
							   questioner.toString());
}

void DatabaseServer::sendWordList(QVector<Word> words, qintptr socketDescriptor)
{
	server.setUserStatus(socketDescriptor, STATUS_PLAYING);
	server.sendMessageToClient(socketDescriptor,
							   QString::number(WORDLIST_FUNCTION) + ',' +
							   Word::specialWord());
	for(auto word : words)
	{
		server.sendMessageToClient(socketDescriptor,
								   QString::number(WORDLIST_FUNCTION) + ',' +
								   word.toString());
	}
	server.sendMessageToClient(socketDescriptor,
							   QString::number(WORDLIST_FUNCTION) + ',' +
							   Word::specialWord(false));
}

void DatabaseServer::sendEndGamePacket(EndGamePacket packet, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(UPDATE_EXP_FUNCTION) + ',' +
							   packet.toString());
}

void DatabaseServer::sendAddedWords(int count, int expGained, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(ADDWORD_FUNCTION) + ',' +
							   QString::number(count) + ',' +
							   QString::number(expGained));
}

void DatabaseServer::sendOnlineUsers(QVector<QString> users, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(ONLINE_USERS_FUNCTION) + ',' +
							   users.toList().join('.'));
}

void DatabaseServer::sendOnlineUserDetail(Player player, Questioner questioner, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(ONLINE_USER_DETAIL_FUNCTION) + ',' +
							   player.toString() + ',' +
							   questioner.toString());
}

void DatabaseServer::sendBattleRequest(BattlePacket packet, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(REQUEST_BATTLE_FUNCTION) + ',' +
							   packet.toString());
}

void DatabaseServer::sendBattleRespond(BattlePacket packet, qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor,
							   QString::number(RESPOND_BATTLE_FUNCTION) + ',' +
							   packet.toString());
}

void DatabaseServer::sendWaitingMessage(qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor, QString::number(WAIT_FUNCTION));
}

void DatabaseServer::sendEnemyGameCancel(qintptr socketDescriptor)
{
	server.sendMessageToClient(socketDescriptor, QString::number(GAME_CANCEL_FUNCTION));
}



void DatabaseServer::receiveLoginPackage(LoginPackage loginPackage, qintptr socketDescriptor)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(QString::number(LOGIN_FUNCTION) + ',' + loginPackage.toString());
#else


	const QString &userName = loginPackage.userName;
	const QString &password = loginPackage.passWord;
	if(query.exec(tr("select * from user where username='%1'").arg(userName)))
	{
		if(query.next())
		{
			QString pwdInDB = query.value(1).toString();
			if(pwdInDB == password)
			{
				server.addOnlineUser(socketDescriptor, userName);
				sendLoginState(LOGIN_SUCCESS, socketDescriptor);
				sendUserInfo(Player(userName, query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
							  Questioner(userName, query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()),
							 socketDescriptor);
			}
			else
				sendLoginState(WRONG_PASSWORD, socketDescriptor);
		}
		else
		{
			sendLoginState(UNFOUND_USERNAME, socketDescriptor);
		}
	}
	else
	{
		qDebug() << query.lastError() << "query for login package failed";
	}
#endif
}

void DatabaseServer::receiveRegisterPackage(RegisterPackage registerPackage, qintptr socketDescriptor)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(QString::number(REGISTER_FUNCTION) + ',' + registerPackage.toString());
#else
	const QString &userName = registerPackage.userName;
	const QString &password = registerPackage.passWord;
	if(query.exec(tr("select * from user where username='%1'").arg(userName)))
	{
		if(query.next())
		{
			sendRegisterState(USER_EXISTED, socketDescriptor);
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
				server.addOnlineUser(socketDescriptor, userName);
				sendRegisterState(REGISTER_SUCCESS, socketDescriptor);
				sendUserInfo(Player(userName, 1, 0, 0), Questioner(userName, 1, 0, 0), socketDescriptor);
			}
			else
				qDebug() << query.lastError() << "query for register package failed";
		}
	}
	else
	{
		qDebug() << query.lastError() << "query for register package failed";
	}
#endif
}

void DatabaseServer::receiveRanklistRequest(SortMethod sortMethod, qintptr socketDescriptor)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(QString::number(RANKLIST_FUNCTION) + ',' + QString::number(sortMethod));
#else
	QVector<Player> players;
	QVector<Questioner> questioners;
	QString base = tr("select * from user order by ");
	QString method;
	switch(sortMethod)
	{
	// initial state, should not be received
	case NULL_SORT:
		qDebug() << "error receiving NULL_SORT";
		break;
	// player part
	case PLAYER_LEVEL_DESC:
		method = tr("playerlevel desc, playerexp desc");
		break;
	case PLAYER_LEVEL_ASC:
		method = tr("playerlevel asc, playerexp asc");
		break;
	case PLAYER_NAME_DESC:
		method = tr("username desc");
		break;
	case PLAYER_NAME_ASC:
		method = tr("username asc");
		break;
	case PLAYER_NUM_DESC:
		method = tr("playernum desc");
		break;
	case PLAYER_NUM_ASC:
		method = tr("playernum asc");
		break;
	// questioner part
	case QUESTIONER_LEVEL_DESC:
		method = tr("questionerlevel desc, questionerexp desc");
		break;
	case QUESTIONER_LEVEL_ASC:
		method = tr("questionerlevel asc, questionerexp asc");
		break;
	case QUESTIONER_NAME_DESC:
		method = tr("username desc");
		break;
	case QUESTIONER_NAME_ASC:
		method = tr("username asc");
		break;
	case QUESTIONER_NUM_DESC:
		method = tr("questionernum desc");
		break;
	case QUESTIONER_NUM_ASC:
		method = tr("questionernum asc");
		break;
	}
	if(query.exec(base + method))
	{
		while(query.next())
		{
			players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
			questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
		}
		sendRanklist(players, questioners, sortMethod, socketDescriptor);
	}
	else
		qDebug() << query.lastError() << "query for player ranklist failed: " << method;

#endif
}

void DatabaseServer::receiveDetailInfoRequest(SortMethod sortMethod, int index, qintptr socketDescriptor)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(tr("%1,%2,%3").arg(DETAILINFO_FUNCTION).arg(sortMethod).arg(index));
#else
	QString base = tr("select * from user order by ");
	QString method;
	QString limit = tr(" limit %1, 1").arg(index);
	switch(sortMethod)
	{
	// initial state, should not be received
	case NULL_SORT:
		qDebug() << "error receiving NULL_SORT";
		return;
	// player part
	case PLAYER_LEVEL_DESC:
		method = tr("playerlevel desc, playerexp desc");
		break;
	case PLAYER_LEVEL_ASC:
		method = tr("playerlevel asc, playerexp asc");
		break;
	case PLAYER_NAME_DESC:
		method = tr("username desc");
		break;
	case PLAYER_NAME_ASC:
		method = tr("username asc");
		break;
	case PLAYER_NUM_DESC:
		method = tr("playernum desc");
		break;
	case PLAYER_NUM_ASC:
		method = tr("playernum asc");
		break;
	// questioner part
	case QUESTIONER_LEVEL_DESC:
		method = tr("questionerlevel desc, questionerexp desc");
		break;
	case QUESTIONER_LEVEL_ASC:
		method = tr("questionerlevel asc, questionerexp asc");
		break;
	case QUESTIONER_NAME_DESC:
		method = tr("username desc");
		break;
	case QUESTIONER_NAME_ASC:
		method = tr("username asc");
		break;
	case QUESTIONER_NUM_DESC:
		method = tr("questionernum desc");
		break;
	case QUESTIONER_NUM_ASC:
		method = tr("questionernum asc");
		break;
	}
	if(query.exec(base + method + limit))
	{
		if(query.next())
		{
			sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
						   Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()),
						   socketDescriptor);
		}
		else
			qDebug() << query.lastError() << "no detail user info... error";
	}
	else
		qDebug() << query.lastError() << "get detail failed for " << method;
#endif
}

void DatabaseServer::receiveWordListRequest(GameLevel level, qintptr socketDescriptor, qintptr socketDescriptor2, int wordNum)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(tr("%1,%2").arg(WORDLIST_FUNCTION).arg(level));
#else
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
	if(query.exec(tr("select * from wordlist where %1 order by random() limit %2").arg(levelRange).arg(wordNum)))
	{
		while(query.next())
		{
			words.push_back(Word(query.value(0).toString(), query.value(1).toInt()));
		}
		qDebug() << "Receive " << words.size() << "words";
		if(socketDescriptor2 == -1)
		{
			sendWordList(words, socketDescriptor);
		}
		else
		{
			sendWordList(words, socketDescriptor);
			sendWordList(words, socketDescriptor2);
		}
	}
	else
		qDebug() << query.lastError() << "get wordlist failed";
#endif
}

void DatabaseServer::receiveEndGamePacket(EndGamePacket packet, qintptr socketDescriptor)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(QString::number(UPDATE_EXP_FUNCTION) + ',' + packet.toString());
#else
	double difficultyScale;
	int expGained;
	if(packet.isWin == GAME_SINGLE)
	{
		 difficultyScale = DIFFICULTY_SCALE_TABLE[packet.level];
		 expGained = static_cast<int>(50 * (max(packet.correctNum - packet.wrongNum, 0))
											  * difficultyScale);
	}
	else
	{
		expGained = packet.expGained;
	}
		if(query.exec(tr("select playerlevel, playerexp, playernum from user where username='%1'").arg(packet.playerName)))
		{
			if(query.next())
			{
				// calculating update
				qDebug() << "update " << packet.playerName;
				int preLevel = query.value(0).toInt();
				int preExp = query.value(1).toInt();
				int preNum = query.value(2).toInt();
				qDebug() << "preLevel: " << preLevel << " preExp: " << preExp << " preNum: " << preNum;
				int curExp = max(preExp + expGained, 0);
				int curNum = preNum + packet.correctNum;
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
						   .arg(curLevel).arg(curExp).arg(curNum).arg(packet.playerName)))
				{
					qDebug() << "updatelevel success";

					// after update the database, send it to the mainwindow
					if(query.exec(tr("select * from user where username='%1'").arg(packet.playerName)))
					{
						if(query.next())
						{
							packet.expGained = expGained;

							server.setUserStatus(socketDescriptor, STATUS_FREE);
							sendEndGamePacket(packet, socketDescriptor);
							sendUserInfo(Player(packet.playerName, query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
										 Questioner(packet.playerName, query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()),
										 socketDescriptor);
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


#endif
}



void DatabaseServer::receiveQuestionWordList(QVector<Word> words, QString questioner, qintptr socketDescriptor)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(QString::number(ADDWORD_FUNCTION) + ",__start," + questioner);
	for(auto word : words)
	{
		tcpClient.sendDataToServer(QString::number(ADDWORD_FUNCTION) + ',' + word.getWord() + ',' + questioner);
	}
	tcpClient.sendDataToServer(QString::number(ADDWORD_FUNCTION) + ",__end," + questioner);
#else
	int cnt = 0;
	double expGained = 0.0;
	int wordCount = 1;
	// insert into wordlist
	for(auto word: words)
	{
		++wordCount;
		if(wordCount % 1000 == 0)
		{
			server.writeLog(server.getCurrentTimeStamp() +
							tr(" host: busy dealing word %1/%2").arg(wordCount).arg(words.size()));
			sendWaitingMessage(socketDescriptor);
			QTime t;
			t.start();
			while(t.elapsed() < 500)
			{
				QThread::msleep(10);
				QApplication::processEvents();
			}
		}


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
						sendUserInfo(Player(questioner, query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
									 Questioner(questioner, query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()),
									 socketDescriptor);
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

	sendAddedWords(cnt, expGained_int, socketDescriptor);
#endif
}

void DatabaseServer::receiveOnlineUserRequest(qintptr socketDescriptor)
{
	 QVector<QString> user = server.excludeOneOnlineUser(socketDescriptor).toVector();
	 sendOnlineUsers(user, socketDescriptor);
}

void DatabaseServer::receiveOnlineUserDetailInfoRequest(QString user, qintptr socketDescriptor)
{
	if(query.exec(tr("select * from user where username='%1'").arg(user)))
	{
		if(query.next())
		{
			sendOnlineUserDetail(Player(user, query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
								 Questioner(user, query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()),
								 socketDescriptor);
		}
		else
			qDebug() << "online detail unfound";
	}
	else
		qDebug() << query.lastError() << "online detail failed";
}

void DatabaseServer::receiveBattleRequest(BattlePacket packet, qintptr socketDescriptor)
{
	assert(packet.isRequest == true);
	packet.self = server.getOnlineUsername(socketDescriptor);
	if(server.getOnlineSocket(packet.enemy) == 0)
	{
		packet.respond = BATTLE_OFFLINE;
		sendBattleRespond(packet, socketDescriptor);
		return;
	}
	switch(server.getUserStatus(server.getOnlineSocket(packet.enemy)))
	{
	case STATUS_FREE:
	{
		server.setUserStatus(socketDescriptor, STATUS_WAITING_BATTLE);
		BattlePacket enemyPacket = packet;
		swap(enemyPacket.self, enemyPacket.enemy);
		sendBattleRequest(enemyPacket, server.getOnlineSocket(packet.enemy));
	}
		break;
	case STATUS_WAITING_BATTLE:
	case STATUS_WAITING_MATCH:
	case STATUS_PLAYING:
		packet.respond = BATTLE_REJECT;
		sendBattleRespond(packet, socketDescriptor);
		break;
	}

}

void DatabaseServer::receiveBattelRespond(BattlePacket packet, qintptr socketDescriptor)
{
	assert(packet.isRequest == false);
	switch(packet.respond)
	{
	case BATTLE_ACCEPT:
		emit sendStartMatch(packet.level, socketDescriptor, server.getOnlineSocket(packet.enemy), packet.wordNum);
		break;
	case BATTLE_REJECT:
	{
		server.setUserStatus(server.getOnlineSocket(packet.enemy), STATUS_FREE);
		BattlePacket enemyPacket = packet;
		swap(enemyPacket.self, enemyPacket.enemy);
		sendBattleRespond(enemyPacket, server.getOnlineSocket(packet.enemy));
	}
		break;
	case BATTLE_MYSELF:
		receiveWordListRequest(EXPERT, socketDescriptor);
		break;
	default:
		server.writeLog(server.getCurrentTimeStamp() + " host: ERROR unexpected battle form " + QString::number(packet.respond));
	}
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
