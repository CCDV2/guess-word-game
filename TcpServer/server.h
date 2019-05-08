#ifndef SERVER_H
#define SERVER_H

#include<QTcpServer>
#include<QObject>
#include<QListWidget>
#include"tcpclientsocket.h"
#include<QTimer>


class Server: public QTcpServer
{
	Q_OBJECT
public:
	Server(QListWidget &_contentWidget, QObject *parent = nullptr, int port = 0);
	QList<TcpClientSocket *> tcpClientSocketList;

	static QString getCurrentTimeStamp();
	void sendMessageToClient(qintptr socketDescriptor, QString message);
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

};

#endif // SERVER_H
