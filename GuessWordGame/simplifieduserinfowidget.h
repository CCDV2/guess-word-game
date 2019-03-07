#ifndef SIMPLIFIEDUSERINFOWIDGET_H
#define SIMPLIFIEDUSERINFOWIDGET_H

#include <QWidget>
#include<QLabel>
#include<QProgressBar>
#include<QPushButton>
#include<QPixmap>
#include<QGridLayout>
#include<QStackedWidget>
#include"user.h"
#include"loginorregisterdialog.h"
#include"databaseserver.h"

class SimplifiedUserInfoWidget: public QWidget
{
	Q_OBJECT
public:
	SimplifiedUserInfoWidget(DatabaseServer &_DBServer, QWidget *parent = nullptr);

	QPushButton *getLoginOrRegisterButton() const;

	LoginOrRegisterDialog *getLoginOrRegisterDialog() const;

	void showUserInfo(Player player, Questioner questioner);
public slots:

private slots:
	void showLoginOrRegisterWindow();
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QLabel *userNameLabel, *levelLabel, *mainUserStateLabel;
	QProgressBar *levelBar;
	QPushButton *loginOrRegisterButton;
	QPixmap *avatorPixmap;
	QStackedWidget *stateOrButtonWidget;

	LoginOrRegisterDialog *loginOrRegisterDialog;

	QGridLayout *mainLayout;
	DatabaseServer &DBserver;
};

#endif // SIMPLIFIEDUSERINFOWIDGET_H
