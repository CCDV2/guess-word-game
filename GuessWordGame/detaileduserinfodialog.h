#ifndef DETAILEDUSERINFODIALOG_H
#define DETAILEDUSERINFODIALOG_H

#include<QDialog>
#include"user.h"
#include<QLabel>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QProgressBar>
#include<QVBoxLayout>

class DetailedUserInfoDialog : public QDialog
{
public:
	DetailedUserInfoDialog(Player player, Questioner questioner, QWidget *parent = nullptr);
private:

	QLabel *userNameLabel, *playerNameLabel, *playerLevelLabel, *playerNumLabel;
	QLabel *questionerNameLabel, *questionerLevelLabel, *questionerNumLabel;
	QProgressBar *playerBar, *questionerBar;
	QVBoxLayout *mainLayout;
	QGridLayout *playerLayout, *questionerLayout;
};

#endif // DETAILEDUSERINFODIALOG_H
