#include "databaseserver.h"
#include<QTime>
#include<QThread>
#include<QApplication>
using std::max;

#ifndef USE_NETWORK
DatabaseServer::DatabaseServer()
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
#else
	connect(&tcpClient, &TcpClient::messageQueueReady, this, &DatabaseServer::handleMessages);
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

void DatabaseServer::receiveLoginPackage(LoginPackage loginPackage)
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
#endif
}

void DatabaseServer::receiveRegisterPackage(RegisterPackage registerPackage)
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
#endif
}

void DatabaseServer::receiveRanklistRequest(SortMethod sortMethod)
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
	if(query.exec(base + method))
	{
		while(query.next())
		{
			players.push_back(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()));
			questioners.push_back(Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
		}
		emit sendRanklist(players, questioners, sortMethod);
	}
	else
		qDebug() << query.lastError() << "query for player ranklist failed: " << method;
#endif
}

void DatabaseServer::receiveDetailInfoRequest(SortMethod sortMethod, int index)
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
			emit sendDetailInfo(Player(query.value(0).toString(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
							  Questioner(query.value(0).toString(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
		}
		else
			qDebug() << query.lastError() << "no detail user info... error";
	}
	else
		qDebug() << query.lastError() << "get detail failed for " << method;
#endif
}

void DatabaseServer::receiveWordListRequest(GameLevel level, GameStatus status)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(tr("%1,%2,%3").arg(WORDLIST_FUNCTION).arg(level).arg(status));
#else
	assert(status == GAME_SINGLE);
	QVector<Word> words;
	QString levelRange;
	int num = 2 + level;
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
	if(query.exec(tr("select * from wordlist where %1 order by random() limit %2").arg(levelRange).arg(num)))
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
#endif
}

void DatabaseServer::receiveEndGamePacket(EndGamePacket packet)
{
#ifdef USE_NETWORK
	tcpClient.sendDataToServer(QString::number(UPDATE_EXP_FUNCTION) + ',' + packet.toString());
#else
	double difficultyScale = DIFFICULTY_SCALE_TABLE[packet.level];
	int expGained = static_cast<int>(50 * (max(packet.correctNum - packet.wrongNum, 0))
									 * difficultyScale);
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
			int curExp = preExp + expGained;
#ifndef VERSION1
			packet.expGained = expGained;
#endif
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
						emit sendShowEndGameDialog(packet);
						emit sendUserInfo(Player(packet.playerName, query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt()),
										  Questioner(packet.playerName, query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt()));
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



void DatabaseServer::receiveQuestionWordList(QVector<Word> words, QString questioner)
{
#ifdef USE_NETWORK
	int count = 0;
	tcpClient.sendDataToServer(QString::number(ADDWORD_FUNCTION) + ',' + Word::specialWord() + ',' + questioner);
	for(auto word : words)
	{
		tcpClient.sendDataToServer(QString::number(ADDWORD_FUNCTION) + ',' + word.toString() + ',' + questioner);
		++count;

		if(count >= 1000)
		{
			tcpClient.sendDataToServer(QString::number(ADDWORD_FUNCTION) + ',' + "__wait.0" + ',' + questioner);
			QTime t;
			t.start();
			while(t.elapsed() < 2000)
			{
				QThread::msleep(10);
				QApplication::processEvents();
			}
			count = 0;
		}
	}
	tcpClient.sendDataToServer(QString::number(ADDWORD_FUNCTION) + ',' + Word::specialWord(false) + ',' + questioner);
#else
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
#endif
}

#ifdef USE_NETWORK
void DatabaseServer::handleMessages()
{
	static bool busy = false;
	if(busy) return;
	qDebug() << "message processing";
	busy = true;
	while(!tcpClient.messageQueue.empty())
	{
		QString message = tcpClient.messageQueue.front();
		tcpClient.messageQueue.pop_front();
		QStringList function = message.split(',');
		bool ok;
		int functionCode = function[0].toInt(&ok);
		if(!ok)
		{
			qDebug() << "ERROR function code" << function[0];
			continue;
		}
		switch(functionCode)
		{
		case LOGIN_FUNCTION:
			emit sendLoginState(static_cast<LoginState>(function[1].toInt()));
			break;
		case REGISTER_FUNCTION:
			emit sendRegisterState(static_cast<RegisterState>(function[1].toInt()));
			break;
		case USERINFO_FUNCTION:
			emit sendUserInfo(Player::fromString(function[1]), Questioner::fromString(function[2]));
			break;
		case RANKLIST_FUNCTION:
		{
			Player player = Player::fromString(function[1]);
			Questioner questioner = Questioner::fromString(function[2]);
			if(player.getUserName() == "__start")
			{
				ranklistCache.players.clear();
				ranklistCache.questioners.clear();
				if(player.getLevel() == questioner.getLevel())
				{
					ranklistCache.method = static_cast<SortMethod>(player.getLevel());
				}
			}
			else if(player.getUserName() == "__end")
			{
				qDebug() << (ranklistCache.method == player.getLevel());
				emit sendRanklist(ranklistCache.players, ranklistCache.questioners, ranklistCache.method);
			}
			else
			{
				ranklistCache.players.push_back(player);
				ranklistCache.questioners.push_back(questioner);
			}
		}
			break;
		case DETAILINFO_FUNCTION:
		{
			qDebug() << "ranklist detail";
			Player player = Player::fromString(function[1]);
			Questioner questioner = Questioner::fromString(function[2]);
			emit sendDetailInfo(player, questioner);
		}
			break;
		case WORDLIST_FUNCTION:
		{
			Word word = Word::fromString(function[1]);
			if(word.getWord() == "__start")
			{
				wordsCache.clear();
			}
			else if(word.getWord() == "__end")
			{
				emit sendWordList(wordsCache);
			}
			else
			{
				wordsCache.push_back(word);
			}
		}
			break;
		case UPDATE_EXP_FUNCTION:
		{
			EndGamePacket packet = EndGamePacket::fromString(function[1]);
			emit sendShowEndGameDialog(packet);
		}
			break;
		case ADDWORD_FUNCTION:
			emit sendAddedWords(function[1].toInt(), function[2].toInt());
			break;
		case ONLINE_USERS_FUNCTION:
		{
			QVector<QString> onlineUser = function[1].split('.').toVector();
			emit sendOnlineUsers(onlineUser);
		}
			break;
		case ONLINE_USER_DETAIL_FUNCTION:
		{
			Player player = Player::fromString(function[1]);
			Questioner questioner = Questioner::fromString(function[2]);
			emit sendOnlineUserDetail(player, questioner);
		}
			break;
		case REQUEST_BATTLE_FUNCTION:
		{
			BattlePacket packet = BattlePacket::fromString(function[1]);
			emit sendBattleRequest(packet);
		}
			break;
		case RESPOND_BATTLE_FUNCTION:
		{
			BattlePacket packet = BattlePacket::fromString(function[1]);
			emit sendBattleRespond(packet);
		}
			break;
		case WAIT_FUNCTION:
			emit sendWaitSignal();
			break;
		case GAME_CANCEL_FUNCTION:
			emit sendEnemyGameCancel();
			break;
		default:
			qDebug() << "ERROR unexpected functioncode " << functionCode;
		}

	}
	busy = false;
}

void DatabaseServer::receiveOnlineUserRequest()
{
	tcpClient.sendDataToServer(QString::number(ONLINE_USERS_FUNCTION));
}

void DatabaseServer::receiveOnlineUserDetailInfoRequest(QString user)
{
	tcpClient.sendDataToServer(QString::number(ONLINE_USER_DETAIL_FUNCTION) + ',' + user);
}

void DatabaseServer::receiveBattleRequest(BattlePacket packet)
{
	tcpClient.sendDataToServer(QString::number(REQUEST_BATTLE_FUNCTION) + ',' + packet.toString());
}

void DatabaseServer::receiveBattelRespond(BattlePacket packet)
{
	tcpClient.sendDataToServer(QString::number(RESPOND_BATTLE_FUNCTION) + ',' +
							   packet.toString());
}

void DatabaseServer::receiveGameCancel()
{
	tcpClient.sendDataToServer(QString::number(GAME_CANCEL_FUNCTION));
}
#endif

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
