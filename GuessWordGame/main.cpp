#include "mainwindow.h"
#include <QApplication>

#include<QSplashScreen>
#include<QMessageBox>
#include"tcpclient.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFile file(":/qss/qss/mystyle.qss");
	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug("Can't open the style sheet file.");
	}
	QString qss = QLatin1String(file.readAll());
	a.setStyleSheet(qss);
	file.close();


	QPixmap pixmap(":/png/img/20130707105529296.jpg");
	QSplashScreen splash(pixmap);
	splash.show();
	a.processEvents();
	splash.showMessage(QObject::tr("正在初始化.."));
	a.processEvents();

	MainWindow w;
	w.show();
	splash.finish(&w);

	return a.exec();
}
