#include "mainwindow.h"
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("猜单词游戏"));
	setWindowState(Qt::WindowMaximized);

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

void MainWindow::on_startGameButton_clicked()
{
	if(player == nullptr)
	{
		QMessageBox::information(this, tr("请先登录"), tr("请先登录后再开始游戏"));
	}
	else
	{

	}
}

void MainWindow::on_startQuestionButton_clicked()
{
	if(player == nullptr)
	{
		QMessageBox::information(this, tr("请先登录"), tr("请先登录后在开始出题"));
	}
	else
	{

	}
}



void MainWindow::createWidget()
{
	mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
//	loginWindow = new LoginDialog();
//	registerWindow = new RegisterDialog();
	gameWidget = new GameWidget();
	simplifiedUserInfoWidget = new SimplifiedUserInfoWidget(DBServer);
	startGameButton = new QPushButton(tr("开始游戏"));
	startQuestionButton = new QPushButton(tr("开始出题"));
	ranklistWidget = new RanklistWidget(DBServer);
}

void MainWindow::createLayout()
{
	mainLayout = new QGridLayout(mainWidget);
	mainLayout->addWidget(simplifiedUserInfoWidget, 0, 0, Qt::AlignTop);
//	mainLayout->addWidget(loginWindow, 0, 0);
//	mainLayout->addWidget(registerWindow, 1, 0);

	mainLayout->addWidget(gameWidget, 0, 1, 1, 1);
	mainLayout->addWidget(ranklistWidget, 1, 1, 1, 1);

	buttonLayout = new QVBoxLayout();
	buttonLayout->addWidget(startGameButton);
	buttonLayout->addWidget(startQuestionButton);

	mainLayout->addLayout(buttonLayout, 0, 2);

	mainWidget->setLayout(mainLayout);
}

void MainWindow::createConnection()
{
	connect(&DBServer, &DatabaseServer::sendUserInfo, this, &MainWindow::receiveUserInfo);
	connect(simplifiedUserInfoWidget, &SimplifiedUserInfoWidget::requireUserInfo,
			this, &MainWindow::receiveRequireForUserInfo);
	connect(this, &MainWindow::sendUserInfo,
			simplifiedUserInfoWidget, &SimplifiedUserInfoWidget::receiveUserInfo);
	connect(startGameButton, &QPushButton::clicked, this, &MainWindow::on_startGameButton_clicked);
	connect(startQuestionButton, &QPushButton::clicked, this, &MainWindow::on_startQuestionButton_clicked);
}
