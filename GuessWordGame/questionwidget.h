#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QTableWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<databaseserver.h>

class QuestionWidget: public QWidget
{
	Q_OBJECT
public:
	explicit QuestionWidget(DatabaseServer &_DBserver ,QWidget *parent = nullptr);
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QPushButton *importButton, *submitButton, *checkButton;
	QTableWidget *tableWidget;
	QHBoxLayout *buttonLayout;
	QVBoxLayout *mainLayout;

	DatabaseServer &DBserver;
};

#endif // QUESTIONWIDGET_H
