#include "registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent): QWidget(parent)
{
	createLabel();
	createLayout();
	createConnection();
}

void RegisterDialog::createLabel()
{
	userNameLabel = new QLabel(tr("用户名"));
	userNameLineEdit = new QLineEdit();
	passwordLabel = new QLabel(tr("密码"));
	passwordLineEdit = new QLineEdit();
	recheckPasswordLabel = new QLabel(tr("确认密码"));
	recheckPasswordLineEdit = new QLineEdit();

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

}
