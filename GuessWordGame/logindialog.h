#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include"datastructure.h"
#include <QWidget>
#include<QDialog>
#include <QLineEdit>
#include <QPushButton>
#include<QLabel>
#include<QGridLayout>
#include<QHBoxLayout>
#include"databaseserver.h"


class LoginDialog : public QDialog
{
	Q_OBJECT
public:
	explicit LoginDialog(DatabaseServer &_DBserver, QWidget *parent = nullptr);

	QPushButton *getSubmitButton() const;

signals:
	void sendLoginPackage(LoginPackage loginPackage);
public slots:
	void receiveLoginState(LoginState state);


private slots:
	void on_submitButton_clicked();
	void on_cancelButton_clicked();
	void resetSentStatus();
private:
	void createWidget();
	void createLayout();
	void createConnection();

	LoginState checkLoginState(const LoginPackage &loginPackage);

	QLineEdit *userNameLineEdit, *passWordLineEdit;
	QLabel *userNameLabel, *passWordLabel;
	QPushButton *submitButton, *cancelButton;
	QGridLayout *loginWindowLayout;
	QHBoxLayout *buttonLayout;

	DatabaseServer &DBserver;
	bool isLoginSent;
};

#endif // LOGINWINDOW_H
