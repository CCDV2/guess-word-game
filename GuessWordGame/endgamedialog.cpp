#include "endgamedialog.h"
using std::max;

EndGameDialog::EndGameDialog(GameCache &_gameCache, QWidget *parent):
	QDialog(parent), gameCache(_gameCache)
{
	state = 0;
	createWidget();
	createLayout();
}

void EndGameDialog::createWidget()
{
	headLabel = new QLabel(tr("闯关成功"));

	numWidget = new QWidget();
	numLabel = new QLabel(tr("单词统计:"));
	correctLabel = new QLabel(tr("答对个数：%1个").arg(gameCache.getCorrectNum()));
	wrongLabel = new QLabel(tr("答错单词：%1个").arg(gameCache.getWrongNum()));

	pressContinueLabel = new QLabel(tr("点击继续"));

	expWidget = new QWidget();
	validNumLabel = new QLabel(tr("%1").arg(max(gameCache.getCorrectNum() - gameCache.getWrongNum(), 0)));
	scaleNumLabel = new QLabel(tr("× 50"));
	levelLabel = new QLabel(tr("× %1").arg(DIFFICULTY_SCALE_TABLE[gameCache.getLevel()]));
	remainTimeLabel = new QLabel(tr("× 1"));
	expGainedLabel = new QLabel(tr("%1").arg(gameCache.getExpGained()));

	stackWidget = new QStackedWidget();
}

void EndGameDialog::createLayout()
{
	setWindowFlag(Qt::FramelessWindowHint);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(headLabel, Qt::AlignVCenter);
	mainLayout->addWidget(stackWidget);

	numLayout = new QGridLayout(numWidget);
	numLayout->addWidget(numLabel, 0, 0, Qt::AlignLeft);
	numLayout->addWidget(correctLabel, 0, 1, Qt::AlignRight);
	numLayout->addWidget(wrongLabel, 1, 1, Qt::AlignRight);
	numLayout->addWidget(pressContinueLabel, 2, 0, 1, 2, Qt::AlignCenter);

	expLayout = new QGridLayout(expWidget);
	expLayout->addWidget(new QLabel(tr("有效单词数")), 0, 0, Qt::AlignLeft);
	expLayout->addWidget(validNumLabel, 0, 1, Qt::AlignRight);
	expLayout->addWidget(new QLabel(tr("基础系数")), 1, 0, Qt::AlignLeft);
	expLayout->addWidget(scaleNumLabel, 1, 1, Qt::AlignRight);
	expLayout->addWidget(new QLabel(tr("难度系数")), 2, 0, Qt::AlignLeft);
	expLayout->addWidget(levelLabel, 2, 1, Qt::AlignRight);
	expLayout->addWidget(new QLabel(tr("剩余时间")), 3, 0, Qt::AlignLeft);
	expLayout->addWidget(remainTimeLabel, 3, 1, Qt::AlignRight);
	expLayout->addWidget(new QLabel(tr("———————————————————————————")), 4, 0, 1, 2, Qt::AlignCenter);
	expLayout->addWidget(new QLabel(tr("获得经验")), 5, 0, Qt::AlignLeft);
	expLayout->addWidget(expGainedLabel, 5, 1, Qt::AlignRight);

	stackWidget->addWidget(numWidget);
	stackWidget->addWidget(expWidget);
}

void EndGameDialog::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		if(state == 0)
		{
			++state;
			stackWidget->setCurrentWidget(expWidget);
		}
		else
			close();
	}
}

