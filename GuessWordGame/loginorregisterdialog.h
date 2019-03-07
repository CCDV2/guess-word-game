#ifndef LOGINORREGISTERDIALOG_H
#define LOGINORREGISTERDIALOG_H

#include <QWidget>
#include"logindialog.h"
#include"registerdialog.h"
#include<QStackedWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"databaseserver.h"

class LoginOrRegisterDialog: public QDialog
{
public:
	LoginOrRegisterDialog(DatabaseServer &_DBServer, QWidget *parent = nullptr);
	LoginDialog *getLoginDialog() const;

private slots:
	void showLoginDialog();
	void showRegisterDialog();

private:
	void createWidget();
	void createLayout();
	void createConnection();

	LoginDialog *loginDialog;
	RegisterDialog *registerDialog;
	QStackedWidget *stackWidget;
	QPushButton *loginButton, *registerButton;

	QVBoxLayout *mainLayout;
	QHBoxLayout *switchButtonLayout;

	bool isInLoginDialog;

	DatabaseServer &DBserver;
};

#endif // LOGINORREGISTERDIALOG_H
