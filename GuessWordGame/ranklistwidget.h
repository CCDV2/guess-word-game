#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QTableWidget>
#include<QVector>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include"user.h"
#include"databaseserver.h"

class RanklistWidget: public QWidget
{
	Q_OBJECT
public:
	explicit RanklistWidget(DatabaseServer &_DBServer, QWidget *parent = nullptr);
signals:
	void requestRanklist(bool isPlayerList);
public slots:
	void receiveRanklist(QVector<Player> players, QVector<Questioner> questioners, bool isPlayerList);

private slots:
	void on_searchPlayerButton_clicked();
	void on_searchQuestionerButton_clicked();

private:
	void createWidget();
	void createLayout();
	void createConnection();

	QPushButton *searchPlayerButton, *searchQuestionerButton;
	QTableWidget *tableWidget;
	QVBoxLayout *mainLayout;
	QHBoxLayout *buttonLayout;


	DatabaseServer &DBserver;

};

#endif // SEARCHWIDGET_H
