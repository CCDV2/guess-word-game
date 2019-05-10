#include "battlechoosedialog.h"
#include<QRegExpValidator>
#include<QMessageBox>

BattleChooseDialog::BattleChooseDialog(BattlePacket &_packet, QWidget *parent):
	QDialog(parent), packet(_packet)
{
	setAttribute(Qt::WA_DeleteOnClose);
	createWidget();
	createLayout();
	createConnection();
}

void BattleChooseDialog::on_easyButton_clicked()
{
	packet.self = "__selected";
	packet.level = EASY;
	close();
}

void BattleChooseDialog::on_normalButton_clicked()
{
	packet.self = "__selected";
	packet.level = NORMAL;
	close();
}

void BattleChooseDialog::on_hardButton_clicked()
{
	packet.self = "__selected";
	packet.level = HARD;
	close();
}

void BattleChooseDialog::on_expertButton_clicked()
{
	packet.self = "__selected";
	packet.level = EXPERT;
	close();
}

void BattleChooseDialog::changeNumText(int _num)
{
	num = _num;
	numLineEdit->setText(QString::number(num));
	packet.wordNum = num;
}

void BattleChooseDialog::changeNumSlider(QString _num)
{
	if(_num.isEmpty() || (num = _num.toInt()) == 0)
	{
		easyButton->setEnabled(false);
		normalButton->setEnabled(false);
		hardButton->setEnabled(false);
		expertButton->setEnabled(false);
		return;
	}
	easyButton->setEnabled(true);
	normalButton->setEnabled(true);
	hardButton->setEnabled(true);
	expertButton->setEnabled(true);
	if(num > 50) num = 50;
	if(num < 1) num = 1;
	numSlider->setValue(num);
	packet.wordNum = num;
}

void BattleChooseDialog::createWidget()
{
	numSelectLabel = new QLabel(tr("请选择题数:"));
	numLineEdit = new QLineEdit(tr("5"));
	numLineEdit->setValidator(new QIntValidator(1, 50, this));
	numSlider = new QSlider(Qt::Horizontal);
	numSlider->setRange(1, 50);
	numSlider->setValue(5);
	num = 5;
	modeSelectLabel = new QLabel(tr("请选择游戏难度"));
	easyButton = new QPushButton(tr("EASY"));
	normalButton = new QPushButton(tr("NORMAL"));
	hardButton = new QPushButton(tr("HARD"));
	expertButton = new QPushButton(tr("EXPERT"));
}

void BattleChooseDialog::createLayout()
{
	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(numSelectLabel, 0, 0);
	mainLayout->addWidget(numLineEdit, 0, 1);
	mainLayout->addWidget(numSlider, 1, 0, 1, 2);
	mainLayout->addWidget(modeSelectLabel, 2, 0, 1, 2);
	mainLayout->addWidget(easyButton, 3, 0);
	mainLayout->addWidget(normalButton, 3, 1);
	mainLayout->addWidget(hardButton, 4, 0);
	mainLayout->addWidget(expertButton, 4, 1);
}

void BattleChooseDialog::createConnection()
{
	connect(easyButton, &QPushButton::clicked, this, &BattleChooseDialog::on_easyButton_clicked);
	connect(normalButton, &QPushButton::clicked, this, &BattleChooseDialog::on_normalButton_clicked);
	connect(hardButton, &QPushButton::clicked, this, &BattleChooseDialog::on_hardButton_clicked);
	connect(expertButton, &QPushButton::clicked, this, &BattleChooseDialog::on_expertButton_clicked);

	connect(numSlider, &QSlider::valueChanged, this, &BattleChooseDialog::changeNumText);
	connect(numLineEdit, &QLineEdit::textChanged, this, &BattleChooseDialog::changeNumSlider);

}


