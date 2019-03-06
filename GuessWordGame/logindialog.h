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

class LoginDialog : public QDialog
{
	Q_OBJECT
public:
	explicit LoginDialog(QWidget *parent = nullptr);

signals:

private slots:
	void on_submitButton_clicked();
	void on_cancelButton_clicked();
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
};

#endif // LOGINWINDOW_H
