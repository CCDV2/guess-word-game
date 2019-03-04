#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("猜单词游戏"));
	setWindowState(Qt::WindowMaximized);

	createWidget();
	createLayout();

}

MainWindow::~MainWindow()
{

}

void MainWindow::createWidget()
{
	mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
	loginWindow = new LoginDialog();
}

void MainWindow::createLayout()
{
	mainLayout = new QGridLayout(mainWidget);
	mainLayout->addWidget(loginWindow, 0, 0);

	mainWidget->setLayout(mainLayout);
}
