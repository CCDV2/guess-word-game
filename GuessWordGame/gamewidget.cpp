#include "gamewidget.h"
#include<QDebug>
#include<QThread>

const int TIME_INTERVAL = 20;

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

void GameWidget::startGame(GameLevel level)
{
	gameCache.reset();
	emit requestWordList(level);
}

void GameWidget::endGame()
{
	qDebug() << "Game finished!";
	qDebug() << "correct:" << gameCache.getCorrectNum();
	qDebug() << "wrong:" << gameCache.getWrongNum();
}

void GameWidget::showWordLineEdit()
{
	wordStackedWidget->setCurrentWidget(wordLineEdit);
	wordLineEdit->setEnabled(true);
	wordLineEdit->setFocus();
}

void GameWidget::showCountDownBar()
{
	wordStackedWidget->setCurrentWidget(wordLabel);
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

void GameWidget::createWidget()
{
	wordLabel = new QLabel(tr("abandon"));
	levelLabel = new QLabel(tr("Level 0"));
	countDownBar = new QProgressBar();
	wordLineEdit = new WordLineEdit();
	wordLineEdit->resize(wordLineEdit->maximumSize());

	wordStackedWidget = new QStackedWidget();
	wordStackedWidget->resize(wordStackedWidget->maximumSize());
	wordStackedWidget->addWidget(wordLabel);
	wordStackedWidget->addWidget(wordLineEdit);
}


void GameWidget::createLayout()
{
	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(levelLabel, 0, Qt::AlignLeft);
	mainLayout->addWidget(countDownBar, 0, Qt::AlignCenter);
	mainLayout->addWidget(wordStackedWidget, 0, Qt::AlignCenter);

	setLayout(mainLayout);
}

void GameWidget::createConnection()
{
	connect(&countDownTimer, &QTimer::timeout, this, &GameWidget::updateCountDown);
	connect(wordLineEdit, &WordLineEdit::sendWord, this, &GameWidget::receiveWord);
	connect(this, &GameWidget::requestWordList, &DBserver, &DatabaseServer::receiveWordListRequest);
	connect(&DBserver, &DatabaseServer::sendWordList, this, &GameWidget::receiveWordList);
	connect(this, &GameWidget::wordCorrectChecked, this, &GameWidget::nextWord);
}

void GameWidget::startCountDown()
{
	countDownBar->setMaximum(gameCache.getTimeLength());
	countDownTimer.setSingleShot(false);
	countDownTimer.start(TIME_INTERVAL);
}


// WordLineEdit class
WordLineEdit::WordLineEdit(QWidget *parent): QWidget(parent)
{
	lineEdit = new QLineEdit(this);
	lineEdit->setEnabled(false);
}

void WordLineEdit::setEnabled(bool enable)
{
	lineEdit->setEnabled(enable);
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


// GameCahe class
void GameCache::setWords(QVector<Word> _words)
{
	words = _words;
	ready = true;
}

bool GameCache::nextWord()
{
	++wordi;
	if(wordi == words.length()) return false;
	timeLength = LEVEL_TIME_TABLE[words[wordi].getLevel()] / TIME_INTERVAL;
	return true;
}

QString GameCache::getCurrentWord() const
{
	return words[wordi].getWord();
}

int GameCache::getCurrentLevel() const
{
	return words[wordi].getLevel();
}

void GameCache::increaseExp(int incExp)
{
	expGained += incExp;
}

void GameCache::increaseCorrectNum(int inc)
{
	correctNum += inc;
}

void GameCache::increaseWrongNum(int inc)
{
	wrongNum += inc;
}

bool GameCache::decreaseTimeLength(int dec)
{
	timeLength -= dec;
	if(timeLength <= 0) return false;
	else return true;
}

void GameCache::reset()
{
	wordi = -1;
	correctNum = -1;
	wrongNum = 0;
	expGained = 0;
	timeLength = 0;
	ready = false;
}

bool GameCache::isReady()
{
	return ready;
}

int GameCache::getTimeLength() const
{
	return timeLength;
}

int GameCache::getCorrectNum() const
{
	return correctNum;
}

int GameCache::getWrongNum() const
{
	return wrongNum;
}

