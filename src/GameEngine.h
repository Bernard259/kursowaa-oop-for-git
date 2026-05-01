#pragma once
#include "IRenderer.h"
#include "ActivePiece.h"
#include "CommandMapper.h"
#include "GhostPiece.h"
#include "GridModel.h"
#include "KeyScanner.h"
#include "LineClearingSystem.h"
#include "MovementController.h"
#include "RuleManager.h"
#include "SequenceGenerator.h"

class GameEngine {
public:
    // Конструктор теперь принимает указатель на любой рендерер
    GameEngine(IRenderer* rendererInstance);

    void run();

private:
    void restartRound();
    void handleEdgeCommands();

    // Указатель на интерфейс отрисовки
    IRenderer* renderer;

    GridModel grid;
    ActivePiece activePiece;
    GhostPiece ghostPiece;
    SequenceGenerator sequence;
    KeyScanner keyScanner;
    CommandMapper commandMapper;
    LineClearingSystem lineClearer;
    RuleManager rules;
    MovementController movement;

    bool paused;
    bool previousPauseKey;
    bool previousRestartKey;
    bool previousHoldKey;
    bool previousRotateKey;
    bool previousHardDropKey;
    int leftRepeatTimer;
    int rightRepeatTimer;
    unsigned long lastGravityTick;
};