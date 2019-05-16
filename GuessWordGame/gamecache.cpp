#include "gamecache.h"


// GameCahe class
void GameCache::setWords(QVector<Word> _words)
{
	words = _words;
	ready = true;
}

bool GameCache::nextWord()
{
	++wordi;
	if(wordi == words.length()) return false;
	timeLength = LEVEL_TIME_TABLE[words[wordi].getLevel()] / TIME_INTERVAL;
	return true;
}

QString GameCache::getCurrentWord() const
{
	return words[wordi].getWord();
}

int GameCache::getCurrentLevel() const
{
	return words[wordi].getLevel();
}

void GameCache::increaseExp(int incExp)
{
	expGained += incExp;
}

void GameCache::increaseCorrectNum(int inc)
{
	correctNum += inc;
}

void GameCache::increaseWrongNum(int inc)
{
	wrongNum += inc;
}

bool GameCache::decreaseTimeLength(int dec)
{
	timeLength -= dec;
	if(timeLength <= 0) return false;
	else return true;
}

void GameCache::reset(GameLevel _level, GameStatus _status)
{
	wordi = -1;
	correctNum = -1;
	wrongNum = 0;
	expGained = 0;
	timeLength = 0;
	ready = false;
	level = _level;
	totalTypingTime = 0;
	status = _status;
}

bool GameCache::isReady()
{
	return ready;
}

int GameCache::getTimeLength() const
{
	return timeLength;
}

int GameCache::getCorrectNum() const
{
	return correctNum;
}

int GameCache::getWrongNum() const
{
	return wrongNum;
}

GameLevel GameCache::getLevel() const
{
	return level;
}

int GameCache::getExpGained() const
{
	return expGained;
}

void GameCache::setExpGained(int value)
{
	expGained = value;
}

void GameCache::startCountTime()
{
	typingTimer.start();

}

void GameCache::endCountTime()
{
	totalTypingTime += typingTimer.elapsed();
}

int GameCache::getTotalTime()
{
	return totalTypingTime;
}

EndGamePacket GameCache::toEndGamePacket(QString player)
{
	return EndGamePacket(player, level, correctNum, wrongNum, totalTypingTime, 0, 0, status, 0);
}
