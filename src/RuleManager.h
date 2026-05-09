// RuleManager.h — очки, уровни, комбо, Game Over, ускорение (через выдачу задержки гравитации).
#pragma once

// Класс RuleManager отвечает за правила подсчёта очков и состояния партии.
// Он считает score/level/combo, ускоряет гравитацию по уровню и хранит флаг Game Over.
class RuleManager
{
public:
    RuleManager();

    void reset();

    void onLinesCleared(int lineCount);
    void onNoLinesCleared();

    int getScore() const;
    int getBestScore() const;
    int getLevel() const;
    int getTotalLinesCleared() const;
    int getComboDisplay() const;
    void addPlayTimeMs(int deltaMs);
    int getPlayTimeSeconds() const;

    bool isGameOver() const;
    void setGameOver(bool value);

    // Задержка между шагами гравитации в миллисекундах (уменьшается с уровнем).
    int getGravityDelayMs() const;

private:
    void loadBestScore();
    void saveBestScore() const;

    int score;
    int bestScore;
    int level;
    int totalLinesCleared;
    int comboChain;
    int playTimeMs;

    bool gameOver;
};
