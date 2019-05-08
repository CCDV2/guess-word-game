#ifndef DETAILEDUSERINFODIALOG_H
#define DETAILEDUSERINFODIALOG_H

#include<QDialog>
#include"user.h"
#include<QLabel>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QProgressBar>
#include<QVBoxLayout>
#include"datastructure.h"

class DetailedUserInfoDialog : public QDialog
{
public:
	DetailedUserInfoDialog(Player _player, Questioner _questioner, DetailedWidgetArg _arg = MYSELF, QWidget *parent = nullptr);
private:

	void createWidget();
	void createLayout();
	void createConnection();
	QLabel *userNameLabel, *playerNameLabel, *playerLevelLabel, *playerNumLabel;
	QLabel *questionerNameLabel, *questionerLevelLabel, *questionerNumLabel;
	QProgressBar *playerBar, *questionerBar;
	QGridLayout *mainLayout;
//	QGridLayout *playerLayout, *questionerLayout;
	QPushButton *backButton;
	QPushButton *matchButton, *deleteFriendButton;
	QPushButton *acceptFriendButton, *rejectFriendButton;
	QPushButton *addFriendButton;
	QHBoxLayout *buttonLayout;

	Player player;
	Questioner questioner;
	DetailedWidgetArg arg;
};

#endif // DETAILEDUSERINFODIALOG_H
