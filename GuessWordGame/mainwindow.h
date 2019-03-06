#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "logindialog.h"
#include"gamewidget.h"
#include"registerdialog.h"
#include"simplifieduserinfowidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();


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
};

#endif // MAINWINDOW_H
