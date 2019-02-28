#include "mainwindow.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("猜单词游戏"));
	resize(2560, 1440);

	loginWindow = new LoginWindow(this);

	QGridLayout *mainLayout = new QGridLayout(this);
	mainLayout->addWidget(loginWindow, 0, 0);

	setLayout(mainLayout);
}

MainWindow::~MainWindow()
{

}
