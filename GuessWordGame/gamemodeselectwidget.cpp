#include "gamemodeselectwidget.h"

GameModeSelectWidget::GameModeSelectWidget(QWidget *parent):
	QWidget(parent)
{
	createWidget();
	createLayout();
	createConnection();
}

void GameModeSelectWidget::on_easyButton_clicked()
{
	emit sendGameMode(EASY);
}

void GameModeSelectWidget::on_normalButton_clicked()
{
	emit sendGameMode(NORMAL);
}

void GameModeSelectWidget::on_hardButton_clicked()
{
	emit sendGameMode(HARD);
}

void GameModeSelectWidget::on_expertButton_clicked()
{
	emit sendGameMode(EXPERT);
}

void GameModeSelectWidget::createWidget()
{
	modeSelectLabel = new QLabel(tr("请选择游戏难度"));
	easyButton = new QPushButton(tr("EASY"));
	normalButton = new QPushButton(tr("NORMAL"));
	hardButton = new QPushButton(tr("HARD"));
	expertButton = new QPushButton(tr("EXPERT"));
}

void GameModeSelectWidget::createLayout()
{
	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(modeSelectLabel, 0, 0, 1, 2, Qt::AlignCenter);
	mainLayout->addWidget(easyButton, 1, 0);
	mainLayout->addWidget(normalButton, 1, 1);
	mainLayout->addWidget(hardButton, 2, 0);
	mainLayout->addWidget(expertButton, 2, 1);
}

void GameModeSelectWidget::createConnection()
{
	connect(easyButton, &QPushButton::clicked, this, &GameModeSelectWidget::on_easyButton_clicked);
	connect(normalButton, &QPushButton::clicked, this, &GameModeSelectWidget::on_normalButton_clicked);
	connect(hardButton, &QPushButton::clicked, this, &GameModeSelectWidget::on_hardButton_clicked);
	connect(expertButton, &QPushButton::clicked, this, &GameModeSelectWidget::on_expertButton_clicked);
}
