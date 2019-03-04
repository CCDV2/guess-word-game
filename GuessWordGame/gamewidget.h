#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include<QProgressBar>
#include<QLabel>
#include<QLineEdit>
#include<QTimer>
#include<QVBoxLayout>
#include<QVector>
#include<QPalette>
#include<QStackedWidget>
#include<QKeyEvent>

class WordLineEdit;

class GameWidget: public QWidget
{
	Q_OBJECT
public:
	GameWidget(QWidget *parent = nullptr);

public slots:
	void receiveWord(QString);

private slots:
	void showWordLineEdit();
	void updateCountDown();

private:
	void createWidget();
	void createLayout();
	void createConnection();

	void startCountDown();

	QVBoxLayout *mainLayout;
	QTimer countDownTimer;
	QProgressBar *countDownBar;
	QLabel *wordLabel, *levelLabel;
	WordLineEdit *wordLineEdit;
	QStackedWidget *wordStackedWidget;
	int timeLength;
};

class WordLineEdit: public QWidget
{
	Q_OBJECT
public:
	WordLineEdit(QWidget *parent = nullptr);
	void setEnabled(bool enable);
signals:
	void sendWord(QString);

private slots:
	void keyPressEvent(QKeyEvent *);
private:
	QLineEdit *lineEdit;
};

#endif // GAMEWIDGET_H
