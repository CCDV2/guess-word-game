#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QStackedWidget>
#include "logindialog.h"
#include"gamewidget.h"
#include"registerdialog.h"
#include"simplifieduserinfowidget.h"
#include"detaileduserinfodialog.h"
#include"databaseserver.h"
#include"ranklistwidget.h"
#include"questionwidget.h"
#include"gamemodeselectwidget.h"
#include"friendwidget.h"
#include"tcpclient.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
signals:
	void sendUserInfo(Player player, Questioner questioner);
	void sendQuestionerName(QString _questionerName);
public slots:
	void receiveUserInfo(Player _player, Questioner _questioner);
	// to detial user info
	void receiveRequireForUserInfo();
	// to questioner
	void receiveRequireForQuestionerName();

private slots:
	void on_startGameButton_clicked();
	void on_startQuestionButton_clicked();
	void on_startRanklistButton_clicked();
	void backToWelcomeWidget();
	void receiveGameMode(GameLevel level);
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QWidget *mainWidget;
	QHBoxLayout *mainLayout;
	QVBoxLayout *buttonLayout;
//	LoginDialog *loginWindow;
//	RegisterDialog *registerWindow;
	GameWidget *gameWidget;
	GameModeSelectWidget *gameModeSelectWidget;
	SimplifiedUserInfoWidget *simplifiedUserInfoWidget;
	QPushButton *startGameButton, *startQuestionButton, *startRanklistButton;
	QuestionWidget *questionWidget;
	RanklistWidget *ranklistWidget;
	QStackedWidget *stackWidget;
	FriendWidget *friendWidget;

	// welcome gameselect game question display
	QWidget *widget[5];
	QPushButton *backButton[4];
	QHBoxLayout *widgetLayout[5];

	QLabel *logoLabel;

	Player *player;
	Questioner *questioner;
	DatabaseServer *DBServer;
	TcpClient *tcpClient;
};

#endif // MAINWINDOW_H
