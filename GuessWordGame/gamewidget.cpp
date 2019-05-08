#include "gamewidget.h"
#include<QDebug>
#include<QThread>
#include<QMessageBox>
#include<iostream>
#include<QStyleOption>
#include<QPainter>
using std::max;


GameWidget::GameWidget(DatabaseServer &_DBserver, QWidget *parent):
	QWidget(parent), DBserver(_DBserver)
{
	QPalette palette = QPalette(this->palette());
	palette.setColor(QPalette::Background, Qt::yellow);
	setAutoFillBackground(true);
	setPalette(palette);

	createWidget();
	createLayout();
	createConnection();
}

void GameWidget::startGame(Player _player, GameLevel level)
{
	player = _player;
	gameCache.reset(level);
	emit requestWordList(level);
}

void GameWidget::endGame()
{	
	EndGamePacket packet = gameCache.toEndGamePacket(player.getUserName());
	emit sendEndGamePacket(packet);
//	double difficultyScale = DIFFICULTY_SCALE_TABLE[gameCache.getLevel()];
//	double expGained = 50 * (max(gameCache.getCorrectNum() - gameCache.getWrongNum(), 0))
//			* difficultyScale;
//	gameCache.setExpGained(static_cast<int>(expGained));
//	emit updateUserExp(player.getUserName(), gameCache.getExpGained(), gameCache.getCorrectNum());
//	// TODO
//	EndGameDialog *endGameDialog = new EndGameDialog(gameCache, this);
//	endGameDialog->exec();
//	emit toMainWindow();
}

void GameWidget::showWordLineEdit()
{
	wordStackedWidget->setCurrentWidget(wordLineEdit);
	wordLineEdit->setEnabled(true);
//	wordLineEdit->setVisible(true);
	wordLineEdit->setFocus();
}

void GameWidget::showCountDownBar()
{
	wordStackedWidget->setCurrentWidget(wordLabel);
//	wordLineEdit->setVisible(false);
	wordLineEdit->setEnabled(false);
}

void GameWidget::updateCountDown()
{
	if(gameCache.decreaseTimeLength())
	{		
		countDownBar->setValue(gameCache.getTimeLength());
	}
	else
	{
		countDownTimer.stop();
		showWordLineEdit();
	}
}

void GameWidget::nextWord(bool isLastCorrect)
{
	// last word accumulate
	if(isLastCorrect)
	{
		qDebug() << "correct!";
		gameCache.increaseCorrectNum();
	}
	else
	{
		qDebug() << "wrong!";
		gameCache.increaseWrongNum();
	}

	// current word start
	if(gameCache.nextWord())
	{
		wordLabel->setText(gameCache.getCurrentWord());
		levelLabel->setText(tr("Level %1").arg(gameCache.getCurrentLevel()));
		showCountDownBar();
		startCountDown();
	}
	else
	{
		endGame();
	}
}

void GameWidget::receiveWord(QString word)
{
	gameCache.endCountTime();
	if(word == gameCache.getCurrentWord())
	{
		emit wordCorrectChecked(true);
	}
	else
	{
		emit wordCorrectChecked(false);
	}
}

void GameWidget::receiveWordList(QVector<Word> words)
{
	gameCache.setWords(words);
	nextWord(true);
}

void GameWidget::receiveShowEndGameDialog(EndGamePacket packet)
{
	EndGameDialog *endGameDialog = new EndGameDialog(packet, this);
	endGameDialog->exec();
	emit toMainWindow();
}

void GameWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption styleOpt;
	styleOpt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void GameWidget::createWidget()
{
	wordLabel = new QLabel(tr("abandon"));
	levelLabel = new QLabel(tr("Level 0"));
	countDownBar = new QProgressBar();
	wordLineEdit = new WordLineEdit();
//	wordLineEdit->resize(200, 100);

	wordStackedWidget = new QStackedWidget();
//	wordStackedWidget->resize(wordStackedWidget->maximumSize());
	wordStackedWidget->addWidget(wordLabel);
	wordStackedWidget->addWidget(wordLineEdit);
}


void GameWidget::createLayout()
{
	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(levelLabel, 1, Qt::AlignLeft);
	mainLayout->addWidget(countDownBar, 5, Qt::AlignCenter);
	mainLayout->addWidget(wordStackedWidget, 4, Qt::AlignCenter);

	setLayout(mainLayout);
}

void GameWidget::createConnection()
{
	connect(&countDownTimer, &QTimer::timeout, this, &GameWidget::updateCountDown);
	connect(wordLineEdit, &WordLineEdit::sendWord, this, &GameWidget::receiveWord);
	connect(this, &GameWidget::requestWordList, &DBserver, &DatabaseServer::receiveWordListRequest);
	connect(&DBserver, &DatabaseServer::sendWordList, this, &GameWidget::receiveWordList);
	connect(this, &GameWidget::wordCorrectChecked, this, &GameWidget::nextWord);
	connect(this, &GameWidget::sendEndGamePacket, &DBserver, &DatabaseServer::receiveEndGamePacket);
	connect(&DBserver, &DatabaseServer::sendShowEndGameDialog, this, &GameWidget::receiveShowEndGameDialog);
}

void GameWidget::startCountDown()
{
	countDownBar->setMaximum(gameCache.getTimeLength());
	countDownTimer.setSingleShot(false);
	countDownTimer.start(TIME_INTERVAL);
	gameCache.startCountTime();
}


// WordLineEdit class
WordLineEdit::WordLineEdit(QWidget *parent): QWidget(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	lineEdit = new QLineEdit();
	mainLayout->addWidget(lineEdit, 0, Qt::AlignCenter);
	lineEdit->setEnabled(false);
}

void WordLineEdit::setEnabled(bool enable)
{
	lineEdit->setEnabled(enable);
}

void WordLineEdit::setFocus()
{
	lineEdit->setFocus();
}


void WordLineEdit::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
	{
		emit sendWord(lineEdit->text());
		lineEdit->clear();
	}
	if(event->key() == Qt::Key_Escape)
	{
		lineEdit->clear();
	}
}



