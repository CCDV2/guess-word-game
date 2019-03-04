#ifndef DATABASESERVER_H
#define DATABASESERVER_H

#include <QObject>
#include"datastructure.h"

class DatabaseServer
{
public:
	DatabaseServer();
	static LoginState checkLoginState(const LoginPackage &loginPackage);
};

#endif // DATABASESERVER_H
