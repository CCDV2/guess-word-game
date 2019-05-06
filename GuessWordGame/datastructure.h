#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include<QString>


struct LoginPackage
{
	QString userName;
	QString passWord;
	LoginPackage(QString _userName, QString _passWord):
		userName(_userName), passWord(_passWord) {}
};
typedef LoginPackage RegisterPackage;

//using RegisterPackage=LoginPackage ;
enum LoginState
{
	LOGIN_SUCCESS,
	WRONG_PASSWORD,
	UNFOUND_USERNAME
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

// used for qss selection
const QString levelBarName = "levelBar";
const QString moduleWidgetName = "ModuleWidget";

#endif // DATASTRUCTURE_H
