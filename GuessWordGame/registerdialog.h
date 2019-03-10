#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H


#include<QWidget>
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QGridLayout>
#include<QHBoxLayout>
#include"datastructure.h"
#include"databaseserver.h"

class RegisterDialog : public QDialog
{
	Q_OBJECT
public:
	explicit RegisterDialog(DatabaseServer &_DBServer, QWidget *parent = nullptr);
signals:
	void sendRegisterPackage(RegisterPackage package);
public slots:
	void receiveRegisterState(RegisterState state);
private slots:
	void on_submitButton_clicked();

private:
	void createLabel();
	void createLayout();
	void createConnection();

	QLabel *userNameLabel, *passwordLabel, *recheckPasswordLabel;
	QLineEdit *userNameLineEdit, *passwordLineEdit, *recheckPasswordLineEdit;
	QPushButton *submitButton, *cancelButton;
	QGridLayout *mainLayout;
	QHBoxLayout *buttonLayout;
	DatabaseServer &DBserver;
};

#endif // REGISTERDIALOG_H
