#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class LoginWindow : public QWidget
{
	Q_OBJECT
public:
	explicit LoginWindow(QWidget *parent = nullptr);

signals:

public slots:

private:
	QLineEdit *userName, *passWord;
	QPushButton *submitButton;
};

#endif // LOGINWINDOW_H
