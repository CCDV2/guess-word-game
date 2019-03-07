#include "loginorregisterdialog.h"

LoginOrRegisterDialog::LoginOrRegisterDialog(DatabaseServer &_DBserver, QWidget *parent):
	QDialog(parent), DBserver(_DBserver)
{
	isInLoginDialog = true;
	createWidget();
	createLayout();
	createConnection();
}

void LoginOrRegisterDialog::showLoginDialog()
{
	if(!isInLoginDialog)
	{
		stackWidget->setCurrentWidget(loginDialog);
		isInLoginDialog = true;
	}
}

void LoginOrRegisterDialog::showRegisterDialog()
{
	if(isInLoginDialog)
	{
		stackWidget->setCurrentWidget(registerDialog);
		isInLoginDialog = false;
	}
}

void LoginOrRegisterDialog::createWidget()
{
	loginButton = new QPushButton(tr("登录"));
	registerButton = new QPushButton(tr("注册"));
	loginDialog = new LoginDialog(DBserver);
	registerDialog = new RegisterDialog();
	stackWidget = new QStackedWidget();
	stackWidget->addWidget(loginDialog);
	stackWidget->addWidget(registerDialog);
}

void LoginOrRegisterDialog::createLayout()
{
	setWindowFlag(Qt::FramelessWindowHint);
	switchButtonLayout = new QHBoxLayout();
	switchButtonLayout->addWidget(loginButton);
	switchButtonLayout->addWidget(registerButton);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addLayout(switchButtonLayout);
	mainLayout->addWidget(stackWidget);
}

void LoginOrRegisterDialog::createConnection()
{
	connect(loginButton, &QPushButton::clicked, this, &LoginOrRegisterDialog::showLoginDialog);
	connect(registerButton, &QPushButton::clicked, this, &LoginOrRegisterDialog::showRegisterDialog);
	connect(loginDialog, &LoginDialog::rejected, this, &LoginOrRegisterDialog::reject);
	connect(registerDialog, &RegisterDialog::rejected, this, &LoginOrRegisterDialog::reject);
	connect(loginDialog, &LoginDialog::accepted, this, &LoginOrRegisterDialog::accept);
}

LoginDialog *LoginOrRegisterDialog::getLoginDialog() const
{
	return loginDialog;
}
