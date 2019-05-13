#include "ranklistwidget.h"
#include<QHeaderView>
#include<QAbstractItemView>
#include<QStyleOption>
#include<QPainter>

RanklistWidget::RanklistWidget(DatabaseServer &_DBserver, QWidget *parent):
	QWidget(parent), DBserver(_DBserver)
{
	currentMethod = NULL_SORT;
	createWidget();
	createLayout();
	createConnection();
}

void RanklistWidget::receiveRanklist(QVector<Player> players, QVector<Questioner> questioners, SortMethod sortMethod)
{
	qDebug() << "ranklist received";
	tableWidget->setColumnCount(3);
	switch(sortMethod)
	{
	// initial state, should not be received
	case NULL_SORT:
		qDebug() << "error receiving NULL_SORT";
		break;
	// player part
	case PLAYER_LEVEL_DESC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名"), tr("等级▼"), tr("做题数")});
		showTableByPlayer(players);
		break;
	case PLAYER_LEVEL_ASC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名"), tr("等级▲"), tr("做题数")});
		showTableByPlayer(players);
		break;
	case PLAYER_NAME_DESC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名▼"), tr("等级"), tr("做题数")});
		showTableByPlayer(players);
		break;
	case PLAYER_NAME_ASC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名▲"), tr("等级"), tr("做题数")});
		showTableByPlayer(players);
		break;
	case PLAYER_NUM_DESC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名"), tr("等级"), tr("做题数▼")});
		showTableByPlayer(players);
		break;
	case PLAYER_NUM_ASC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名"), tr("等级"), tr("做题数▲")});
		showTableByPlayer(players);
		break;
	// questioner part
	case QUESTIONER_LEVEL_DESC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名"), tr("等级▼"), tr("出题数")});
		showTableByQuestioner(questioners);
		break;
	case QUESTIONER_LEVEL_ASC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名"), tr("等级▲"), tr("出题数")});
		showTableByQuestioner(questioners);
		break;
	case QUESTIONER_NAME_DESC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名▼"), tr("等级"), tr("出题数")});
		showTableByQuestioner(questioners);
		break;
	case QUESTIONER_NAME_ASC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名▲"), tr("等级"), tr("出题数")});
		showTableByQuestioner(questioners);
		break;
	case QUESTIONER_NUM_DESC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名"), tr("等级"), tr("出题数▼")});
		showTableByQuestioner(questioners);
		break;
	case QUESTIONER_NUM_ASC:
		tableWidget->setHorizontalHeaderLabels({tr("用户名"), tr("等级"), tr("出题数▲")});
		showTableByQuestioner(questioners);
		break;
	}
}

void RanklistWidget::receiveDetailInfo(Player player, Questioner questioner)
{
	DetailedUserInfoDialog *detailDialog;
	if(player.getUserName() == userName)
	{
		detailDialog = new DetailedUserInfoDialog(player, questioner, DBserver, MYSELF_OPEN);
	}
	else
	{
		detailDialog = new DetailedUserInfoDialog(player, questioner, DBserver, RANKLIST_OPEN);
		connect(detailDialog, &DetailedUserInfoDialog::sendGameMode, this, &RanklistWidget::receiveGameMode);
	}
	detailDialog->exec();
}

void RanklistWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption styleOpt;
	styleOpt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void RanklistWidget::on_searchPlayerButton_clicked()
{
	currentMethod = PLAYER_LEVEL_DESC;
	emit requestRanklist(currentMethod);
}

void RanklistWidget::on_searchQuestionerButton_clicked()
{
	currentMethod = QUESTIONER_LEVEL_DESC;
	emit requestRanklist(currentMethod);
}

void RanklistWidget::on_tableWidgetItem_doubleClicked(QTableWidgetItem *item)
{
	qDebug() << "clicked (" << item->row() << ',' << item->column() << ')';
	emit requestDetailInfo(currentMethod, item->row());
}

void RanklistWidget::on_header_clicked(int column)
{
	switch(column)
	{
	case 0:
		if(currentMethod <= PLAYER_NUM_ASC)
		{
			if(currentMethod == PLAYER_NAME_DESC) currentMethod = PLAYER_NAME_ASC;
			else currentMethod = PLAYER_NAME_DESC;
		}
		else
		{
			if(currentMethod == QUESTIONER_NAME_DESC) currentMethod = QUESTIONER_NAME_ASC;
			else currentMethod = QUESTIONER_NAME_DESC;
		}
		break;
	case 1:
		if(currentMethod <= PLAYER_NUM_ASC)
		{
			if(currentMethod == PLAYER_LEVEL_DESC) currentMethod = PLAYER_LEVEL_ASC;
			else currentMethod = PLAYER_LEVEL_DESC;
		}
		else
		{
			if(currentMethod == QUESTIONER_LEVEL_DESC) currentMethod = QUESTIONER_LEVEL_ASC;
			else currentMethod = QUESTIONER_LEVEL_DESC;
		}
		break;
	case 2:
		if(currentMethod <= PLAYER_NUM_ASC)
		{
			if(currentMethod == PLAYER_NUM_DESC) currentMethod = PLAYER_NUM_ASC;
			else currentMethod = PLAYER_NUM_DESC;
		}
		else
		{
			if(currentMethod == QUESTIONER_NUM_DESC) currentMethod = QUESTIONER_NUM_ASC;
			else currentMethod = QUESTIONER_NUM_DESC;
		}
		break;
	default:
		qDebug() << "unexpected column in header";
	}
	emit requestRanklist(currentMethod);
}

void RanklistWidget::receiveGameMode(GameLevel level, GameStatus status, bool needSignal)
{
	emit sendGameMode(level, status, needSignal);
}

void RanklistWidget::createWidget()
{
	searchPlayerButton = new QPushButton(tr("玩家榜"));
	searchQuestionerButton = new QPushButton(tr("出题榜"));
	tableWidget = new QTableWidget();
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//	tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:transparent;}");
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
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
	connect(this, &RanklistWidget::requestDetailInfo, &DBserver, &DatabaseServer::receiveDetailInfoRequest);
	connect(&DBserver, &DatabaseServer::sendDetailInfo, this, &RanklistWidget::receiveDetailInfo);

	connect(tableWidget, &QTableWidget::itemDoubleClicked, this, &RanklistWidget::on_tableWidgetItem_doubleClicked);
	connect(tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &RanklistWidget::on_header_clicked);
}

void RanklistWidget::showTableByPlayer(QVector<Player> &players)
{
	tableWidget->setRowCount(players.size());
	int cnt = 0;
	for(auto player : players)
	{
		tableWidget->setItem(cnt, 0, new QTableWidgetItem(player.getUserName()));
		tableWidget->setItem(cnt, 1, new QTableWidgetItem(tr("%1").arg(player.getLevel())));
		tableWidget->setItem(cnt, 2, new QTableWidgetItem(tr("%1").arg(player.getPlayNum())));
		++cnt;
	}
}

void RanklistWidget::showTableByQuestioner(QVector<Questioner> &questioners)
{
	tableWidget->setRowCount(questioners.size());
	int cnt = 0;
	for(auto questioner : questioners)
	{
		tableWidget->setItem(cnt, 0, new QTableWidgetItem(questioner.getUserName()));
		tableWidget->setItem(cnt, 1, new QTableWidgetItem(tr("%1").arg(questioner.getLevel())));
		tableWidget->setItem(cnt, 2, new QTableWidgetItem(tr("%1").arg(questioner.getQuestionNum())));
		++cnt;
	}
}

void RanklistWidget::setUserName(const QString &value)
{
	userName = value;
}

