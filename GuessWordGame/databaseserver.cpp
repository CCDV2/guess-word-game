#include "databaseserver.h"

DatabaseServer::DatabaseServer()
{

}

LoginState DatabaseServer::checkLoginState(const LoginPackage &loginPackage)
{
	if(loginPackage.userName == QObject::tr("CCDV2"))
	{
		return SUCCESS;
	}
	else
	{
		return UNFOUND_USERNAME;
	}
}
