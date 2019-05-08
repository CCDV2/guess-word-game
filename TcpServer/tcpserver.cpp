#include "tcpserver.h"
#include<QTime>
#include<QStringList>

TcpServer::TcpServer(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent)
{
	Q_UNUSED(f)

	port = 8010;
	setWindowState(Qt::WindowMaximized);
	createWidget();
	createLayout();
	createConnection();
}

TcpServer::~TcpServer()
{

}

void TcpServer::sendMessage(qintptr socketDescriptor, QString message)
{
	server->sendMessageToClient(socketDescriptor, message);
}



void TcpServer::slotCreateServer()
{
	server = new Server(*contentListWidget, this, port);
	DBServer = new DatabaseServer(*server, this);
	connect(server, &Server::sendUpdateServer, this, &TcpServer::receiveUpdateServer);
	createButton->setEnabled(false);

}

void TcpServer::receiveUpdateServer(QString message, int length, qintptr socketDescriptor)
{
	contentListWidget->addItem(Server::getCurrentTimeStamp() + ' ' + QString::number(socketDescriptor) + ": " + message.left(length));
	QStringList messages = message.left(length).split('\n');
	for(auto toHandleMessage : messages)
	{
		if(toHandleMessage.isEmpty()) continue;
		messageQueue.push_back({toHandleMessage, socketDescriptor});
	}
	handleMessage();
}

void TcpServer::handleMessage()
{
	while(!messageQueue.empty())
	{
		auto item = messageQueue.front();
		messageQueue.pop_front();
		QString message = item.message;
		qintptr socketDescriptor = item.socketDescriptor;

		QStringList function = message.split(',');
		bool ok;
		int functionCode = function[0].toInt(&ok);
		if(!ok)
		{
			contentListWidget->addItem(Server::getCurrentTimeStamp() + ' ' + "host: ERROR converting function code. Origin string is " + function[0]);
			continue;
		}
		switch(functionCode)
		{
		case LOGIN_FUNCTION:
			DBServer->receiveLoginPackage(LoginPackage::fromString(function[1]), socketDescriptor);
			break;
		case REGISTER_FUNCTION:
			DBServer->receiveRegisterPackage(RegisterPackage::fromString(function[1]), socketDescriptor);
			break;
		case USERINFO_FUNCTION:
			break;
		case RANKLIST_FUNCTION:
			DBServer->receiveRanklistRequest(static_cast<SortMethod>(function[1].toInt()), socketDescriptor);
			break;
		case DETAILINFO_FUNCTION:
			DBServer->receiveDetailInfoRequest(static_cast<SortMethod>(function[1].toInt()), function[2].toInt(), socketDescriptor);
			break;
		case WORDLIST_FUNCTION:
			DBServer->receiveWordListRequest(static_cast<GameLevel>(function[1].toInt()), socketDescriptor);
			break;
		case UPDATE_EXP_FUNCTION:
		{
			EndGamePacket packet = EndGamePacket::fromString(function[1]);
			DBServer->receiveEndGamePacket(packet, socketDescriptor);
		}
			break;
		case ADDWORD_FUNCTION:
		{
			Word word = Word::fromString(function[1]);
			QString questioner = function[2];
			if(word.getWord() == "__start")
			{
				addWordCache.words.clear();
				addWordCache.questioner = questioner;
			}
			else if(word.getWord() == "__end")
			{
				qDebug() << (addWordCache.questioner == questioner);
				DBServer->receiveQuestionWordList(addWordCache.words, addWordCache.questioner, socketDescriptor);
			}
			else
			{
				addWordCache.words.push_back(word);
			}
		}
			break;
		default:
			contentListWidget->addItem(Server::getCurrentTimeStamp() + ' ' + tr("host: unexpected function code %1").arg(functionCode));
			break;
		}
	}
}

void TcpServer::createWidget()
{
	setWindowTitle(tr("TCP Server"));
	contentListWidget = new QListWidget();
	portLabel = new QLabel(tr("端口："));
	portLineEdit = new QLineEdit();
	portLineEdit->setText(QString::number(port));
	createButton = new QPushButton(tr("创建聊天室"));
}

void TcpServer::createLayout()
{
	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(contentListWidget, 0, 0, 1, 2);
	mainLayout->addWidget(portLabel, 1, 0);
	mainLayout->addWidget(portLineEdit, 1, 1);
	mainLayout->addWidget(createButton, 2, 0, 1, 2);
}

void TcpServer::createConnection()
{
	connect(createButton, &QPushButton::clicked, this, &TcpServer::slotCreateServer);
}
