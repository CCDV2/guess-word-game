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
	EASY,
	NORMAL,
	HARD,
	EXPERT
};

const int LEVEL_TIME_TABLE[] =
{
	0,
	5500, //level 1
	5000, //level 2
	4500, //level 3
	4000, //level 4
	3500, //level 5
	3000, //level 6
	2500, //level 7
	2000, //level 8
	1500, //level 9
	1000, //level 10
};

#endif // DATASTRUCTURE_H
