#include "gamewidget.h"
#include<QDebug>

const int timeInterval = 20;

GameWidget::GameWidget(QWidget *parent): QWidget(parent)
{
	QPalette palette = QPalette(this->palette());
	palette.setColor(QPalette::Background, Qt::yellow);
	setAutoFillBackground(true);
	setPalette(palette);

	timeLength = 200;

	createWidget();
	createLayout();
	createConnection();
	startCountDown();
}

void GameWidget::showWordLineEdit()
{
	wordStackedWidget->setCurrentWidget(wordLineEdit);
	wordLineEdit->setEnabled(true);
}

void GameWidget::updateCountDown()
{
	if(timeLength > 0)
	{
		--timeLength;
//		qDebug() << timeLength;
		countDownBar->setValue(timeLength);
		countDownTimer.singleShot(timeInterval, this, &GameWidget::updateCountDown);
	}
	else
	{
		showWordLineEdit();
	}
}

void GameWidget::receiveWord(QString word)
{
	qDebug() << word;
}

void GameWidget::createWidget()
{
	wordLabel = new QLabel(tr("abandon"));
	levelLabel = new QLabel(tr("Level 0"));
	countDownBar = new QProgressBar();
	wordLineEdit = new WordLineEdit();

	wordStackedWidget = new QStackedWidget();
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
//	connect(&countDownTimer, &QTimer::timeout, this, &GameWidget::showWordLineEdit);
	connect(wordLineEdit, &WordLineEdit::sendWord, this, &GameWidget::receiveWord);
}

void GameWidget::startCountDown()
{
	countDownBar->setMaximum(timeLength);
	countDownTimer.singleShot(timeInterval, this, &GameWidget::updateCountDown);

}

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

