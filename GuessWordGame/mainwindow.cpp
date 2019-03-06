#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("猜单词游戏"));
	setWindowState(Qt::WindowMaximized);

	createWidget();
	createLayout();
	createConnection();

}

MainWindow::~MainWindow()
{

}


void MainWindow::createWidget()
{
	mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
//	loginWindow = new LoginDialog();
//	registerWindow = new RegisterDialog();
	gameWidget = new GameWidget();
	simplifiedUserInfoWidget = new SimplifiedUserInfoWidget();
}

void MainWindow::createLayout()
{
	mainLayout = new QGridLayout(mainWidget);
	mainLayout->addWidget(simplifiedUserInfoWidget, 0, 0);
//	mainLayout->addWidget(loginWindow, 0, 0);
//	mainLayout->addWidget(registerWindow, 1, 0);

	mainLayout->addWidget(gameWidget, 0, 1);
	mainWidget->setLayout(mainLayout);
}

void MainWindow::createConnection()
{

}
