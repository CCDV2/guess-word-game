#include "server.h"
#include<QDateTime>

Server::Server(QListWidget &_contentListWidget, QObject *parent, int port):
	QTcpServer(parent), contentListWidget(_contentListWidget)
{
	if(listen(QHostAddress::Any, static_cast<quint16>(port)))
	{
		contentListWidget.addItem(getCurrentTimeStamp() + ' ' + tr("host: server establish success"));
		contentListWidget.addItem(getCurrentTimeStamp() + ' ' + tr("host: port on %1").arg(port));
		timer.start(10000);
		connect(&timer, &QTimer::timeout, this, &Server::recheckClients);
	}
	else
	{
		contentListWidget.addItem(getCurrentTimeStamp() + ' ' + tr("host: server establish failed"));
	}
}

QString Server::getCurrentTimeStamp()
{
	QString ret = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
	ret = ret.left(23);
	return ret;
}

void Server::sendMessageToClient(qintptr socketDescriptor, QString message)
{
	message += '\n';
	contentListWidget.addItem(getCurrentTimeStamp() + " host: send to " + QString::number(socketDescriptor) + " message:\n" + message);
	if(descriptorToSocket[socketDescriptor]->write(message.toLatin1(), message.toLatin1().size()) != message.toLatin1().size())
	{
		return;
	}
}


void Server::ReceiveUpdateClients(QString message, int length, qintptr socketDescriptor)
{
	emit sendUpdateServer(message, length, socketDescriptor);
//	for(auto item : tcpClientSocketList)
//	{
//		if(item->write(message.toLatin1(), length) != length)
//		{
//			continue;
//		}
//	}
}

void Server::slotDisconnected(int descriptor)
{
	contentListWidget.addItem(getCurrentTimeStamp() + ' ' + tr("host: disconnect. socket decriptor %1").arg(descriptor));
	for(auto item : tcpClientSocketList)
	{
		if(item->socketDescriptor() == descriptor)
		{
			tcpClientSocketList.removeOne(item);
			return;
		}
	}
	return;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);

	connect(tcpClientSocket, &TcpClientSocket::sendUpdateClients, this, &Server::ReceiveUpdateClients);
	connect(tcpClientSocket, &TcpClientSocket::socketDisconnected, this, &Server::slotDisconnected);
	tcpClientSocket->setSocketDescriptor(socketDescriptor);
	tcpClientSocketList.append(tcpClientSocket);
	descriptorToSocket[socketDescriptor] = tcpClientSocket;
	contentListWidget.addItem(getCurrentTimeStamp() + ' ' + tr("host: connect established. socket descriptor %1").arg(tcpClientSocket->socketDescriptor()));
}

void Server::recheckClients()
{
	contentListWidget.addItem(getCurrentTimeStamp() + ' ' + tr("host: active socket num: %1").arg(tcpClientSocketList.size()));
}
