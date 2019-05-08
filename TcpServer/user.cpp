#include "user.h"

#include<QObject>

User::User(QString _userName): userName(_userName)
{

}

QString User::getUserName() const
{
	return userName;
}

void User::setUserName(const QString &value)
{
	userName = value;
}

Player::Player(QString _userName, int _level, int _experience, int _playNum):
	User(_userName), level(_level), experience(_experience), playNum(_playNum)
{

}


int Player::getLevel() const
{
	return level;
}

int Player::getExperience() const
{
	return experience;
}

int Player::getPlayNum() const
{
	return playNum;
}

void Player::setLevel(int value)
{
	level = value;
}

void Player::setExperience(int value)
{
	experience = value;
}

void Player::setPlayNum(int value)
{
	playNum = value;
}

const QString Player::toString()
{
	QString ret = userName + '.' + QObject::tr("%1.%2.%3").arg(level).arg(experience).arg(playNum);
	return ret;
}

const Player Player::fromString(QString s)
{
	QStringList list = s.split('.');
	return Player(list[0], list[1].toInt(), list[2].toInt(), list[3].toInt());
}

const QString Player::specialPlayer(int sortMehtod, bool isStart)
{
	if(isStart)
		return QObject::tr("__start.%1.0.0").arg(sortMehtod);
	else
		return QObject::tr("__end.%1.0.0").arg(sortMehtod);
}

Questioner::Questioner(QString _userName, int _level, int _experience, int _questionNum):
	User(_userName), level(_level), experience(_experience), questionNum(_questionNum)
{

}


int Questioner::getLevel() const
{
	return level;
}

void Questioner::setLevel(int value)
{
	level = value;
}

int Questioner::getExperience() const
{
	return experience;
}

void Questioner::setExperience(int value)
{
	experience = value;
}

int Questioner::getQuestionNum() const
{
	return questionNum;
}

void Questioner::setQuestionNum(int value)
{
	questionNum = value;
}

const QString Questioner::toString()
{
	QString ret = userName + '.' + QObject::tr("%1.%2.%3").arg(level).arg(experience).arg(questionNum);
	return ret;
}

const Questioner Questioner::fromString(QString s)
{
	QStringList list = s.split('.');
	return Questioner(list[0], list[1].toInt(), list[2].toInt(), list[3].toInt());
}

const QString Questioner::specialQuestioner(int sortMehtod, bool isStart)
{
	if(isStart)
		return QObject::tr("__start.%1.0.0").arg(sortMehtod);
	else
		return QObject::tr("__end.%1.0.0").arg(sortMehtod);
}
