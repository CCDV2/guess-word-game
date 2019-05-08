#include "friendwidget.h"
#include<QDebug>
#include<QTreeWidgetItem>

FriendWidget::FriendWidget(QWidget *parent):
	QWidget(parent)
{
	createWidget();
	createLayout();
	createConnection();
}

void FriendWidget::refreshFriendStatus(QVector<QString> onlineFriends, QVector<QString> offlineFriends, QVector<QString> friendRequests)
{
	onlineFriendItem->takeChildren();
	offlineFriendItem->takeChildren();
	friendRequestItem->takeChildren();
	for(auto onlineFriend : onlineFriends)
	{
		QTreeWidgetItem *temp = new QTreeWidgetItem();
		temp->setText(0, onlineFriend);
		onlineFriendItem->addChild(temp);
	}
	for(auto offlineFriend : offlineFriends)
	{
		QTreeWidgetItem *temp = new QTreeWidgetItem();
		temp->setText(0, offlineFriend);
		onlineFriendItem->addChild(temp);
	}
	for(auto friendRequest : friendRequests)
	{
		QTreeWidgetItem *temp = new QTreeWidgetItem();
		temp->setText(0, friendRequest);
		friendRequestItem->addChild(temp);
	}
}

void FriendWidget::on_item_clicked(QTreeWidgetItem *item, int column)
{
	if(item->text(column) == tr("在线好友"))
	{
		QTreeWidgetItem *test = new QTreeWidgetItem();
		test->setText(0, "abc");
		item->addChild(test);

		item->setExpanded(!item->isExpanded());
	}
	else if(item->text(column) == tr("离线好友"))
	{
		QTreeWidgetItem *test = new QTreeWidgetItem();
		test->setText(0, "def");
		item->addChild(test);

		item->setExpanded(!item->isExpanded());
	}
	else if(item->text(column) == tr("好友请求"))
	{

		QTreeWidgetItem *test = new QTreeWidgetItem();
		test->setText(0, "ghj");
		item->addChild(test);

		item->setExpanded(!item->isExpanded());
	}
	else
	{
		qDebug() << "not what we want";
	}
}

void FriendWidget::on_item_doubleclicked(QTreeWidgetItem *item, int column)
{
	// It's not a top item. i.e. It's someone's name.
	if(item->parent() != nullptr)
	{
		qDebug() << "catching " << item->text(column);
	}
}

void FriendWidget::createWidget()
{
	treeWidget = new QTreeWidget();
	treeWidget->setHeaderHidden(true);

	onlineFriendItem = new QTreeWidgetItem(treeWidget);
	onlineFriendItem->setText(0, tr("在线好友"));
	offlineFriendItem = new QTreeWidgetItem(treeWidget);
	offlineFriendItem->setText(0, tr("离线好友"));
	friendRequestItem = new QTreeWidgetItem(treeWidget);
	friendRequestItem->setText(0, tr("好友请求"));

//	treeWidget->addTopLevelItem(onlineFriendItem);
//	treeWidget->addTopLevelItem(offlineFriendItem);
//	treeWidget->addTopLevelItem(friendRequestItem);
}

void FriendWidget::createLayout()
{
	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(treeWidget);
}

void FriendWidget::createConnection()
{
	connect(treeWidget, &QTreeWidget::itemClicked, this, &FriendWidget::on_item_clicked);
	connect(treeWidget, &QTreeWidget::itemDoubleClicked, this, &FriendWidget::on_item_doubleclicked);
}
