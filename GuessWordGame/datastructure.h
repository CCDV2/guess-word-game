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

enum LoginState
{
	SUCCESS,
	WRONG_PASSWORD,
	UNFOUND_USERNAME
};


#endif // DATASTRUCTURE_H
