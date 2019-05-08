#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include<QHostAddress>
#include<QTcpSocket>
#include<QQueue>
#include"datastructure.h"

class TcpClient : public QObject
{
	Q_OBJECT
public:
	TcpClient(QObject *parent = nullptr);
	~TcpClient();
	void sendDataToServer(QString message);
	QQueue<QString> messageQueue;
signals:
	void messageQueueReady();
public slots:
	void receiveDataFromServer();
private slots:
	void tcpConnected();
	void tcpDisconnected();
private:

	QString data;

	bool status;
	int port;
	QHostAddress *serverIP;
	QString userName;
	QTcpSocket *tcpSocket;
};

#endif // TCPCLIENT_H
