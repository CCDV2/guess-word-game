#ifndef BATTLECHOOSEDIALOG_H
#define BATTLECHOOSEDIALOG_H

#include<QDialog>
#include<QLabel>
#include<QPushButton>
#include<QCheckBox>
#include<QGridLayout>
#include<QSlider>
#include<QLineEdit>
#include"datastructure.h"

class BattleChooseDialog: public QDialog
{
	Q_OBJECT
public:
	explicit BattleChooseDialog(BattlePacket &_packet, QWidget *parent = nullptr);



private slots:
	void on_easyButton_clicked();
	void on_normalButton_clicked();
	void on_hardButton_clicked();
	void on_expertButton_clicked();
	void changeNumText(int _num);
	void changeNumSlider(QString _num);
private:
	void createWidget();
	void createLayout();
	void createConnection();

	QSlider *numSlider;
	QLabel *numSelectLabel;
	QLineEdit *numLineEdit;
	QPushButton *easyButton, *normalButton, *hardButton, *expertButton;
	QLabel *modeSelectLabel;

	QGridLayout *mainLayout;
	int num;
	BattlePacket &packet;
};

#endif // BATTLECHOOSEDIALOG_H
