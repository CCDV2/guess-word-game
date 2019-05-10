#include "server.h"
#include<QDateTime>

Server::Server(QListWidget &_contentListWidget, QObject *parent, int port):
	QTcpServer(parent), contentListWidget(_contentListWidget)
{
	file.setFileName(tr("server %1.log").arg(QDateTime::currentDateTime().toString("yyyyMMdd hhmmsszzz")));
	file.open(QIODevice::WriteOnly);
	fileStream.setDevice(&file);

	if(listen(QHostAddress::Any, static_cast<quint16>(port)))
	{
		writeLog(getCurrentTimeStamp() + ' ' + tr("host: server establish success"));
		writeLog(getCurrentTimeStamp() + ' ' + tr("host: port on %1").arg(port));
		timer.start(10000);
		connect(&timer, &QTimer::timeout, this, &Server::recheckClients);
	}
	else
	{
		writeLog(getCurrentTimeStamp() + ' ' + tr("host: server establish failed"));
	}
}

Server::~Server()
{
	file.close();
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
	writeLog(getCurrentTimeStamp() + " host: send to " + QString::number(socketDescriptor) + " message:\n" + message);
	if(descriptorToSocket[socketDescriptor]->write(message.toLatin1(), message.toLatin1().size()) != message.toLatin1().size())
	{
		return;
	}
}

void Server::addOnlineUser(qintptr socketDescriptor, QString userName)
{
	descriptorToOnlineUser[socketDescriptor] = userName;
	onlineUserToDescriptor[userName] = socketDescriptor;
	userStatus[socketDescriptor] = STATUS_FREE;
}

const QString Server::getOnlineUsername(qintptr socketDescriptor) const
{
	return descriptorToOnlineUser[socketDescriptor];
}

qintptr Server::getOnlineSocket(QString userName) const
{
	if(onlineUserToDescriptor.contains(userName))
		return onlineUserToDescriptor[userName];
	else
		return 0;
}

QStringList Server::excludeOneOnlineUser(qintptr socketDescriptor)
{
	QStringList users;
	for(auto item = descriptorToOnlineUser.begin(); item != descriptorToOnlineUser.end(); ++item)
	{
		if(item.key() != socketDescriptor)
		{
			users.push_back(item.value());
		}
	}
	return users;
}

UserStatus Server::getUserStatus(qintptr socketDescriptor)
{
	return userStatus[socketDescriptor];
}

void Server::setUserStatus(qintptr socketDescriptor, UserStatus status)
{
	if(!userStatus.contains(socketDescriptor))
	{
		writeLog(getCurrentTimeStamp() + " host: WARNING cannot set an offline user to " + status);
		return;
	}
	userStatus[socketDescriptor] = status;
}

void Server::writeLog(QString message)
{
	fileStream << message << endl;
	contentListWidget.addItem(message);
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
	for(auto item : tcpClientSocketList)
	{
		if(item->socketDescriptor() == descriptor)
		{
			writeLog(getCurrentTimeStamp() + ' ' +
					 tr("host: disconnect. socket decriptor %1").arg(item->getPreSocketDescriptor()));

			userStatus.remove(item->getPreSocketDescriptor());
			onlineUserToDescriptor.remove(descriptorToOnlineUser[item->getPreSocketDescriptor()]);
			descriptorToSocket.remove(item->getPreSocketDescriptor());
			descriptorToOnlineUser.remove(item->getPreSocketDescriptor());

			tcpClientSocketList.removeOne(item);
			return;
		}
	}
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);

	connect(tcpClientSocket, &TcpClientSocket::sendUpdateClients, this, &Server::ReceiveUpdateClients);
	connect(tcpClientSocket, &TcpClientSocket::socketDisconnected, this, &Server::slotDisconnected);
	tcpClientSocket->setSocketDescriptor(socketDescriptor);
	tcpClientSocket->setPreSocketDescriptor(socketDescriptor);
	tcpClientSocketList.append(tcpClientSocket);
	descriptorToSocket[socketDescriptor] = tcpClientSocket;
	writeLog(getCurrentTimeStamp() + ' ' + tr("host: connect established. socket descriptor %1").arg(tcpClientSocket->socketDescriptor()));
}

void Server::recheckClients()
{
	if(contentListWidget.count() > 10000) contentListWidget.clear();
	writeLog(getCurrentTimeStamp() + ' ' +
			 tr("host: active socket num: %1  active user num: %2").
			 arg(tcpClientSocketList.size()).
			 arg(descriptorToOnlineUser.size()));
}
