#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("猜单词游戏"));
//	setWindowState(Qt::WindowMaximized);

	createWidget();
	createLayout();
	createConnection();
	player = nullptr;
	questioner = nullptr;
}

MainWindow::~MainWindow()
{
	delete player;
	delete questioner;
}

void MainWindow::receiveUserInfo(Player _player, Questioner _questioner)
{
	player = new Player(_player);
	questioner = new Questioner(_questioner);
	simplifiedUserInfoWidget->showUserInfo(*player, *questioner);
}

void MainWindow::receiveRequireForUserInfo()
{
	emit sendUserInfo(*player, *questioner);
}



void MainWindow::createWidget()
{
	mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
//	loginWindow = new LoginDialog();
//	registerWindow = new RegisterDialog();
	gameWidget = new GameWidget();
	simplifiedUserInfoWidget = new SimplifiedUserInfoWidget(DBServer);
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
	connect(&DBServer, &DatabaseServer::sendUserInfo, this, &MainWindow::receiveUserInfo);
	connect(simplifiedUserInfoWidget, &SimplifiedUserInfoWidget::requireUserInfo,
			this, &MainWindow::receiveRequireForUserInfo);
	connect(this, &MainWindow::sendUserInfo,
			simplifiedUserInfoWidget, &SimplifiedUserInfoWidget::receiveUserInfo);
}
