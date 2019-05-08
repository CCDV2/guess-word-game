#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include<QDialog>
#include<QWidget>
#include<QLabel>
#include<QStackedWidget>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QMouseEvent>
#include"gamecache.h"

class EndGameDialog: public QDialog
{
public:
	explicit EndGameDialog(EndGamePacket _packet, QWidget *parent = nullptr);
private:
	void createWidget();
	void createLayout();

	void toNextWidget();

	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

	EndGamePacket packet;
	QLabel *headLabel;
	// first page
	QWidget *numWidget;
	QLabel *numLabel, *correctLabel, *wrongLabel;
	QLabel *enemyCorrectNumLabel;
	QLabel *pressContinueLabel;
	// second page
	QWidget *timeWidget;
	QLabel *timeLabel, *spendTimeLabel;
	QLabel *enemySpendTimeLabel;
	// third page
	QWidget *expWidget;
	QLabel *validNumLabel, *scaleNumLabel, *levelLabel, *remainTimeLabel, *expGainedLabel;

	QStackedWidget *stackWidget;
	QGridLayout *numLayout, *timeLayout, *expLayout;
	QVBoxLayout *mainLayout;

	int state;
};

#endif // ENDGAMEDIALOG_H
