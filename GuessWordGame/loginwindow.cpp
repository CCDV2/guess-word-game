#include "loginwindow.h"
#include <QVBoxLayout>


LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
	userName = new QLineEdit(this);
	passWord = new QLineEdit(this);
	submitButton = new QPushButton(this);

	QVBoxLayout *loginWindowLayout = new QVBoxLayout(this);
	loginWindowLayout->addWidget(userName);
	loginWindowLayout->addWidget(passWord);
	loginWindowLayout->addWidget(submitButton);

	setLayout(loginWindowLayout);
}
