#include "mainwindow.h"
#include<QMessageBox>
#include<QPainter>
#include<QThread>

//#if defined(Q_OS_WIN)
//#include<windows.h>
//#endif

#define USE_LOGO

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(tr("猜单词游戏"));
	setWindowState(Qt::WindowMaximized);
	setWindowIcon(QIcon(":/png/img/icon.png"));
	tcpClient = new TcpClient(this);


	DBServer = new DatabaseServer(*tcpClient);
	createWidget();
	createLayout();
	createConnection();



	player = nullptr;
	questioner = nullptr;
	QThread::sleep(4);
}

MainWindow::~MainWindow()
{
	if(player)
		delete player;
	if(questioner)
		delete questioner;
	if(DBServer)
		delete DBServer;
}

void MainWindow::receiveUserInfo(Player _player, Questioner _questioner)
{
	if(player != nullptr) delete player;
	if(questioner != nullptr) delete questioner;
	player = new Player(_player);
	questioner = new Questioner(_questioner);
	simplifiedUserInfoWidget->showUserInfo(*player, *questioner);
	ranklistWidget->setUserName(player->getUserName());
	onlineUserWidget->setIsLogin(true);
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

void MainWindow::receiveBattleRequest(BattlePacket packet)
{
	respondPacket = packet;
	QString level = tr("难度：");
	switch(packet.level)
	{
	case EASY:
		level += tr("EASY");
		break;
	case NORMAL:
		level += tr("NORMAL");
		break;
	case HARD:
		level += tr("HARD");
		break;
	case EXPERT:
		level += tr("EXPERT");
		break;
	}

	battleBox.setText(packet.enemy +
				tr("向你发来了对战请求，是否接受？\n") +
				level + ' ' +
				tr("单词数量：%1").arg(packet.wordNum));
	battleBox.show();

}

void MainWindow::receiveBattleRespond(BattlePacket packet)
{
	switch(packet.respond)
	{
	case BATTLE_REJECT:
		QMessageBox::information(this, tr("对战请求"), packet.enemy + tr("拒绝了你的对战请求"), QMessageBox::Ok);
		backToWelcomeWidget();
		break;
	case BATTLE_OFFLINE:
		QMessageBox::information(this, tr("对战请求"), packet.enemy + tr("似乎并不在线。。"), QMessageBox::Ok);
		backToWelcomeWidget();
		break;
	default:
		qDebug() << "battle respond can't be here";
	}

}

void MainWindow::receiveEnmeyGameCancel()
{
	battleBox.close();
	QMessageBox::information(this, tr("对战请求"), tr("对方取消了对战请求"));
	backToWelcomeWidget();
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

void MainWindow::receiveGameMode(GameLevel level, GameStatus status, bool needSignal)
{
	stackWidget->setCurrentWidget(widget[2]);
	gameWidget->startGame(*player, level, status, needSignal);
}

void MainWindow::showEvent(QShowEvent *event)
{
	Q_UNUSED(event);
	if(!tcpClient->isConnected())
	{
		QTimer::singleShot(500, this, &MainWindow::networkFailed);
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	Q_UNUSED(event);
#ifdef USE_NETWORK
	disconnect(tcpClient, &TcpClient::serverDisconnected, this, &MainWindow::networkFailed);
#endif
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption styleOpt;
	styleOpt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void MainWindow::networkFailed()
{
	QMessageBox::critical(this, tr("网络断开"), tr("网络连接失败"));
	close();
}

void MainWindow::receiveWaitSignal()
{
	waitBox.show();
}

void MainWindow::on_gameBackButton_clicked()
{
	emit sendGameCancel();
}



void MainWindow::battleBoxClosed(int _result)
{
	switch(_result)
	{
	case QMessageBox::Yes:
		respondPacket.isRequest = false;
		respondPacket.respond = BATTLE_ACCEPT;
		emit sendBattleRespond(respondPacket);
		receiveGameMode(respondPacket.level, GAME_DUO, false);
		break;
	case QMessageBox::No:
	case 0:
		respondPacket.isRequest = false;
		respondPacket.respond = BATTLE_REJECT;
		emit sendBattleRespond(respondPacket);
		break;
	default:
		qDebug() << "the result is " << _result;
		break;
	}
}






void MainWindow::createWidget()
{
	mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
//	loginWindow = new LoginDialog();
//	registerWindow = new RegisterDialog();
	simplifiedUserInfoWidget = new SimplifiedUserInfoWidget(*DBServer);
	simplifiedUserInfoWidget->setObjectName(moduleWidgetName);
	logoLabel = new QLabel(tr("LOGO"));
#ifdef USE_LOGO
	QImage logoImg;
	logoImg.load(":/png/img/logo-fade-50.png");
	logoImg.scaled(logoLabel->size(), Qt::KeepAspectRatio);
	logoLabel->setPixmap(QPixmap::fromImage(logoImg));
	logoLabel->setScaledContents(true);
#endif
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
	gameWidget = new GameWidget(*DBServer);
	gameWidget->setObjectName(moduleWidgetName);
	backButton[1] = new QPushButton(tr("返回"));
	widget[2] = new QWidget();

//	question widget
	questionWidget = new QuestionWidget(*DBServer);
	questionWidget->setObjectName(moduleWidgetName);
	backButton[2] = new QPushButton(tr("返回"));
	widget[3] = new QWidget();

//	ranklist widget
	ranklistWidget = new RanklistWidget(*DBServer);
	ranklistWidget->setObjectName(moduleWidgetName);
	backButton[3] = new QPushButton(tr("返回"));
	widget[4] = new QWidget();

	for(int i = 0; i < 5; ++i)
	{
		stackWidget->addWidget(widget[i]);
	}

//	friend widget
	onlineUserWidget = new OnlineUserWidget(*DBServer, this);
	onlineUserWidget->setObjectName(moduleWidgetName);

	waitBox.setWindowTitle(tr("服务器忙"));
	waitBox.setText(tr("服务器繁忙中，请稍等"));
	waitBox.setStandardButtons(QMessageBox::Ok);
	waitBox.setModal(false);

	battleBox.setWindowTitle(tr("对战请求"));
	battleBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	battleBox.setModal(false);

//	exit button
	exitButton = new QPushButton(tr("退出游戏"));
}

void MainWindow::createLayout()
{
	mainLayout = new QHBoxLayout(mainWidget);
	loginOnlineLayout = new QVBoxLayout();
	loginOnlineLayout->addWidget(simplifiedUserInfoWidget, 1);
	loginOnlineLayout->addWidget(onlineUserWidget, 4);
	mainLayout->addLayout(loginOnlineLayout, 1);
//	mainLayout->addWidget(loginWindow, 0, 0);
//	mainLayout->addWidget(registerWindow, 1, 0);

	for(int i = 0; i < 5; ++i)
	{
		widgetLayout[i] = new QHBoxLayout(widget[i]);
	}

//	welcome widget
	buttonLayout = new QVBoxLayout();
	buttonLayout->addWidget(startGameButton, 3, Qt::AlignCenter);
	buttonLayout->addWidget(startQuestionButton, 3, Qt::AlignCenter);
	buttonLayout->addWidget(startRanklistButton, 3, Qt::AlignCenter);
	buttonLayout->addWidget(exitButton, 1, Qt::AlignCenter);
	widgetLayout[0]->addWidget(logoLabel, 4);
	widgetLayout[0]->addLayout(buttonLayout, 1);

//	game select widget
	widgetLayout[1]->addWidget(gameModeSelectWidget);
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
	connect(DBServer, &DatabaseServer::sendUserInfo, this, &MainWindow::receiveUserInfo);
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
	connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);
#ifdef USE_NETWORK
	connect(DBServer, &DatabaseServer::sendBattleRequest, this, &MainWindow::receiveBattleRequest);
	connect(DBServer, &DatabaseServer::sendBattleRespond, this, &MainWindow::receiveBattleRespond);
	connect(this, &MainWindow::sendBattleRespond, DBServer, &DatabaseServer::receiveBattelRespond);

	connect(onlineUserWidget, &OnlineUserWidget::sendGameMode, this, &MainWindow::receiveGameMode);
	connect(ranklistWidget, &RanklistWidget::sendGameMode, this, &MainWindow::receiveGameMode);

	connect(tcpClient, &TcpClient::serverDisconnected, this, &MainWindow::networkFailed);
	connect(DBServer, &DatabaseServer::sendWaitSignal, this, &MainWindow::receiveWaitSignal);

	connect(backButton[1], &QPushButton::clicked, this, &MainWindow::on_gameBackButton_clicked);
	connect(this, &MainWindow::sendGameCancel, DBServer, &DatabaseServer::receiveGameCancel);
	connect(DBServer, &DatabaseServer::sendEnemyGameCancel, this, &MainWindow::receiveEnmeyGameCancel);
	connect(&battleBox, &QMessageBox::finished, this, &MainWindow::battleBoxClosed);
#endif


}
