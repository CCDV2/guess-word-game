#include "detaileduserinfodialog.h"
#include"datastructure.h"


DetailedUserInfoDialog::DetailedUserInfoDialog(Player player, Questioner questioner, QWidget *parent):
	QDialog(parent)
{
	// widget
	userNameLabel = new QLabel(player.getUserName());
	playerNameLabel = new QLabel(tr("挑战者"));
	playerLevelLabel = new QLabel(tr("Lv. %1").arg(player.getLevel()));
	playerNumLabel = new QLabel(tr("已闯关关卡数: %1").arg(player.getPlayNum()));
	playerBar = new QProgressBar();
	playerBar->setObjectName(levelBarName);
	playerBar->setMaximum(getLevelMaxExp(player.getLevel()));
	playerBar->setValue(player.getExperience());
	playerBar->setFormat(tr("%1/%2").arg(player.getExperience()).arg(getLevelMaxExp(player.getLevel())));

	questionerNameLabel = new QLabel(tr("出题者"));
	questionerLevelLabel = new QLabel(tr("Lv. %1").arg(questioner.getLevel()));
	questionerNumLabel = new QLabel(tr("已出题题数: %1").arg(questioner.getQuestionNum()));
	questionerBar = new QProgressBar();
	questionerBar->setObjectName(levelBarName);
	questionerBar->setMaximum(getLevelMaxExp(questioner.getLevel()));
	questionerBar->setValue(questioner.getExperience());
	questionerBar->setFormat(tr("%1/%2").arg(questioner.getExperience()).arg(getLevelMaxExp(questioner.getLevel())));

	// layout
	playerLayout = new QGridLayout();
	playerLayout->addWidget(playerLevelLabel, 0, 0);
	playerLayout->addWidget(playerBar, 0, 1);
	playerLayout->addWidget(playerNumLabel, 1, 0);

	questionerLayout = new QGridLayout();
	questionerLayout->addWidget(questionerLevelLabel, 0, 0);
	questionerLayout->addWidget(questionerBar, 0, 1);
	questionerLayout->addWidget(questionerNumLabel, 1, 0);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(userNameLabel, 0, Qt::AlignCenter);
	mainLayout->addWidget(playerNameLabel, 0, Qt::AlignLeft);
	mainLayout->addLayout(playerLayout);
	mainLayout->addWidget(questionerNameLabel, 0, Qt::AlignLeft);
	mainLayout->addLayout(questionerLayout);
}

