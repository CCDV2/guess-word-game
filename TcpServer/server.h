#ifndef SERVER_H
#define SERVER_H

#include<QTcpServer>
#include<QObject>
#include<QListWidget>
#include"tcpclientsocket.h"
#include<QTimer>
#include<QFile>
#include<QTextStream>
#include"datastructure.h"

class Server: public QTcpServer
{
	Q_OBJECT
public:
	Server(QListWidget &_contentWidget, QObject *parent = nullptr, int port = 0);
	~Server();
	QList<TcpClientSocket *> tcpClientSocketList;

	static QString getCurrentTimeStamp();
	void sendMessageToClient(qintptr socketDescriptor, QString message);

	void addOnlineUser(qintptr socketDescriptor, QString userName);
	const QString getOnlineUsername(qintptr socketDescriptor) const;
	qintptr getOnlineSocket(QString userName) const;
	QStringList excludeOneOnlineUser(qintptr socketDescriptor);
	UserStatus getUserStatus(qintptr socketDescriptor);
	void setUserStatus(qintptr socketDescriptor, UserStatus status);

	void writeLog(QString message);

signals:
	void sendUpdateServer(QString message, int length, qintptr socketDescriptor);
public slots:
	void ReceiveUpdateClients(QString message, int length, qintptr socketDescriptor);
	void slotDisconnected(int descriptor);

protected:
	void incomingConnection(qintptr socketDescriptor);
private slots:
	void recheckClients();
private:


	QListWidget &contentListWidget;
	QTimer timer;
	QHash<qintptr, TcpClientSocket *> descriptorToSocket;
	QHash<qintptr, QString> descriptorToOnlineUser;
	QHash<QString, qintptr> onlineUserToDescriptor;
	QHash<qintptr, UserStatus> userStatus;

	QFile file;
	QTextStream fileStream;
};

#endif // SERVER_H
