#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include<QLabel>
#include<QWidget>
#include<QGridLayout>
#include<QLineEdit>
#include<QPushButton>
#include<QListWidget>
#include<QQueue>
#include<QHash>
#include<QVector>
#include"server.h"
#include"datastructure.h"
#include"databaseserver.h"
#include"matchmodule.h"


struct MessageQueueItem
{
	QString message;
	qintptr socketDescriptor;
};


class TcpServer : public QDialog
{
	Q_OBJECT

public:
	TcpServer(QWidget *parent = nullptr, Qt::WindowFlags f = nullptr);
	~TcpServer();

	void sendMessage(qintptr socketDescriptor, QString message);
	void writeLog(QString message);

public slots:
	void slotCreateServer();
	void receiveUpdateServer(QString message, int length, qintptr socketDescriptor);
	void receiveDeleteRequest(MatchModule *module);
	void startMatch(int level, qintptr p1, qintptr p2, int wordNum);
private slots:
private:
	void handleMessage();

	void checkWaitingList();
	bool sendToMatch(EndGamePacket packet, qintptr socketDescriptor);

	bool removeFromWaitingMacthList(qintptr socketDescriptor);

	void createWidget();
	void createLayout();
	void createConnection();

	QListWidget *contentListWidget;

	QLabel *portLabel;
	QLineEdit *portLineEdit;
	QPushButton *createButton;
	QGridLayout *mainLayout;

	int port;
	Server *server;
	QQueue<MessageQueueItem> messageQueue;
	DatabaseServer *DBServer;

	QVector<qintptr> waitingMatchList[4];
	QVector<MatchModule *> matches;
	QHash<qintptr, qintptr> waitingBattlePair;


	struct
	{
		QVector<Word> words;
		QString questioner;
	} addWordCache;


};

#endif // TCPSERVER_H
