#include "onlineuserwidget.h"
#include<QDebug>
#include<QTreeWidgetItem>
#include<QMessageBox>
#include<QPainter>

OnlineUserWidget::OnlineUserWidget(DatabaseServer &_DBserver, QWidget *parent):
	QWidget(parent), DBserver(_DBserver)
{
	isLogin = false;
	createWidget();
	createLayout();
	createConnection();
}

void OnlineUserWidget::receiveOnlineUsers(QVector<QString> users)
{
	onlineUserItem->takeChildren();
	for(auto user : users)
	{
		if(user.isEmpty()) continue;
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, user);
		onlineUserItem->addChild(item);
	}
}

void OnlineUserWidget::receiveOnlineDetailInfo(Player player, Questioner questoiner)
{
	DetailedUserInfoDialog *dialog = new DetailedUserInfoDialog(player, questoiner, DBserver, ONLINE_OPEN);
	connect(dialog, &DetailedUserInfoDialog::sendGameMode, this, &OnlineUserWidget::receiveGameMode);
	dialog->exec();
}




void OnlineUserWidget::on_item_clicked(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column);
	if(!isLogin)
	{
		QMessageBox::information(this, tr("请先登录"), tr("请先登录再查看在线玩家"), QMessageBox::Ok);
	}
	else
	{
		if(item->parent() == nullptr)
		{
			emit sendOnlineUserRequest();
		}
	}
}

void OnlineUserWidget::on_item_doubleclicked(QTreeWidgetItem *item, int column)
{
	// It's not a top item. i.e. It's someone's name.
	if(!isLogin)
	{
		QMessageBox::information(this, tr("请先登录"), tr("请先登录再查看在线玩家"), QMessageBox::Ok);
	}
	else
	{
		if(item->parent() != nullptr)
		{
			QString name = item->text(column);
			if(name.isEmpty()) return;
			emit sendOnlineDetailInfoRequest(name);
		}
	}
}

void OnlineUserWidget::receiveGameMode(GameLevel level, GameStatus status, bool needSignal)
{
	emit sendGameMode(level, status, needSignal);
}

void OnlineUserWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption styleOpt;
	styleOpt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}


void OnlineUserWidget::createWidget()
{
	treeWidget = new QTreeWidget();
	treeWidget->setHeaderHidden(true);

	onlineUserItem = new QTreeWidgetItem(treeWidget);
	onlineUserItem->setText(0, tr("在线玩家"));
}

void OnlineUserWidget::createLayout()
{
	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(treeWidget);
}

void OnlineUserWidget::createConnection()
{
	connect(treeWidget, &QTreeWidget::itemClicked, this, &OnlineUserWidget::on_item_clicked);
	connect(treeWidget, &QTreeWidget::itemDoubleClicked, this, &OnlineUserWidget::on_item_doubleclicked);
#ifdef USE_NETWORK
	connect(this, &OnlineUserWidget::sendOnlineUserRequest, &DBserver, &DatabaseServer::receiveOnlineUserRequest);
	connect(&DBserver, &DatabaseServer::sendOnlineUsers, this, &OnlineUserWidget::receiveOnlineUsers);
	connect(this, &OnlineUserWidget::sendOnlineDetailInfoRequest, &DBserver, &DatabaseServer::receiveOnlineUserDetailInfoRequest);
	connect(&DBserver, &DatabaseServer::sendOnlineUserDetail, this, &OnlineUserWidget::receiveOnlineDetailInfo);
#endif
}

void OnlineUserWidget::setIsLogin(bool value)
{
	isLogin = value;
}
