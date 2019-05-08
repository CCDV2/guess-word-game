#ifndef WORD_H
#define WORD_H

#include<QVector>
#include<QObject>

class Word
{
public:
	Word(QString _word = "", int _level = 0);
	QString getWord() const;
	void setWord(const QString &value);

	int getLevel() const;
	void setLevel(int value);
	const QString toString();
	static const Word fromString(QString s);
	static const QString specialWord(bool isStart = true);
private:
	QString word;
	int level;
};

const Word initWords[] =
{
	{QObject::tr("apple"), 1},
	{QObject::tr("banana"), 1},
	{QObject::tr("pear"), 1},
};


#endif // WORD_H
