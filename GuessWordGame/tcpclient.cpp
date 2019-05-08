#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent): QObject(parent)
{
	Q_UNUSED(parent)

	port = 8010;
	serverIP = new QHostAddress();
	QString ip = "127.0.0.1";
	if(!serverIP->setAddress(ip))
	{
		qDebug() << "IP error";
	}
	tcpSocket = new QTcpSocket(this);
	connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::tcpConnected);
	connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpClient::tcpDisconnected);
	connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::receiveDataFromServer);
	tcpSocket->connectToHost(*serverIP, static_cast<quint16>(port));
}

TcpClient::~TcpClient()
{
	tcpSocket->disconnectFromHost();
}

void TcpClient::sendDataToServer(QString message)
{
	if(message.isEmpty())
	{
		qDebug() << "null message";
		return;
	}
	message = message + '\n';
	qDebug() << "send to server:";
	qDebug() << message;
	tcpSocket->write(message.toLatin1(), message.length());
}

void TcpClient::receiveDataFromServer()
{
	while(tcpSocket->bytesAvailable() > 0)
	{
		QByteArray datagram;
		datagram.resize(static_cast<qint32>(tcpSocket->bytesAvailable()));
		tcpSocket->read(datagram.data(), datagram.size());
		QString message = datagram.data();
		QStringList messages = message.split('\n');
		for(auto toHandleMessage : messages)
		{
			if(toHandleMessage.isEmpty()) continue;
			messageQueue.push_back(toHandleMessage);
		}
	}
	emit messageQueueReady();
}

void TcpClient::tcpConnected()
{
	qDebug() << "connect established";
}

void TcpClient::tcpDisconnected()
{
	qDebug() << "disconnected";
}
