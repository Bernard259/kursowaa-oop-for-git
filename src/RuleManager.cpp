// RuleManager.cpp
#include "RuleManager.h"

RuleManager::RuleManager()
{
    reset();
}

void RuleManager::reset()
{
    score = 0;
    level = 1;
    totalLinesCleared = 0;
    comboChain = 0;
    playTimeMs = 0;
    gameOver = false;
}

void RuleManager::onLinesCleared(int lineCount)
{
    if (lineCount <= 0 || lineCount > 4)
    {
        onNoLinesCleared();
        return;
    }

    int basePoints = 0;
    if (lineCount == 1)
    {
        basePoints = 100;
    }
    else if (lineCount == 2)
    {
        basePoints = 300;
    }
    else if (lineCount == 3)
    {
        basePoints = 500;
    }
    else
    {
        basePoints = 800;
    }

    int levelMultiplier = level;
    if (levelMultiplier < 1)
    {
        levelMultiplier = 1;
    }

    int gained = basePoints * levelMultiplier;

    // Комбо: бонус за подряд идущие очистки (после первой успешной очистки цепочка растёт).
    if (comboChain > 0)
    {
        int comboBonus = 50 * levelMultiplier * comboChain * lineCount;
        gained = gained + comboBonus;
    }

    comboChain = comboChain + 1;

    score = score + gained;
    totalLinesCleared = totalLinesCleared + lineCount;

    // Каждые 10 собранных линий — новый уровень.
    int newLevel = 1 + (totalLinesCleared / 10);
    if (newLevel > level)
    {
        level = newLevel;
    }
}

void RuleManager::onNoLinesCleared()
{
    comboChain = 0;
}

int RuleManager::getScore() const
{
    return score;
}

int RuleManager::getLevel() const
{
    return level;
}

int RuleManager::getTotalLinesCleared() const
{
    return totalLinesCleared;
}

int RuleManager::getComboDisplay() const
{
    return comboChain;
}

void RuleManager::addPlayTimeMs(int deltaMs)
{
    if (deltaMs > 0)
    {
        playTimeMs = playTimeMs + deltaMs;
    }
}

int RuleManager::getPlayTimeSeconds() const
{
    return playTimeMs / 1000;
}

bool RuleManager::isGameOver() const
{
    return gameOver;
}

void RuleManager::setGameOver(bool value)
{
    gameOver = value;
}

int RuleManager::getGravityDelayMs() const
{
    // Чем выше уровень, тем меньше задержка (быстрее падает фигура).
    int delay = 800 - (level - 1) * 55;
    if (delay < 80)
    {
        delay = 80;
    }
    return delay;
}
