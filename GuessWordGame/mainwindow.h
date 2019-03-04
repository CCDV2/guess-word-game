#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "logindialog.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	void createWidget();
	void createLayout();
	QWidget *mainWidget;
	QGridLayout *mainLayout;
	LoginDialog *loginWindow;
};

#endif // MAINWINDOW_H
