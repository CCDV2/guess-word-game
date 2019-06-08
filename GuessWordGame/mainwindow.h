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
#include"onlineuserwidget.h"
#include"tcpclient.h"
#include<QToolBox>
#include<QMessageBox>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
signals:
	void sendUserInfo(Player player, Questioner questioner);
	void sendQuestionerName(QString _questionerName);

	void sendBattleRespond(BattlePacket packet);

	void sendGameCancel();

public slots:
	void receiveUserInfo(Player _player, Questioner _questioner);
	// to detial user info
	void receiveRequireForUserInfo();
	// to questioner
	void receiveRequireForQuestionerName();

	void receiveBattleRequest(BattlePacket packet);
	void receiveBattleRespond(BattlePacket packet);
	void receiveEnmeyGameCancel();

private slots:
	void on_startGameButton_clicked();
	void on_startQuestionButton_clicked();
	void on_startRanklistButton_clicked();
	void backToWelcomeWidget();
	void receiveGameMode(GameLevel level, GameStatus status, bool needSignal);
	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);
	void paintEvent(QPaintEvent *event);
	void networkFailed();
	void receiveWaitSignal();
	void on_gameBackButton_clicked();
	void battleBoxClosed(int result);
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QWidget *mainWidget;
	QHBoxLayout *mainLayout;
	QVBoxLayout *buttonLayout, *loginOnlineLayout;
//	LoginDialog *loginWindow;
//	RegisterDialog *registerWindow;
	GameWidget *gameWidget;
	GameModeSelectWidget *gameModeSelectWidget;
	SimplifiedUserInfoWidget *simplifiedUserInfoWidget;
	QPushButton *startGameButton, *startQuestionButton, *startRanklistButton;
	QPushButton *exitButton;
	QuestionWidget *questionWidget;
	RanklistWidget *ranklistWidget;
	QStackedWidget *stackWidget;

#ifdef USE_NETWORK
	// network only!!
	OnlineUserWidget *onlineUserWidget;
#endif

	// welcome gameselect game question display
	QWidget *widget[5];
	QPushButton *backButton[4];
	QHBoxLayout *widgetLayout[5];

	QLabel *logoLabel;

	Player *player;
	Questioner *questioner;
	DatabaseServer *DBServer;
#ifdef USE_NETWORK
	TcpClient *tcpClient;
#endif

	QTimer netWorkTimer;
	QMessageBox waitBox, battleBox;
	BattlePacket respondPacket;
};

#endif // MAINWINDOW_H
