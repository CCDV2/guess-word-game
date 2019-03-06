#include "user.h"

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
