#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QTableWidget>
#include<QVector>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QTableWidgetItem>
#include"user.h"
#include"databaseserver.h"
#include"detaileduserinfodialog.h"

class RanklistWidget: public QWidget
{
	Q_OBJECT
public:
	explicit RanklistWidget(DatabaseServer &_DBServer, QWidget *parent = nullptr);
	void setUserName(const QString &value);

signals:
	void requestRanklist(SortMethod sortMethod);
	void requestDetailInfo(SortMethod sortMethod, int index);
	void sendGameMode(GameLevel level, GameStatus status, bool needSignal);
public slots:
	void receiveRanklist(QVector<Player> players, QVector<Questioner> questioners, SortMethod sortMethod);
	void receiveDetailInfo(Player player, Questioner questioner);
	void paintEvent(QPaintEvent *event);
private slots:
	void on_searchPlayerButton_clicked();
	void on_searchQuestionerButton_clicked();
	void on_tableWidgetItem_doubleClicked(QTableWidgetItem *item);
	void on_header_clicked(int column);
	void receiveGameMode(GameLevel level, GameStatus status, bool needSignal);
private:
	void createWidget();
	void createLayout();
	void createConnection();

	void showTableByPlayer(QVector<Player> &players);
	void showTableByQuestioner(QVector<Questioner> &questioners);

	QPushButton *searchPlayerButton, *searchQuestionerButton;
	QTableWidget *tableWidget;
	QVBoxLayout *mainLayout;
	QHBoxLayout *buttonLayout;
	SortMethod currentMethod;

	DatabaseServer &DBserver;
	QString userName;

};

#endif // SEARCHWIDGET_H
