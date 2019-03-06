#include "simplifieduserinfowidget.h"
#include<QDebug>

SimplifiedUserInfoWidget::SimplifiedUserInfoWidget(QWidget *parent): QWidget(parent)
{
	createWidget();
	createLayout();
	createConnection();
}

void SimplifiedUserInfoWidget::resetUserInfo(QString &userName, int level, int experience)
{
	userNameLabel->setText(userName);
	levelLabel->setText(tr("Lv ") + QString::number(level));

	// TODO
	levelBar->setMaximum(100);
	levelBar->setValue(experience);
	levelBar->setVisible(true);
}

void SimplifiedUserInfoWidget::showLoginOrRegisterWindow()
{
//	qDebug() << "connected";
	loginOrRegisterDialog = new LoginOrRegisterDialog(this);
	loginOrRegisterDialog->exec();
}

void SimplifiedUserInfoWidget::createWidget()
{
	userNameLabel = new QLabel(tr("游客"));
	loginOrRegisterButton = new QPushButton(tr("登录/注册"));
	mainUserStateLabel = new QLabel();

	stateOrButtonWidget = new QStackedWidget();
	stateOrButtonWidget->addWidget(loginOrRegisterButton);
	stateOrButtonWidget->addWidget(mainUserStateLabel);

	levelLabel = new QLabel();
	levelBar = new QProgressBar();
	levelBar->setVisible(false);
	avatorPixmap = new QPixmap();
}

void SimplifiedUserInfoWidget::createLayout()
{
	mainLayout = new QGridLayout(this);

	mainLayout->addWidget(userNameLabel, 0, 0);
	mainLayout->addWidget(stateOrButtonWidget, 0, 1);
	mainLayout->addWidget(levelLabel, 1, 0);
	mainLayout->addWidget(levelBar, 1, 1);
}

void SimplifiedUserInfoWidget::createConnection()
{
	connect(loginOrRegisterButton, &QPushButton::clicked,
			this, &SimplifiedUserInfoWidget::showLoginOrRegisterWindow)
;}

QPushButton *SimplifiedUserInfoWidget::getLoginOrRegisterButton() const
{
	return loginOrRegisterButton;
}



