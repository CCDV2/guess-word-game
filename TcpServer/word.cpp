#include "word.h"

Word::Word(QString _word, int _level):
	word(_word), level(_level)
{

}

QString Word::getWord() const
{
	return word;
}

void Word::setWord(const QString &value)
{
	word = value;
}

int Word::getLevel() const
{
	return level;
}

void Word::setLevel(int value)
{
	level = value;
}

const QString Word::toString()
{
	QString ret = word + '.' + QString::number(level);
	return ret;
}

const Word Word::fromString(QString s)
{
	QStringList list = s.split('.');
	return Word(list[0], list[1].toInt());
}

const QString Word::specialWord(bool isStart)
{
	if(isStart)
		return "__start.0";
	else
		return "__end.0";
}
