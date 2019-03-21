#include "questionwidget.h"
#include<QHeaderView>
#include<QKeyEvent>
#include<QModelIndex>
#include<QMessageBox>

QuestionWidget::QuestionWidget(DatabaseServer &_DBserver, QWidget *parent):
	QWidget(parent), DBserver(_DBserver)
{
	createWidget();
	createLayout();
	createConnection();
}

void QuestionWidget::receiveAddedWords(int count)
{
	QMessageBox::information(this, tr("导入成功"), tr("您成功导入了%1个单词").arg(count));
}

void QuestionWidget::createWidget()
{
	importButton = new QPushButton(tr("导入并提交"));
	submitButton = new QPushButton(tr("提交"));
	checkButton = new QPushButton(tr("检查"));

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
	buttonLayout->addWidget(checkButton);
	buttonLayout->addWidget(submitButton);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(tableWidget);
	mainLayout->addLayout(buttonLayout);
}

void QuestionWidget::createConnection()
{
	connect(submitButton, &QPushButton::clicked, this, &QuestionWidget::on_submitButton_clicked);
	connect(this, &QuestionWidget::sendQuestionWordList, &DBserver, &DatabaseServer::receiveQuestionWordList);
	connect(&DBserver, &DatabaseServer::sendAddedWords, this, &QuestionWidget::receiveAddedWords);
}

void QuestionWidget::showImportDialog(QVector<Word> words)
{

}

void QuestionWidget::on_importButton_clicked()
{
}

void QuestionWidget::on_submitButton_clicked()
{
	QVector<Word> words;
	for(int i = 0; i < tableWidget->rowCount(); ++i)
	{
		if(tableWidget->item(i, 0) == nullptr || tableWidget->item(i, 1) == nullptr) continue;
		QString word = tableWidget->item(i, 0)->text();
		if(word.isEmpty()) continue;
		bool ok;
		int level = tableWidget->item(i, 1)->text().toInt(&ok);
		if(!ok) continue;
		words.push_back(Word(word, level));
	}
	emit sendQuestionWordList(words);
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
