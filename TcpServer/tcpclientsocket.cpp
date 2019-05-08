#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
	Q_UNUSED(parent)

	connect(this, &TcpClientSocket::readyRead, this, &TcpClientSocket::dataReceived);
	connect(this, &TcpClientSocket::disconnected, this, &TcpClientSocket::slotDisconnected);
}

void TcpClientSocket::dataReceived()
{
	while(bytesAvailable() > 0)
	{
		int length = static_cast<int>(bytesAvailable());
		QByteArray datagram;
		datagram.resize(length);
		read(datagram.data(), length);
		QString message = datagram.data();
		emit sendUpdateClients(message, length, this->socketDescriptor());
	}
}

void TcpClientSocket::slotDisconnected()
{
	emit socketDisconnected(static_cast<int>(this->socketDescriptor()));
}
