#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QTableWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"databaseserver.h"
#include<QVector>
#include"word.h"

class QuestionWidget: public QWidget
{
	Q_OBJECT
public:
	explicit QuestionWidget(DatabaseServer &_DBserver ,QWidget *parent = nullptr);
signals:
	// to database
	void sendQuestionWordList(QVector<Word> words, QString questionerName);
	// to mainwindow
	void requireQuestionerName();
public slots:
	void receiveAddedWords(int count, int expGained);
	void receiveQuestionerName(QString _questionerName);
	void paintEvent(QPaintEvent *event);
private:	
	void createWidget();
	void createLayout();
	void createConnection();

	void showImportDialog(QVector<Word> words);
	void on_importButton_clicked();
	void on_clearButton_clicked();
	void on_submitButton_clicked();

	void keyPressEvent(QKeyEvent *event);
	void addNewLine();

	QPushButton *importButton, *submitButton, *clearButton;
	QTableWidget *tableWidget;
	QHBoxLayout *buttonLayout;
	QVBoxLayout *mainLayout;

	DatabaseServer &DBserver;
	QString questionerName;
};

#endif // QUESTIONWIDGET_H
