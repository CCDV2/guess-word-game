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



#endif // DATASTRUCTURE_H
