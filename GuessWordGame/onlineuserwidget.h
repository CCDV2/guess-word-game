#ifndef ONLINEUSERWIDGET_H
#define ONLINEUSERWIDGET_H

#include <QWidget>
#include<QTreeWidget>
#include<QLabel>
#include<QVBoxLayout>
#include"detaileduserinfodialog.h"
#include"databaseserver.h"

class OnlineUserWidget: public QWidget
{
	Q_OBJECT
public:
	OnlineUserWidget(DatabaseServer &_DBserver, QWidget *parent = nullptr);
	void setIsLogin(bool value);

signals:
	void sendOnlineUserRequest();
	void sendOnlineDetailInfoRequest(QString user);
	void sendGameMode(GameLevel level, GameStatus status, bool needSignal);
public slots:
	void receiveOnlineUsers(QVector<QString> users);
	void receiveOnlineDetailInfo(Player player, Questioner questoiner);
private slots:
	void on_item_clicked(QTreeWidgetItem *item, int column);
	void on_item_doubleclicked(QTreeWidgetItem *item, int column);

	void receiveGameMode(GameLevel level, GameStatus status, bool needSignal);
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QTreeWidget *treeWidget;
	QTreeWidgetItem *onlineUserItem;
	QVBoxLayout *mainLayout;
	DatabaseServer &DBserver;
	bool isLogin;
};

#endif // ONLINEUSERWIDGET_H
