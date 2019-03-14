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

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
signals:
	void sendUserInfo(Player player, Questioner questioner);
	void sendUpdateUserInfo(Player player, Questioner questioner);
public slots:
	void receiveUserInfo(Player _player, Questioner _questioner);
	void receiveRequireForUserInfo();
private slots:
	void on_startGameButton_clicked();
	void on_startQuestionButton_clicked();
	void on_startRanklistButton_clicked();
	void backToWelcomeWidget();
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
	SimplifiedUserInfoWidget *simplifiedUserInfoWidget;
	QPushButton *startGameButton, *startQuestionButton, *startRanklistButton;
	QuestionWidget *questionWidget;
	RanklistWidget *ranklistWidget;
	QStackedWidget *stackWidget;

	// welcome gameselect game question display
	QWidget *widget[5];
	QPushButton *backButton[4];
	QHBoxLayout *widgetLayout[5];

	QLabel *logoLabel;

	Player *player;
	Questioner *questioner;
	DatabaseServer DBServer;
};

#endif // MAINWINDOW_H
