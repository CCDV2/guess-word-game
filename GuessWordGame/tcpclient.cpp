#include "tcpclient.h"
#include<QTime>
#include<QFile>
#include<QtXml>


TcpClient::TcpClient(QObject *parent): QObject(parent)
{
	Q_UNUSED(parent)
	file.setFileName("config.xml");

	ip = "127.0.0.1";
	port = 8010;

	readXml();

	connectStatus = false;
	serverIP = new QHostAddress();
	if(!serverIP->setAddress(ip))
	{
		qDebug() << "IP error";
	}
	tcpSocket = new QTcpSocket(this);
	connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::tcpConnected);
	connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpClient::tcpDisconnected);
	connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::receiveDataFromServer);
	tcpSocket->connectToHost(*serverIP, static_cast<quint16>(port));
	connectStatus = tcpSocket->waitForConnected();

	writeXml();
}

TcpClient::~TcpClient()
{
	tcpSocket->disconnectFromHost();
}

void TcpClient::sendDataToServer(QString message)
{
	if(!connectStatus)
	{
		qDebug() << "unconnected";
		return;
	}
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

bool TcpClient::isConnected()
{
	return connectStatus;
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
	connectStatus = true;
	qDebug() << "connect established";
}

void TcpClient::tcpDisconnected()
{
	qDebug() << "disconnected";
	emit serverDisconnected();
}

void TcpClient::receiveError(QAbstractSocket::SocketError error)
{
	qDebug() << error;
}

void TcpClient::readXml()
{
	if(file.open(QIODevice::ReadOnly))
	{
		QDomDocument doc;
		if(doc.setContent(&file))
		{
			QDomElement root = doc.documentElement();
			if(root.nodeName() != "config") goto closeFile;
			QDomNode node = root.firstChild();
			if(node.isNull()) goto closeFile;
			qDebug() << node.nodeName();

			QDomElement ipElement = node.toElement();
			if(ipElement.nodeName() != "ip") goto closeFile;
			qDebug() << ipElement.text();
			ip = ipElement.text();

			node = node.nextSibling();
			if(node.isNull()) goto closeFile;

			QDomElement portElement = node.toElement();
			if(portElement.nodeName() != "port") goto closeFile;
			qDebug() << portElement.text();

			bool ok;
			port = portElement.text().toInt(&ok);
			if(!ok)
			{
				port = 8010;
				return;
			}
		}
	closeFile:
		file.close();
	}
}

void TcpClient::writeXml()
{
	if(file.open(QIODevice::WriteOnly))
	{
		QDomDocument doc;
		doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\""));
		QDomElement root = doc.createElement("config");
		doc.appendChild(root);
		QDomElement ipElement = doc.createElement("ip");
		ipElement.appendChild(doc.createTextNode(ip));
		QDomElement portElement = doc.createElement("port");
		portElement.appendChild(doc.createTextNode(QString::number(port)));
		root.appendChild(ipElement);
		root.appendChild(portElement);

		QTextStream os(&file);
		doc.save(os, 4);
		file.close();
	}
}
