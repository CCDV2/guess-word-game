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
#include"databaseserver.h"

class DetailedUserInfoDialog : public QDialog
{
	Q_OBJECT
public:
	DetailedUserInfoDialog(Player _player, Questioner _questioner, DatabaseServer &_DBserver, DetailedWidgetArg _arg = MYSELF_OPEN, QWidget *parent = nullptr);
signals:
	void sendBattleRequest(BattlePacket packet);
	void sendGameMode(GameLevel level, GameStatus status, bool needSignal);
private slots:
	void on_matchButton_clicked();
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
	QPushButton *matchButton;
	QHBoxLayout *buttonLayout;

	Player player;
	Questioner questioner;
	DetailedWidgetArg arg;
	DatabaseServer &DBServer;
};

#endif // DETAILEDUSERINFODIALOG_H
