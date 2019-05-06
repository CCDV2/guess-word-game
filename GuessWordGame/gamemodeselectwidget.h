#ifndef GAMEMODESELECTWIDGET_H
#define GAMEMODESELECTWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QGridLayout>
#include"datastructure.h"


class GameModeSelectWidget: public QWidget
{
	Q_OBJECT
public:
	explicit GameModeSelectWidget(QWidget *parent = nullptr);
signals:
	void sendGameMode(GameLevel level);
public slots:
	void paintEvent(QPaintEvent *event);

private slots:
	void on_easyButton_clicked();
	void on_normalButton_clicked();
	void on_hardButton_clicked();
	void on_expertButton_clicked();

private:
	void createWidget();
	void createLayout();
	void createConnection();

	QPushButton *easyButton, *normalButton, *hardButton, *expertButton;
	QLabel *modeSelectLabel;

	QGridLayout *mainLayout;
};

#endif // GAMEMODESELECTWIDGET_H
