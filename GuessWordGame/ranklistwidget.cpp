#include "ranklistwidget.h"

RanklistWidget::RanklistWidget(DatabaseServer &_DBserver, QWidget *parent):
	QWidget(parent), DBserver(_DBserver)
{
	createWidget();
	createLayout();
	createConnection();
}

void RanklistWidget::receiveRanklist(QVector<Player> players, QVector<Questioner> questioners, bool isPlayerList)
{
	if(isPlayerList)
	{

	}
	else // questioner list
	{

	}
}

void RanklistWidget::on_searchPlayerButton_clicked()
{
	emit requestRanklist(true);
}

void RanklistWidget::on_searchQuestionerButton_clicked()
{
	emit requestRanklist(false);
}

void RanklistWidget::createWidget()
{
	searchPlayerButton = new QPushButton(tr("玩家榜"));
	searchQuestionerButton = new QPushButton(tr("出题榜"));
	tableWidget = new QTableWidget();
}

void RanklistWidget::createLayout()
{
	buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(searchPlayerButton);
	buttonLayout->addWidget(searchQuestionerButton);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addLayout(buttonLayout);
	mainLayout->addWidget(tableWidget);
}

void RanklistWidget::createConnection()
{
	connect(searchPlayerButton, &QPushButton::clicked, this, &RanklistWidget::on_searchPlayerButton_clicked);
	connect(searchQuestionerButton, &QPushButton::clicked, this, &RanklistWidget::on_searchQuestionerButton_clicked);

	connect(this, &RanklistWidget::requestRanklist, &DBserver, &DatabaseServer::receiveRanklistRequest);
	connect(&DBserver, &DatabaseServer::sendRanklist, this, &RanklistWidget::receiveRanklist);
}

