#include "questionwidget.h"
#include<QHeaderView>
#include<QKeyEvent>
#include<QModelIndex>
#include<QMessageBox>
#include<QFileDialog>
#include<QThread>
#include<QStyleOption>
#include<QPainter>

QuestionWidget::QuestionWidget(DatabaseServer &_DBserver, QWidget *parent):
	QWidget(parent), DBserver(_DBserver)
{
	questionerName = "";
	createWidget();
	createLayout();
	createConnection();
}

void QuestionWidget::receiveAddedWords(int count, int expGained)
{
	QMessageBox::information(this, tr("导入成功"), tr("您成功导入了%1个单词\n增加经验：%2").arg(count).arg(expGained));
}

void QuestionWidget::receiveQuestionerName(QString _questionerName)
{
	questionerName = _questionerName;
}

void QuestionWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption styleOpt;
	styleOpt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void QuestionWidget::createWidget()
{
	importButton = new QPushButton(tr("导入"));
	submitButton = new QPushButton(tr("提交"));
	clearButton = new QPushButton(tr("清空"));

	tableWidget = new QTableWidget();
	tableWidget->setSortingEnabled(true);
	tableWidget->setColumnCount(2);
	tableWidget->setHorizontalHeaderLabels({tr("单词"), tr("等级")});
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableWidget->setRowCount(1);

}

void QuestionWidget::createLayout()
{
	buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(importButton);
	buttonLayout->addWidget(clearButton);
	buttonLayout->addWidget(submitButton);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(tableWidget);
	mainLayout->addLayout(buttonLayout);
}

void QuestionWidget::createConnection()
{
	connect(submitButton, &QPushButton::clicked, this, &QuestionWidget::on_submitButton_clicked);
	connect(clearButton, &QPushButton::clicked, this, &QuestionWidget::on_clearButton_clicked);
	connect(importButton, &QPushButton::clicked, this, &QuestionWidget::on_importButton_clicked);
	connect(this, &QuestionWidget::sendQuestionWordList, &DBserver, &DatabaseServer::receiveQuestionWordList);
	connect(&DBserver, &DatabaseServer::sendAddedWords, this, &QuestionWidget::receiveAddedWords);
}

void QuestionWidget::showImportDialog(QVector<Word> words)
{
	tableWidget->setRowCount(words.size());
	int cnt = 0;
	for(auto word : words)
	{
		tableWidget->setItem(cnt, 0, new QTableWidgetItem(word.getWord()));
		tableWidget->setItem(cnt, 1, new QTableWidgetItem(tr("%1").arg(word.getLevel())));
		++cnt;
	}
}

void QuestionWidget::on_importButton_clicked()
{
	QVector<Word> words;
	QString fileName = QFileDialog::getOpenFileName(this, tr("导入文件"), tr("."), tr("csv文件(*.csv)"));
	if(!fileName.isEmpty())
	{
		QFile file(fileName);
		if(file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QTextStream in(&file);
			while(!in.atEnd())
			{
				QString line = in.readLine();
				auto lists = line.split(',');
				QString word = lists[0];
				bool ok;
				int level = lists[1].toInt(&ok);
				if(word.isEmpty() || !ok) continue;
				words.push_back(Word(word, level));
			}
			showImportDialog(words);
		}
		else
			QMessageBox::warning(this, tr("打开文件失败"), tr("打开文件失败，请检查读写类型"));
	}
}

void QuestionWidget::on_clearButton_clicked()
{
	tableWidget->clearContents();
	tableWidget->setRowCount(1);
}

void QuestionWidget::on_submitButton_clicked()
{
	QVector<Word> words;
	emit requireQuestionerName();
	while(questionerName.isEmpty())
	{
		QThread::sleep(100);
		qDebug() << "waiting";
	}
	for(int i = 0; i < tableWidget->rowCount(); ++i)
	{
		if(tableWidget->item(i, 0) == nullptr || tableWidget->item(i, 1) == nullptr) continue;
		QString word = tableWidget->item(i, 0)->text();
		if(word.isEmpty()) continue;
		bool ok;
		int level = tableWidget->item(i, 1)->text().toInt(&ok);
		if(!ok) continue;
		if(level < MIN_WORD_LEVEL || level > MAX_WORD_LEVEL) continue;
		words.push_back(Word(word, level));
	}
	emit sendQuestionWordList(words, questionerName);
}

void QuestionWidget::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
	{
		addNewLine();
	}
}

void QuestionWidget::addNewLine()
{
	tableWidget->insertRow(tableWidget->rowCount());
	tableWidget->setCurrentCell(tableWidget->rowCount() - 1, 0);
}
