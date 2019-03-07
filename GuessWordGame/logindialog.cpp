#include "logindialog.h"
#include "datastructure.h"
#include"databaseserver.h"
#include<QMessageBox>

LoginDialog::LoginDialog(DatabaseServer &_DBserver, QWidget *parent) :
	QDialog(parent), DBserver(_DBserver)
{
	createWidget();
	createLayout();
	createConnection();
}

void LoginDialog::receiveLoginState(LoginState state)
{
	switch(state)
	{
	case LOGIN_SUCCESS:
		accepted();
		break;
	case WRONG_PASSWORD:
		QMessageBox::warning(this, tr("密码错误"), tr("密码错误，请重新输入密码"));
		passWordLineEdit->setFocus();
		break;
	case UNFOUND_USERNAME:
		QMessageBox::warning(this, tr("未找到用户"), tr("该用户未被注册"));
		userNameLineEdit->setFocus();
		break;
	}
}

void LoginDialog::createWidget()
{
	userNameLineEdit = new QLineEdit();
	userNameLabel = new QLabel(tr("用户名"));
	passWordLineEdit = new QLineEdit();
	passWordLineEdit->setEchoMode(QLineEdit::Password);
	passWordLabel = new QLabel(tr("密码"));
	submitButton = new QPushButton(tr("登录"));
	cancelButton = new QPushButton(tr("取消"));
}

void LoginDialog::createLayout()
{
	loginWindowLayout = new QGridLayout(this);
	loginWindowLayout->addWidget(userNameLabel, 0, 0);
	loginWindowLayout->addWidget(userNameLineEdit, 0, 1);
	loginWindowLayout->addWidget(passWordLabel, 1, 0);
	loginWindowLayout->addWidget(passWordLineEdit, 1, 1);

	buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(submitButton);
	buttonLayout->addWidget(cancelButton);

	loginWindowLayout->addLayout(buttonLayout, 2, 0, 1, 2, Qt::AlignCenter);

	setLayout(loginWindowLayout);

//	setFixedSize(this->size());

}

void LoginDialog::createConnection()
{
	connect(submitButton, &QPushButton::clicked, this, &LoginDialog::on_submitButton_clicked);
	connect(cancelButton, &QPushButton::clicked, this, &LoginDialog::reject);
	connect(this, &LoginDialog::sendLoginPackage, &DBserver, &DatabaseServer::receiveLoginPackage);
	connect(&DBserver, &DatabaseServer::sendLoginState, this, &LoginDialog::receiveLoginState);
}


void LoginDialog::on_submitButton_clicked()
{
	LoginPackage loginPackage = LoginPackage(userNameLineEdit->text(), passWordLineEdit->text());

	// has empty username
	if(loginPackage.userName.isEmpty())
	{
		QMessageBox::information(this, tr("请输入用户名"), tr("请先输入用户名再登录"));
		userNameLineEdit->setFocus();
	}
	else
	{
		// has empty password
		if(loginPackage.passWord.isEmpty())
		{
			QMessageBox::information(this, tr("请输入密码"), tr("请先输入密码再登录"));
			passWordLineEdit->setFocus();
		}
		else // check valid
		{
			emit sendLoginPackage(loginPackage);
		}
	}
}

void LoginDialog::on_cancelButton_clicked()
{
//	rejected();
}

LoginState LoginDialog::checkLoginState(const LoginPackage &loginPackage)
{
	// TODO
	return DatabaseServer::checkLoginState(loginPackage);
}

QPushButton *LoginDialog::getSubmitButton() const
{
	return submitButton;
}
