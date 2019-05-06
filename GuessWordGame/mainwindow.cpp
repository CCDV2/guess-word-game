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
	if(player != nullptr) delete player;
	if(questioner != nullptr) delete questioner;
	player = new Player(_player);
	questioner = new Questioner(_questioner);
	simplifiedUserInfoWidget->showUserInfo(*player, *questioner);
}

void MainWindow::receiveRequireForUserInfo()
{
	emit sendUserInfo(*player, *questioner);
}

void MainWindow::receiveRequireForQuestionerName()
{
	if(questioner == nullptr)
	{
		qDebug() << "questioner not created error";
		emit sendQuestionerName(tr(""));
	}
	else
	{
		emit sendQuestionerName(questioner->getUserName());
	}
}

void MainWindow::on_startGameButton_clicked()
{
	if(player == nullptr)
	{
		QMessageBox::information(this, tr("请先登录"), tr("请先登录后再开始游戏"));
	}
	else
	{
		stackWidget->setCurrentWidget(widget[1]);
	}
}

void MainWindow::on_startQuestionButton_clicked()
{
	if(player == nullptr)
	{
		QMessageBox::information(this, tr("请先登录"), tr("请先登录后再开始出题"));
	}
	else
	{
		stackWidget->setCurrentWidget(widget[3]);
	}
}

void MainWindow::on_startRanklistButton_clicked()
{
	if(player == nullptr)
	{
		QMessageBox::information(this, tr("请先登录"), tr("请先登录后再查看排行榜"));
	}
	else
	{
		stackWidget->setCurrentWidget(widget[4]);
	}
}

void MainWindow::backToWelcomeWidget()
{
	stackWidget->setCurrentWidget(widget[0]);
}

void MainWindow::receiveGameMode(GameLevel level)
{
	stackWidget->setCurrentWidget(widget[2]);
	gameWidget->startGame(*player, level);
}



void MainWindow::createWidget()
{
	mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
//	loginWindow = new LoginDialog();
//	registerWindow = new RegisterDialog();
	simplifiedUserInfoWidget = new SimplifiedUserInfoWidget(DBServer);
	simplifiedUserInfoWidget->setObjectName(moduleWidgetName);
	logoLabel = new QLabel(tr("LOGO"));
	QImage logoImg;
	logoImg.load(":/png/img/20130707105529296.jpg");
	logoLabel->setPixmap(QPixmap::fromImage(logoImg));

	stackWidget = new QStackedWidget();

//	welcome widget
	startGameButton = new QPushButton(tr("开始游戏"));
	startQuestionButton = new QPushButton(tr("开始出题"));
	startRanklistButton = new QPushButton(tr("查看排行榜"));
	widget[0] = new QWidget();

//	game mode select widget
	gameModeSelectWidget = new GameModeSelectWidget();
	gameModeSelectWidget->setObjectName(moduleWidgetName);
	backButton[0] = new QPushButton(tr("返回"));
	widget[1] = new QWidget();

//	game widget
	gameWidget = new GameWidget(DBServer);
	gameWidget->setObjectName(moduleWidgetName);
	backButton[1] = new QPushButton(tr("返回"));
	widget[2] = new QWidget();

//	question widget
	questionWidget = new QuestionWidget(DBServer);
	questionWidget->setObjectName(moduleWidgetName);
	backButton[2] = new QPushButton(tr("返回"));
	widget[3] = new QWidget();

//	ranklist widget
	ranklistWidget = new RanklistWidget(DBServer);
	ranklistWidget->setObjectName(moduleWidgetName);
	backButton[3] = new QPushButton(tr("返回"));
	widget[4] = new QWidget();

	for(int i = 0; i < 5; ++i)
	{
		stackWidget->addWidget(widget[i]);
	}
}

void MainWindow::createLayout()
{
	mainLayout = new QHBoxLayout(mainWidget);
	mainLayout->addWidget(simplifiedUserInfoWidget, 1, Qt::AlignTop);
//	mainLayout->addWidget(loginWindow, 0, 0);
//	mainLayout->addWidget(registerWindow, 1, 0);

	for(int i = 0; i < 5; ++i)
	{
		widgetLayout[i] = new QHBoxLayout(widget[i]);
	}

//	welcome widget
	buttonLayout = new QVBoxLayout();
	buttonLayout->addWidget(startGameButton, 1, Qt::AlignCenter);
	buttonLayout->addWidget(startQuestionButton, 1, Qt::AlignCenter);
	buttonLayout->addWidget(startRanklistButton, 1, Qt::AlignCenter);
	widgetLayout[0]->addWidget(logoLabel, 4);
	widgetLayout[0]->addLayout(buttonLayout, 1);

//	game select widget
	widgetLayout[1]->addWidget(gameModeSelectWidget, 0, Qt::AlignCenter);
	widgetLayout[1]->addWidget(backButton[0], 0, Qt::AlignBottom | Qt::AlignRight);

//	game widget
	widgetLayout[2]->addWidget(gameWidget, 1);
	widgetLayout[2]->addWidget(backButton[1], 0, Qt::AlignBottom | Qt::AlignRight);

//	question widget
	widgetLayout[3]->addWidget(questionWidget);
	widgetLayout[3]->addWidget(backButton[2], 0, Qt::AlignBottom | Qt::AlignRight);

//	ranklist widget
	widgetLayout[4]->addWidget(ranklistWidget);
	widgetLayout[4]->addWidget(backButton[3], 0, Qt::AlignBottom | Qt::AlignRight);


	mainLayout->addWidget(stackWidget, 5);
	mainWidget->setLayout(mainLayout);
}

void MainWindow::createConnection()
{
	// use in login
	connect(&DBServer, &DatabaseServer::sendUserInfo, this, &MainWindow::receiveUserInfo);
	connect(simplifiedUserInfoWidget, &SimplifiedUserInfoWidget::requireUserInfo,
			this, &MainWindow::receiveRequireForUserInfo);

	// use for detail uesr info
	connect(this, &MainWindow::sendUserInfo,
			simplifiedUserInfoWidget, &SimplifiedUserInfoWidget::receiveUserInfo);

	// use for questioner widget
	connect(questionWidget, &QuestionWidget::requireQuestionerName, this, &MainWindow::receiveRequireForQuestionerName);
	connect(this, &MainWindow::sendQuestionerName, questionWidget, &QuestionWidget::receiveQuestionerName);

	connect(startGameButton, &QPushButton::clicked, this, &MainWindow::on_startGameButton_clicked);
	connect(gameModeSelectWidget, &GameModeSelectWidget::sendGameMode, this, &MainWindow::receiveGameMode);
	connect(startQuestionButton, &QPushButton::clicked, this, &MainWindow::on_startQuestionButton_clicked);
	connect(startRanklistButton, &QPushButton::clicked, this, &MainWindow::on_startRanklistButton_clicked);

	connect(gameWidget, &GameWidget::toMainWindow, this, &MainWindow::backToWelcomeWidget);
	for(int i = 0; i < 4; ++i)
	{
		connect(backButton[i], &QPushButton::clicked, this, &MainWindow::backToWelcomeWidget);
	}
}
