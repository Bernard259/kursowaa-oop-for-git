#include "GameEngine.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

GameEngine::GameEngine(IRenderer* rendererInstance)
    : renderer(rendererInstance) {
    movement.setGrid(&grid);
    movement.setActivePiece(&activePiece);
    movement.setGhostPiece(&ghostPiece);
    movement.setSequence(&sequence);
    movement.setLineSystem(&lineClearer);
    movement.setRules(&rules);

    paused = false;
    previousPauseKey = false;
    previousRestartKey = false;
    previousHoldKey = false;
    previousRotateKey = false;
    previousHardDropKey = false;
    leftRepeatTimer = 0;
    rightRepeatTimer = 0;
    lastGravityTick = 0;

    restartRound();
}

void GameEngine::run() {
    while (true) {
        keyScanner.refresh();
        if (keyScanner.isDown(VK_ESCAPE)) {
            break;
        }
        commandMapper.updateFromKeys(keyScanner);
        handleEdgeCommands();

        if (!paused && !rules.isGameOver()) {
            if (commandMapper.getMoveLeft()) {
                if (leftRepeatTimer <= 0) {
                    movement.tryMoveLeft();
                    leftRepeatTimer = 3;
                } else {
                    leftRepeatTimer = leftRepeatTimer - 1;
                }
            } else {
                leftRepeatTimer = 0;
            }

            if (commandMapper.getMoveRight()) {
                if (rightRepeatTimer <= 0) {
                    movement.tryMoveRight();
                    rightRepeatTimer = 3;
                } else {
                    rightRepeatTimer = rightRepeatTimer - 1;
                }
            } else {
                rightRepeatTimer = 0;
            }

            if (commandMapper.getSoftDrop()) {
                if (!movement.tryMoveDown()) {
                    movement.lockPiece();
                }
            }

            unsigned long nowTick = GetTickCount();
            if (nowTick - lastGravityTick >= static_cast<unsigned long>(rules.getGravityDelayMs())) {
                if (!movement.tryMoveDown()) {
                    movement.lockPiece();
                }
                lastGravityTick = nowTick;
            }
        }

        renderer->renderFrame(grid, activePiece, ghostPiece, rules, movement, sequence, paused, rules.isGameOver());
        Sleep(16);
    }
}

void GameEngine::restartRound() {
    grid.clear();
    sequence.reset();
    rules.reset();
    movement.beginNewGame();
    paused = false;
    previousPauseKey = false;
    previousRestartKey = false;
    previousHoldKey = false;
    previousRotateKey = false;
    previousHardDropKey = false;
    leftRepeatTimer = 0;
    rightRepeatTimer = 0;
    lastGravityTick = GetTickCount();
}

void GameEngine::handleEdgeCommands() {
    bool pauseKey = commandMapper.getPause();
    if (pauseKey && !previousPauseKey) {
        paused = !paused;
    }
    previousPauseKey = pauseKey;

    bool restartKey = commandMapper.getRestart();
    if (restartKey && !previousRestartKey) {
        restartRound();
        return;
    }
    previousRestartKey = restartKey;

    if (paused || rules.isGameOver()) {
        previousHoldKey = commandMapper.getHold();
        previousRotateKey = commandMapper.getRotate();
        previousHardDropKey = commandMapper.getHardDrop();
        return;
    }

    bool holdKey = commandMapper.getHold();
    if (holdKey && !previousHoldKey) {
        movement.tryHold();
    }
    previousHoldKey = holdKey;

    bool rotateKey = commandMapper.getRotate();
    if (rotateKey && !previousRotateKey) {
        movement.tryRotateClockwise();
    }
    previousRotateKey = rotateKey;

    bool hardDropKey = commandMapper.getHardDrop();
    if (hardDropKey && !previousHardDropKey) {
        movement.hardDrop();
    }
    previousHardDropKey = hardDropKey;
}