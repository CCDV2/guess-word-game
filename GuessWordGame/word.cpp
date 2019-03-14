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
