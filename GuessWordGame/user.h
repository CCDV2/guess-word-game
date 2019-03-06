#ifndef USER_H
#define USER_H

#include<QString>

class User
{
public:
	User(QString _userName);
	QString getUserName() const;
	void setUserName(const QString &value);

protected:
	QString userName;
};

class Player: User
{

public:
	Player(QString _userName, int _level, int _experience, int _playNum);

	int getLevel() const;

	int getExperience() const;

	int getPlayNum() const;

	void setLevel(int value);

	void setExperience(int value);

	void setPlayNum(int value);

private:
	int level, experience;
	int playNum;

};

class Questioner: User
{

public:
	Questioner(QString _userName, int _level, int _experience, int _questionNum);

	int getLevel() const;
	void setLevel(int value);

	int getExperience() const;
	void setExperience(int value);

	int getQuestionNum() const;
	void setQuestionNum(int value);

private:
	int level, experience;
	int questionNum;
};

#endif // USER_H
