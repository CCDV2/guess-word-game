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
#include"server.h"
#include"datastructure.h"
#include"databaseserver.h"

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


public slots:
	void slotCreateServer();
	void receiveUpdateServer(QString message, int length, qintptr socketDescriptor);

private:
	void handleMessage();


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

	struct
	{
		QVector<Word> words;
		QString questioner;
	} addWordCache;
};

#endif // TCPSERVER_H
