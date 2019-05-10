#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include<QHostAddress>
#include<QTcpSocket>
#include<QQueue>
#include"datastructure.h"
#include<QFile>

class TcpClient : public QObject
{
	Q_OBJECT
public:
	TcpClient(QObject *parent = nullptr);
	~TcpClient();
	void sendDataToServer(QString message);
	QQueue<QString> messageQueue;
	bool isConnected();
signals:
	void messageQueueReady();
	void serverDisconnected();
public slots:
	void receiveDataFromServer();
private slots:
	void tcpConnected();
	void tcpDisconnected();
	void receiveError(QAbstractSocket::SocketError error);
private:

	void readXml();
	void writeXml();

	QString data;

	bool connectStatus;
	int port;
	QHostAddress *serverIP;
	QString userName;
	QTcpSocket *tcpSocket;

	QFile file;
	QString ip;
};

#endif // TCPCLIENT_H
