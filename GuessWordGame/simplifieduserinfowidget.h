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

class SimplifiedUserInfoWidget: public QWidget
{
	Q_OBJECT
public:
	SimplifiedUserInfoWidget(QWidget *parent = nullptr);

	QPushButton *getLoginOrRegisterButton() const;

public slots:
	void resetUserInfo(QString &userName, int level, int experience);

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
};

#endif // SIMPLIFIEDUSERINFOWIDGET_H
