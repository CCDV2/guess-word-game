#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include<QDialog>
#include<QProgressBar>
#include<QLabel>
#include<QLineEdit>
#include<QTimer>
#include<QVBoxLayout>
#include<QVector>
#include<QPalette>
#include<QStackedWidget>
#include<QKeyEvent>
#include"datastructure.h"
#include"word.h"
#include"databaseserver.h"
#include"endgamedialog.h"
#include"gamecache.h"
#include<QTime>



class WordLineEdit;


class GameWidget: public QWidget
{
	Q_OBJECT
public:
	GameWidget(DatabaseServer &_DBserver, QWidget *parent = nullptr);
	void startGame(Player _player, GameLevel level, GameStatus status, bool needSignal = true);
	void endGame();
public slots:
	void receiveWord(QString); // the word from line edit
	void receiveWordList(QVector<Word> _words);
	void receiveShowEndGameDialog(EndGamePacket packet);
	void paintEvent(QPaintEvent *event);
signals:
	// to datbase
	void requestWordList(GameLevel level, GameStatus status);
	void sendEndGamePacket(EndGamePacket packet);
	// to this(self)
	void wordCorrectChecked(bool isCorrect);
	// to database
	void updateUserExp(QString playerName, int expGained, int problemNum);
	// to mainwindow
	void toMainWindow();



private slots:
	void updateCountDown();
	void nextWord(bool isLastCorrect);

private:
	void createWidget();
	void createLayout();
	void createConnection();

	void startCountDown();
	void showWordLineEdit();
	void showCountDownBar();

	QVBoxLayout *mainLayout;
	QTimer countDownTimer;
	QProgressBar *countDownBar;
	QLabel *wordLabel, *levelLabel;
	WordLineEdit *wordLineEdit;
	QStackedWidget *wordStackedWidget;

	GameCache gameCache;

	DatabaseServer &DBserver;
	Player player;

	QTime typingTimer;
};

class WordLineEdit: public QWidget
{
	Q_OBJECT
public:
	WordLineEdit(QWidget *parent = nullptr);
	void setEnabled(bool enable);
	void setFocus();
signals:
	void sendWord(QString);

private slots:
	void keyPressEvent(QKeyEvent *);
private:
	QLineEdit *lineEdit;
};



#endif // GAMEWIDGET_H
