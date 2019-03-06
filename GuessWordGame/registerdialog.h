#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H


#include<QWidget>
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QGridLayout>
#include<QHBoxLayout>

class RegisterDialog : public QDialog
{
public:
	explicit RegisterDialog(QWidget *parent = nullptr);
private:
	void createLabel();
	void createLayout();
	void createConnection();

	QLabel *userNameLabel, *passwordLabel, *recheckPasswordLabel;
	QLineEdit *userNameLineEdit, *passwordLineEdit, *recheckPasswordLineEdit;
	QPushButton *submitButton, *cancelButton;
	QGridLayout *mainLayout;
	QHBoxLayout *buttonLayout;
};

#endif // REGISTERDIALOG_H
