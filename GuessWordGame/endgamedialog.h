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
	explicit EndGameDialog(GameCache &_gameCache, QWidget *parent = nullptr);
private:
	void createWidget();
	void createLayout();
	void mouseReleaseEvent(QMouseEvent *event);

	GameCache &gameCache;
	QLabel *headLabel;
	// first page
	QWidget *numWidget;
	QLabel *numLabel, *correctLabel, *wrongLabel;
	QLabel *pressContinueLabel;
	// second page
	QWidget *expWidget;
	QLabel *validNumLabel, *scaleNumLabel, *levelLabel, *remainTimeLabel, *expGainedLabel;


	QStackedWidget *stackWidget;
	QGridLayout *numLayout, *expLayout;
	QVBoxLayout *mainLayout;

	int state;
};

#endif // ENDGAMEDIALOG_H
