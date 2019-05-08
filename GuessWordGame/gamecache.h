#ifndef GAMECACHE_H
#define GAMECACHE_H

#include<QVector>
#include"word.h"
#include<QString>
#include"datastructure.h"
#include<QTime>

class GameCache
{
public:
	void setWords(QVector<Word> _words);

	bool nextWord();
	QString getCurrentWord() const;
	int getCurrentLevel() const;
	void increaseExp(int incExp);
	void increaseCorrectNum(int inc = 1);
	void increaseWrongNum(int inc = 1);
	bool decreaseTimeLength(int dec = 1);
	void reset(GameLevel _level);
	bool isReady();
	int getTimeLength() const;

	int getCorrectNum() const;

	int getWrongNum() const;

	GameLevel getLevel() const;

	int getExpGained() const;
	void setExpGained(int value);

	void startCountTime();
	void pauseCountTime();
	void resumeCountTime();
	void endCountTime();
	int getTotalTime();

	EndGamePacket toEndGamePacket(QString player);
private:
	int timeLength;

	QVector<Word> words;
	int wordi;

	int correctNum, wrongNum;
	int expGained;
	bool ready;
	GameLevel level;
	QTime typingTimer;
	int totalTypingTime;
};

#endif // GAMECACHE_H
