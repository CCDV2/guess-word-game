#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>
#include<QTreeWidget>
#include<QLabel>
#include<QVBoxLayout>

class FriendWidget: public QWidget
{
	Q_OBJECT
public:
	FriendWidget(QWidget *parent = nullptr);
public slots:
	void refreshFriendStatus(QVector<QString> onlineFriends, QVector<QString> offlineFriends, QVector<QString> friendRequests);

private slots:
	void on_item_clicked(QTreeWidgetItem *item, int column);
	void on_item_doubleclicked(QTreeWidgetItem *item, int column);
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QTreeWidget *treeWidget;
	QTreeWidgetItem *onlineFriendItem, *offlineFriendItem, *friendRequestItem;
	QVBoxLayout *mainLayout;
};

#endif // FRIENDWIDGET_H
