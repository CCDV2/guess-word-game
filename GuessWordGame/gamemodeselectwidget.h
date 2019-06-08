#ifndef GAMEMODESELECTWIDGET_H
#define GAMEMODESELECTWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QGridLayout>
#include"datastructure.h"
#include<QCheckBox>

class GameModeSelectWidget: public QWidget
{
	Q_OBJECT
public:
	explicit GameModeSelectWidget(QWidget *parent = nullptr);
signals:
	void sendGameMode(GameLevel level, GameStatus status, bool needSignal);
public slots:
	void paintEvent(QPaintEvent *event);
#ifdef VERSION1
	void startGame();
#endif
private slots:
	void on_easyButton_clicked();
	void on_normalButton_clicked();
	void on_hardButton_clicked();
	void on_expertButton_clicked();
	void changeStateText();

private:
	void createWidget();
	void createLayout();
	void createConnection();
#ifdef USE_NETWORK
	QCheckBox *duoCheckBox;
	QLabel *duoSelectLabel, *duoStateLabel;
#endif
	QPushButton *easyButton, *normalButton, *hardButton, *expertButton;
	QLabel *modeSelectLabel;

	QGridLayout *mainLayout;
	GameStatus status;
};

#endif // GAMEMODESELECTWIDGET_H
