#include "questionwidget.h"

QuestionWidget::QuestionWidget(DatabaseServer &_DBserver, QWidget *parent):
	QWidget(parent), DBserver(_DBserver)
{
	createWidget();
	createLayout();
	createConnection();
}

void QuestionWidget::createWidget()
{
	importButton = new QPushButton(tr("导入"));
	submitButton = new QPushButton(tr("提交"));
	checkButton = new QPushButton(tr("检查"));

	tableWidget = new QTableWidget();

}

void QuestionWidget::createLayout()
{
	buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(importButton);
	buttonLayout->addWidget(submitButton);
	buttonLayout->addWidget(checkButton);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(tableWidget);
	mainLayout->addLayout(buttonLayout);
}

void QuestionWidget::createConnection()
{

}
