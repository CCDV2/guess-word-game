#include "endgamedialog.h"
using std::max;
#include<QDebug>

EndGameDialog::EndGameDialog(EndGamePacket _packet, QWidget *parent):
	QDialog(parent), packet(_packet)
{
	qDebug() << "endgame " <<packet.toString();
	state = 0;
	createWidget();
	createLayout();
}

void EndGameDialog::createWidget()
{
	headLabel = new QLabel();
	switch(packet.isWin)
	{
	case GAME_SINGLE:
		headLabel->setText(tr("闯关成功"));
		break;
	case GAME_WIN:
		headLabel->setText(tr("对战胜利"));
		break;
	case GAME_LOSE:
		headLabel->setText(tr("对战失败"));
		break;
	case GAME_TIE:
		headLabel->setText(tr("平局"));
		break;
	default:
		headLabel->setText(tr("未知错误"));
		break;
	}

	numWidget = new QWidget();
	numLabel = new QLabel(tr("单词统计:"));
	correctLabel = new QLabel(tr("答对个数：%1个").arg(packet.correctNum));
	wrongLabel = new QLabel(tr("答错单词：%1个").arg(packet.wrongNum));

	if(packet.isWin != GAME_SINGLE)
	{
		enemyCorrectNumLabel = new QLabel(tr("对方答对个数：%1个").arg(packet.enemyCorrectNum));
	}

	pressContinueLabel = new QLabel(tr("点击继续"));

	timeWidget = new QWidget();
	timeLabel = new QLabel(tr("时间统计"));
	spendTimeLabel = new QLabel(tr("花费时间：%1.%2s").
								arg(packet.totalTime / 1000).arg((packet.totalTime % 1000) / 100));
	if(packet.isWin != 0)
	{
		enemySpendTimeLabel = new QLabel(tr("对方花费时间：%1.%2s").
										 arg(packet.enemyTotalTime / 1000).
										 arg((packet.enemyTotalTime % 1000) / 100));
	}

	expWidget = new QWidget();
	validNumLabel = new QLabel(tr("%1").arg(max(packet.correctNum - packet.wrongNum, 0)));
	scaleNumLabel = new QLabel(tr("× 50"));
	levelLabel = new QLabel(tr("× %1").arg(DIFFICULTY_SCALE_TABLE[packet.level]));
	remainTimeLabel = new QLabel();
	switch(packet.isWin)
	{
	case GAME_SINGLE:
		remainTimeLabel->setText(tr("× 1"));
		break;
	case GAME_WIN:
		remainTimeLabel->setText(tr("× 2"));
		break;
	case GAME_LOSE:
		remainTimeLabel->setText(tr("× -0.5"));
		break;
	case GAME_TIE:
		remainTimeLabel->setText(tr("× 1.5"));
		break;
	default:
		remainTimeLabel->setText(tr("× 0"));
		break;
	}
	expGainedLabel = new QLabel(tr("%1").arg(packet.expGained));

	stackWidget = new QStackedWidget();
}

void EndGameDialog::createLayout()
{
	setWindowFlag(Qt::FramelessWindowHint);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(headLabel, 0, Qt::AlignCenter);
	mainLayout->addWidget(stackWidget);


	numLayout = new QGridLayout(numWidget);
	numLayout->addWidget(numLabel, 0, 0, Qt::AlignLeft);
	numLayout->addWidget(correctLabel, 1, 1, Qt::AlignRight);
	numLayout->addWidget(wrongLabel, 2, 1, Qt::AlignRight);
	if(packet.isWin == GAME_SINGLE)
	{
		numLayout->addWidget(pressContinueLabel, 3, 0, 1, 2, Qt::AlignCenter);
	}
	else
	{
		numLayout->addWidget(enemyCorrectNumLabel, 3, 1, Qt::AlignRight);
		numLayout->addWidget(pressContinueLabel, 4, 0, 1, 2, Qt::AlignCenter);
	}

	timeLayout = new QGridLayout(timeWidget);
	timeLayout->addWidget(timeLabel, 0, 0, Qt::AlignLeft);
	timeLayout->addWidget(spendTimeLabel, 1, 1, Qt::AlignRight);
	if(packet.isWin != GAME_SINGLE)
	{
		timeLayout->addWidget(enemySpendTimeLabel, 2, 1, Qt::AlignRight);
	}

	expLayout = new QGridLayout(expWidget);
	expLayout->addWidget(new QLabel(tr("有效单词数")), 0, 0, Qt::AlignLeft);
	expLayout->addWidget(validNumLabel, 0, 1, Qt::AlignRight);
	expLayout->addWidget(new QLabel(tr("基础系数")), 1, 0, Qt::AlignLeft);
	expLayout->addWidget(scaleNumLabel, 1, 1, Qt::AlignRight);
	expLayout->addWidget(new QLabel(tr("难度系数")), 2, 0, Qt::AlignLeft);
	expLayout->addWidget(levelLabel, 2, 1, Qt::AlignRight);
	expLayout->addWidget(new QLabel(tr("对战系数")), 3, 0, Qt::AlignLeft);
	expLayout->addWidget(remainTimeLabel, 3, 1, Qt::AlignRight);
	expLayout->addWidget(new QLabel(tr("———————————————————————————")), 4, 0, 1, 2, Qt::AlignCenter);
	expLayout->addWidget(new QLabel(tr("获得经验")), 5, 0, Qt::AlignLeft);
	expLayout->addWidget(expGainedLabel, 5, 1, Qt::AlignRight);

	stackWidget->addWidget(numWidget);
	stackWidget->addWidget(timeWidget);
	stackWidget->addWidget(expWidget);
}

void EndGameDialog::toNextWidget()
{
	if(state != 2)
	{
		++state;
		stackWidget->setCurrentIndex(state);
	}
	else
		close();
}

void EndGameDialog::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		toNextWidget();
	}
}

void EndGameDialog::keyPressEvent(QKeyEvent *event)
{
	Q_UNUSED(event);
	toNextWidget();
}

