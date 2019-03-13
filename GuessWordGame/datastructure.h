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


#endif // DATASTRUCTURE_H
