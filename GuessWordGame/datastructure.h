#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include<QString>
#include<QStringList>
#include<QObject>

struct LoginPackage
{
	QString userName;
	QString passWord;
	LoginPackage(QString _userName, QString _passWord):
		userName(_userName), passWord(_passWord) {}
	QString toString()
	{
		QString temp = userName + '.' + passWord;
		return temp;
	}
	static LoginPackage fromString(QString s)
	{
		QStringList temp = s.split('.');
		return LoginPackage(temp[0], temp[1]);
	}
};
typedef LoginPackage RegisterPackage;

//using RegisterPackage=LoginPackage ;
enum LoginState
{
	LOGIN_SUCCESS,
	WRONG_PASSWORD,
	UNFOUND_USERNAME,
	LOGIN_ALREADY
};

enum RegisterState
{
	REGISTER_SUCCESS,
	USER_EXISTED
};

enum SortMethod
{
	NULL_SORT,
	PLAYER_LEVEL_DESC,
	PLAYER_LEVEL_ASC,
	PLAYER_NAME_DESC,
	PLAYER_NAME_ASC,
	PLAYER_NUM_DESC,
	PLAYER_NUM_ASC,
	QUESTIONER_LEVEL_DESC,
	QUESTIONER_LEVEL_ASC,
	QUESTIONER_NAME_DESC,
	QUESTIONER_NAME_ASC,
	QUESTIONER_NUM_DESC,
	QUESTIONER_NUM_ASC
};

enum GameLevel
{
	EASY = 0,
	NORMAL = 1,
	HARD = 2,
	EXPERT = 3
};

const int LEVEL_TIME_TABLE[] =
{
	0,
	2750, //level 1
	2500, //level 2
	2250, //level 3
	2000, //level 4
	1750, //level 5
	1500, //level 6
	1250, //level 7
	1000, //level 8
	750, //level 9
	500, //level 10
};

const double DIFFICULTY_SCALE_TABLE[] =
{
	1.00,
	1.05,
	1.10,
	1.15
};

const int TIME_INTERVAL = 20;

inline int getLevelMaxExp(int level)
{
	// 0~100: lv * 100
	// 100~300: lv * 50 + 5000
	// 300+: 20000
	return level <= 100 ? level * 100 : (level <= 300 ? 5000 + level * 50 : 20000);
}

const double LEVEL_SCALE_TABLE[] =
{
	0,
	1.01, //level 1
	1.02, //level 2
	1.03, //level 3
	1.04, //level 4
	1.05, //level 5
	1.06, //level 6
	1.07, //level 7
	1.08, //level 8
	1.09, //level 9
	1.10, //level 10
};

const int MIN_WORD_LEVEL = 1;
const int MAX_WORD_LEVEL = 10;

enum DetailedWidgetArg
{
	MYSELF_OPEN,
	RANKLIST_OPEN,
	ONLINE_OPEN
};

// used for qss selection
const QString levelBarName = "levelBar";
const QString moduleWidgetName = "ModuleWidget";
const QString levelButtonName = "levelButton";

// used for tcp connection
enum ConnectFunction
{
	LOGIN_FUNCTION,
	REGISTER_FUNCTION,
	USERINFO_FUNCTION,
	RANKLIST_FUNCTION,
	DETAILINFO_FUNCTION,
	WORDLIST_FUNCTION,
	UPDATE_EXP_FUNCTION,
	ADDWORD_FUNCTION,
	ONLINE_USERS_FUNCTION,
	ONLINE_USER_DETAIL_FUNCTION,
	REQUEST_BATTLE_FUNCTION,
	RESPOND_BATTLE_FUNCTION,
	WAIT_FUNCTION,
	GAME_CANCEL_FUNCTION
};

// version3
#define USE_NETWORK
#ifndef USE_NETWORK
// version1, comment it will be version2
// #define VERSION1
#endif

enum GameStatus
{
	GAME_SINGLE,
	GAME_DUO,
	GAME_WIN,
	GAME_LOSE,
	GAME_TIE,
};

struct EndGamePacket
{
	EndGamePacket(QString _playerName = "", GameLevel _level = EASY, int _correctNum = 0, int _wrongNum = 0, int _totalTime = 0,
				  int _enemyTotalTime = 0, int _enemyCorrectNum = 0, GameStatus _isWin = GAME_SINGLE, int _expGained = 0):
		playerName(_playerName), level(_level), correctNum(_correctNum), wrongNum(_wrongNum), totalTime(_totalTime),
		enemyTotalTime(_enemyTotalTime), enemyCorrectNum(_enemyCorrectNum),isWin(_isWin), expGained(_expGained){}
	const QString toString()
	{
		return playerName + '.' + QString::number(level) + '.' +
				QObject::tr("%1.%2.%3.%4.%5.").
				arg(correctNum).arg(wrongNum).arg(totalTime).
				arg(enemyTotalTime).arg(enemyCorrectNum)
				+ QString::number(isWin) + '.' + QString::number(expGained);
	}
	static const EndGamePacket fromString(QString s)
	{
		QStringList list = s.split('.');
		return EndGamePacket(list[0],
				static_cast<GameLevel>(list[1].toInt()),
				list[2].toInt(),
				list[3].toInt(),
				list[4].toInt(),
				list[5].toInt(),
				list[6].toInt(),
				static_cast<GameStatus>(list[7].toInt()),
				list[8].toInt());
	}
	QString playerName;
	GameLevel level;
	int correctNum, wrongNum;
	int totalTime;
	int enemyTotalTime;
	int enemyCorrectNum;
	GameStatus isWin;
	int expGained;
};

enum BattleRespond
{
	BATTLE_REJECT,
	BATTLE_ACCEPT,
	BATTLE_MYSELF,
	BATTLE_OFFLINE
};

struct BattlePacket
{
	BattlePacket(QString _self = "", QString _enemy = "", bool _isRequest = true,
				 BattleRespond _respond = BATTLE_MYSELF, GameLevel _level = EXPERT, int _wordNum = 5):
		self(_self), enemy(_enemy), isRequest(_isRequest), respond(_respond), level(_level), wordNum(_wordNum){}

	const QString toString()
	{
		QString ret = QStringList({self,
								   enemy,
								   QString::number(isRequest),
								   QString::number(respond),
								   QString::number(level),
								   QString::number(wordNum)}).join('.');
		return ret;
	}

	static BattlePacket fromString(QString s)
	{
		QStringList list = s.split('.');
		return BattlePacket(list[0], list[1], list[2].toInt(),
				static_cast<BattleRespond>(list[3].toInt()),
				static_cast<GameLevel>(list[4].toInt()),
				list[5].toInt());
	}

	QString self, enemy;
	bool isRequest;
	BattleRespond respond;
	GameLevel level;
	int wordNum;
};

#endif // DATASTRUCTURE_H
