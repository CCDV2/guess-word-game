#include "mainwindow.h"
#include <QApplication>

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
	qDebug() << a.styleSheet();
	file.close();

	MainWindow w;
	w.show();

	return a.exec();
}
