#include "registerdialog.h"
#include<QMessageBox>

RegisterDialog::RegisterDialog(DatabaseServer &_DBserver, QWidget *parent):
	QDialog(parent), DBserver(_DBserver)
{
	createLabel();
	createLayout();
	createConnection();
}

void RegisterDialog::receiveRegisterState(RegisterState state)
{
	switch(state)
	{
	case REGISTER_SUCCESS:
		QMessageBox::information(this, tr("注册成功"), tr("注册成功，欢迎来玩游戏！"));
		accepted();
		close();
		break;
	case USER_EXISTED:
		QMessageBox::warning(this, tr("用户已存在"), tr("用户已存在，请起一个新的用户名"));
		userNameLineEdit->setFocus();
		break;
	}
}

void RegisterDialog::on_submitButton_clicked()
{
	const QString userName = userNameLineEdit->text();
	const QString password = passwordLineEdit->text();
	const QString recheckPassword = recheckPasswordLineEdit->text();
	if(userName.isEmpty())
	{
		QMessageBox::information(this, tr("请输入用户名"), tr("请先输入用户名再注册"));
		userNameLineEdit->setFocus();
	}
	else if(password.isEmpty())
	{
		QMessageBox::information(this, tr("请输入密码"), tr("请先输入密码再注册"));
		passwordLineEdit->setFocus();
	}
	else if(recheckPassword.isEmpty())
	{
		QMessageBox::information(this, tr("请输入确认密码"), tr("请先输入确认密码再注册"));
		passwordLineEdit->setFocus();
	}
	else
	{
		if(password != recheckPassword)
		{
			QMessageBox::warning(this, tr("密码错误"), tr("两次密码不一致，请重新输入"));
			passwordLineEdit->setFocus();
		}
		else
		{
			RegisterPackage package = LoginPackage(userName, password);
			emit sendRegisterPackage(package);
		}
	}

}

void RegisterDialog::createLabel()
{
	userNameLabel = new QLabel(tr("用户名"));
	userNameLineEdit = new QLineEdit();
	passwordLabel = new QLabel(tr("密码"));
	passwordLineEdit = new QLineEdit();
	passwordLineEdit->setEchoMode(QLineEdit::Password);
	recheckPasswordLabel = new QLabel(tr("确认密码"));
	recheckPasswordLineEdit = new QLineEdit();
	recheckPasswordLineEdit->setEchoMode(QLineEdit::Password);

	submitButton = new QPushButton(tr("注册"));
	cancelButton = new QPushButton(tr("取消"));
}

void RegisterDialog::createLayout()
{
	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(userNameLabel, 0, 0);
	mainLayout->addWidget(userNameLineEdit, 0, 1);
	mainLayout->addWidget(passwordLabel, 1, 0);
	mainLayout->addWidget(passwordLineEdit, 1, 1);
	mainLayout->addWidget(recheckPasswordLabel, 2, 0);
	mainLayout->addWidget(recheckPasswordLineEdit, 2, 1);

	buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(submitButton);
	buttonLayout->addWidget(cancelButton);

	mainLayout->addLayout(buttonLayout, 3, 0, 1, 2, Qt::AlignCenter);
}

void RegisterDialog::createConnection()
{
	connect(cancelButton, &QPushButton::clicked, this, &RegisterDialog::reject);
	connect(submitButton, &QPushButton::clicked, this, &RegisterDialog::on_submitButton_clicked);
	connect(this, &RegisterDialog::sendRegisterPackage, &DBserver, &DatabaseServer::receiveRegisterPackage);
	connect(&DBserver, &DatabaseServer::sendRegisterState, this, &RegisterDialog::receiveRegisterState);
}
