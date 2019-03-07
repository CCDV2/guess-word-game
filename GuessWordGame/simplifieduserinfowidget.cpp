#include "simplifieduserinfowidget.h"
#include<QDebug>

SimplifiedUserInfoWidget::SimplifiedUserInfoWidget(DatabaseServer &_DBserver, QWidget *parent):
	QWidget(parent), DBserver(_DBserver)
{
	createWidget();
	createLayout();
	createConnection();
}


void SimplifiedUserInfoWidget::showLoginOrRegisterWindow()
{
//	qDebug() << "connected";
	loginOrRegisterDialog = new LoginOrRegisterDialog(DBserver, this);
	loginOrRegisterDialog->exec();
}

void SimplifiedUserInfoWidget::showUserInfo(Player player, Questioner questioner)
{
	userNameLabel->setText(player.getUserName());
	loginOrRegisterButton->setVisible(false);
	stateOrButtonWidget->setCurrentWidget(mainUserStateLabel);
	levelLabel->setVisible(true);
	levelBar->setVisible(true);
	levelBar->setMaximum(100);
	int currentExp;
	if(player.getLevel() >= questioner.getLevel())
	{
		mainUserStateLabel->setText(tr("主业：挑战者"));
		levelLabel->setText(tr("Lv. %1").arg(player.getLevel()));
		currentExp = player.getExperience();
	}
	else
	{
		mainUserStateLabel->setText(tr("主业：出题者"));
		levelLabel->setText(tr("Lv. %1").arg(questioner.getLevel()));
		currentExp = player.getExperience();
	}
	for(int i = 0; i <= currentExp; ++i)
	{
		levelBar->setValue(i);
	}
}

void SimplifiedUserInfoWidget::createWidget()
{
	userNameLabel = new QLabel(tr("游客"));
	loginOrRegisterButton = new QPushButton(tr("登录/注册"));
	mainUserStateLabel = new QLabel();

	stateOrButtonWidget = new QStackedWidget();
	stateOrButtonWidget->addWidget(loginOrRegisterButton);
	stateOrButtonWidget->addWidget(mainUserStateLabel);

	levelLabel = new QLabel(tr("Lv"));
	levelLabel->setVisible(false);
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
			this, &SimplifiedUserInfoWidget::showLoginOrRegisterWindow);

}

LoginOrRegisterDialog *SimplifiedUserInfoWidget::getLoginOrRegisterDialog() const
{
	return loginOrRegisterDialog;
}

QPushButton *SimplifiedUserInfoWidget::getLoginOrRegisterButton() const
{
	return loginOrRegisterButton;
}



