#ifndef SIMPLIFIEDUSERINFOWIDGET_H
#define SIMPLIFIEDUSERINFOWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QProgressBar>
#include<QPushButton>
#include<QPixmap>
#include<QGridLayout>
#include<QStackedWidget>
#include<QStackedLayout>
#include<QMouseEvent>
#include<QHBoxLayout>
#include"user.h"
#include"loginorregisterdialog.h"
#include"databaseserver.h"
#include"detaileduserinfodialog.h"

class SimplifiedUserInfoWidget: public QWidget
{
	Q_OBJECT
public:
	SimplifiedUserInfoWidget(DatabaseServer &_DBServer, QWidget *parent = nullptr);

	QPushButton *getLoginOrRegisterButton() const;

	LoginOrRegisterDialog *getLoginOrRegisterDialog() const;

	void showUserInfo(Player player, Questioner questioner);
signals:
	void requireUserInfo();
public slots:
	void receiveUserInfo(Player player, Questioner questioner);
private slots:
	void showLoginOrRegisterWindow();
	void showDetailedInfo();
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QLabel *userNameLabel, *levelLabel, *mainUserStateLabel;
	QProgressBar *levelBar;
	QPushButton *loginOrRegisterButton, *showDetailButton;
	QPixmap *avatorPixmap;
	QStackedWidget *stateOrButtonWidget;
	QWidget *stateWidget;
	QHBoxLayout *stateLayout;

	LoginOrRegisterDialog *loginOrRegisterDialog;

	QGridLayout *mainLayout;
	DatabaseServer &DBserver;
};

#endif // SIMPLIFIEDUSERINFOWIDGET_H
