#include <QCoreApplication>

#include<iostream>
using std::min;
using std::cout;
//using std::endl;
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QHash>

int getLevel(QString s)
{
	int length = s.length();
	if(length <= 2)
	{
		return 1;
	}
	else
	{
		assert(length > 2);
		return min(length - 1, 10);
	}
}



int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QFile textIn("wordlist.csv");

	QHash<QString, int> map;

	int count = 40;
	if(textIn.open(QIODevice::ReadOnly))
	{
		QTextStream in(&textIn);
		QString line = in.readLine();
		while(!line.isEmpty())
		{
			QStringList list = line.split(' ');
			for(auto word : list)
			{
				word = word.trimmed();
				if(word.isEmpty()) continue;
				word = word.toLower();

				map[word] = getLevel(word);

			}


			line = in.readLine();
		}
		textIn.close();
	}


	QFile textOut("toImport.csv");
	textOut.open(QIODevice::WriteOnly);
	QTextStream out(&textOut);

	for(auto word = map.begin(); word != map.end(); ++word)
	{
		out << word.key() << ',' << word.value() << endl;
	}
	textOut.close();

	a.quit();
	return 0;
//	return a.exec();
}
