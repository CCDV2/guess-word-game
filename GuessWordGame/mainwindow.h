#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "logindialog.h"
#include"gamewidget.h"
#include"registerdialog.h"
#include"simplifieduserinfowidget.h"
#include"detaileduserinfodialog.h"
#include"databaseserver.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
signals:
	void sendUserInfo(Player player, Questioner questioner);
public slots:
	void receiveUserInfo(Player _player, Questioner _questioner);
	void receiveRequireForUserInfo();
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QWidget *mainWidget;
	QGridLayout *mainLayout;
//	LoginDialog *loginWindow;
//	RegisterDialog *registerWindow;
	GameWidget *gameWidget;
	SimplifiedUserInfoWidget *simplifiedUserInfoWidget;

	Player *player;
	Questioner *questioner;
	DatabaseServer DBServer;
};

#endif // MAINWINDOW_H
