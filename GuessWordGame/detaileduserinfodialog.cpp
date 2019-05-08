#include "detaileduserinfodialog.h"
#include"datastructure.h"
#include<QPushButton>

DetailedUserInfoDialog::DetailedUserInfoDialog(Player _player, Questioner _questioner, DetailedWidgetArg _arg, QWidget *parent):
	QDialog(parent), player(_player), questioner(_questioner), arg(_arg)
{
	setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	createWidget();
	createLayout();
	createConnection();
}

void DetailedUserInfoDialog::createWidget()
{
	setWindowTitle(tr("玩家详情"));
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

	backButton = new QPushButton(tr("返回"));
	switch(arg)
	{
	case MYSELF:
		break;
	case FRIEND:
		matchButton = new QPushButton(tr("对战"));
		deleteFriendButton = new QPushButton(tr("删除"));
		break;
	case CHECKING_FRIEND:
		acceptFriendButton = new QPushButton(tr("接受"));
		rejectFriendButton = new QPushButton(tr("拒绝"));
		break;
	case ADDING_FRIEND:
		addFriendButton = new QPushButton(tr("添加"));
		break;
	}
}

void DetailedUserInfoDialog::createLayout()
{
	// layout
	mainLayout = new QGridLayout();
	mainLayout->setHorizontalSpacing(100);
	mainLayout->addWidget(userNameLabel, 0, 0, 1, 2, Qt::AlignCenter | Qt::AlignTop);

	mainLayout->addWidget(playerNameLabel, 1, 0, 1, 2, Qt::AlignLeft | Qt::AlignCenter);
	mainLayout->addWidget(playerLevelLabel, 2, 0, Qt::AlignBottom);
	mainLayout->addWidget(playerBar, 2, 1, Qt::AlignBottom);
	mainLayout->addWidget(playerNumLabel, 3, 0, 1, 2, Qt::AlignLeft | Qt::AlignTop);

	mainLayout->addWidget(new QLabel(tr("")), 4, 0, 1, 2);

	mainLayout->addWidget(questionerNameLabel, 5, 0, 1, 2, Qt::AlignLeft | Qt::AlignCenter);
	mainLayout->addWidget(questionerLevelLabel, 6, 0, Qt::AlignBottom);
	mainLayout->addWidget(questionerBar, 6, 1, Qt::AlignBottom);
	mainLayout->addWidget(questionerNumLabel, 7, 0, 1, 2, Qt::AlignLeft | Qt::AlignTop);


	buttonLayout = new QHBoxLayout();
	switch(arg)
	{
	case MYSELF:
		break;
	case FRIEND:
		buttonLayout->addWidget(matchButton, 0, Qt::AlignLeft);
		buttonLayout->addWidget(deleteFriendButton, 0, Qt::AlignCenter);
		break;
	case CHECKING_FRIEND:
		buttonLayout->addWidget(acceptFriendButton, 0, Qt::AlignLeft);
		buttonLayout->addWidget(rejectFriendButton, 0, Qt::AlignCenter);
		break;
	case ADDING_FRIEND:
		buttonLayout->addWidget(addFriendButton, 0, Qt::AlignLeft);
		break;
	}
	buttonLayout->addWidget(backButton, 0, Qt::AlignRight);

	mainLayout->addLayout(buttonLayout, 8, 0, 1, 2);

	mainLayout->setRowStretch(0, 1);
	mainLayout->setRowStretch(1, 2);
	mainLayout->setRowStretch(2, 2);
	mainLayout->setRowStretch(3, 2);
	mainLayout->setRowStretch(4, 2);
	mainLayout->setRowStretch(6, 2);
	mainLayout->setRowStretch(7, 2);

	setLayout(mainLayout);
}

void DetailedUserInfoDialog::createConnection()
{
	connect(backButton, &QPushButton::clicked, this, &DetailedUserInfoDialog::close);
	switch(arg)
	{
	case MYSELF:
		break;
	case FRIEND:
		break;
	case CHECKING_FRIEND:
		break;
	case ADDING_FRIEND:
		break;
	}
}

