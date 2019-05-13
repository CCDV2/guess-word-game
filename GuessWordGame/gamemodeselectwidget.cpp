#include "gamemodeselectwidget.h"
#include<QStyleOption>
#include<QPainter>


GameModeSelectWidget::GameModeSelectWidget(QWidget *parent):
	QWidget(parent)
{
	createWidget();
	createLayout();
	createConnection();
}

void GameModeSelectWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption styleOpt;
	styleOpt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void GameModeSelectWidget::on_easyButton_clicked()
{
	emit sendGameMode(EASY, status, true);
}

void GameModeSelectWidget::on_normalButton_clicked()
{
	emit sendGameMode(NORMAL, status, true);
}

void GameModeSelectWidget::on_hardButton_clicked()
{
	emit sendGameMode(HARD, status, true);
}

void GameModeSelectWidget::on_expertButton_clicked()
{
	emit sendGameMode(EXPERT, status, true);
}

void GameModeSelectWidget::changeStateText()
{
	if(duoCheckBox->isChecked())
	{
		status = GAME_DUO;
		duoStateLabel->setText(tr("双人匹配：开启"));
	}
	else
	{
		status = GAME_SINGLE;
		duoStateLabel->setText(tr("双人匹配：关闭"));
	}
}

void GameModeSelectWidget::createWidget()
{
	duoSelectLabel = new QLabel(tr("请选择游戏模式"));
	duoStateLabel = new QLabel(tr("双人匹配：关闭"));
	duoCheckBox = new QCheckBox();
	duoCheckBox->setCheckState(Qt::Unchecked);
	status = GAME_SINGLE;
	modeSelectLabel = new QLabel(tr("请选择游戏难度"));
	easyButton = new QPushButton(tr("EASY"));
//	easyButton->setObjectName(levelButtonName);
	normalButton = new QPushButton(tr("NORMAL"));
//	normalButton->setObjectName(levelButtonName);
	hardButton = new QPushButton(tr("HARD"));
//	hardButton->setObjectName(levelButtonName);
	expertButton = new QPushButton(tr("EXPERT"));
//	expertButton->setObjectName(levelButtonName);
}

void GameModeSelectWidget::createLayout()
{
	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(duoSelectLabel, 0, 0, 1, 2, Qt::AlignCenter | Qt::AlignBottom);
	mainLayout->addWidget(duoCheckBox, 1, 0, Qt::AlignRight | Qt::AlignTop);
	mainLayout->addWidget(duoStateLabel, 1, 1, Qt::AlignLeft | Qt::AlignTop);
	mainLayout->addWidget(modeSelectLabel, 2, 0, 1, 2, Qt::AlignCenter | Qt::AlignBottom);
	mainLayout->addWidget(easyButton, 3, 0);
	mainLayout->addWidget(normalButton, 3, 1);
	mainLayout->addWidget(hardButton, 4, 0);
	mainLayout->addWidget(expertButton, 4, 1);
	mainLayout->addItem(new QSpacerItem(50, 10), 5, 0, 1, 2);

	mainLayout->setRowStretch(0, 3);
	mainLayout->setRowStretch(1, 1);
	mainLayout->setRowStretch(2, 2);
	mainLayout->setRowStretch(3, 1);
	mainLayout->setRowStretch(4, 1);
	mainLayout->setRowStretch(5, 3);
	mainLayout->setMargin(this->size().width() / 5);

	mainLayout->setColumnStretch(0, 1);
	mainLayout->setColumnStretch(1, 1);
}

void GameModeSelectWidget::createConnection()
{
	connect(easyButton, &QPushButton::clicked, this, &GameModeSelectWidget::on_easyButton_clicked);
	connect(normalButton, &QPushButton::clicked, this, &GameModeSelectWidget::on_normalButton_clicked);
	connect(hardButton, &QPushButton::clicked, this, &GameModeSelectWidget::on_hardButton_clicked);
	connect(expertButton, &QPushButton::clicked, this, &GameModeSelectWidget::on_expertButton_clicked);

	connect(duoCheckBox, &QCheckBox::clicked, this, &GameModeSelectWidget::changeStateText);
}
