// MovementController.cpp
#include "MovementController.h"
#include "ActivePiece.h"
#include "GhostPiece.h"
#include "GridModel.h"
#include "LineClearingSystem.h"
#include "RuleManager.h"
#include "SequenceGenerator.h"

MovementController::MovementController()
{
    grid = nullptr;
    active = nullptr;
    ghost = nullptr;
    sequence = nullptr;
    lineSystem = nullptr;
    rules = nullptr;
    holdPieceType = -1;
    canHold = true;
}

void MovementController::setGrid(GridModel* gridPtr)
{
    grid = gridPtr;
}

void MovementController::setActivePiece(ActivePiece* piecePtr)
{
    active = piecePtr;
}

void MovementController::setGhostPiece(GhostPiece* ghostPtr)
{
    ghost = ghostPtr;
}

void MovementController::setSequence(SequenceGenerator* seqPtr)
{
    sequence = seqPtr;
}

void MovementController::setLineSystem(LineClearingSystem* linePtr)
{
    lineSystem = linePtr;
}

void MovementController::setRules(RuleManager* rulesPtr)
{
    rules = rulesPtr;
}

void MovementController::beginNewGame()
{
    holdPieceType = -1;
    canHold = true;
    if (rules != nullptr)
    {
        rules->setGameOver(false);
    }
    spawnNextPiece();
}

bool MovementController::spawnPieceOfType(int pieceType)
{
    if (active == nullptr || grid == nullptr || rules == nullptr)
    {
        return false;
    }

    active->setType(pieceType);
    active->setRotation(0);
    active->setPosition(3, 0);

    if (!grid->canPlaceShape(active->getType(), active->getRotation(), active->getBoardX(), active->getBoardY()))
    {
        rules->setGameOver(true);
        return false;
    }

    if (ghost != nullptr)
    {
        ghost->updateFrom(*active, *grid);
    }

    return true;
}

bool MovementController::spawnNextPiece()
{
    if (sequence == nullptr)
    {
        return false;
    }
    int nextType = sequence->nextPieceType();
    return spawnPieceOfType(nextType);
}

bool MovementController::tryMoveLeft()
{
    if (active == nullptr || grid == nullptr)
    {
        return false;
    }
    int newX = active->getBoardX() - 1;
    int y = active->getBoardY();
    if (!grid->canPlaceShape(active->getType(), active->getRotation(), newX, y))
    {
        return false;
    }
    active->setPosition(newX, y);
    if (ghost != nullptr)
    {
        ghost->updateFrom(*active, *grid);
    }
    return true;
}

bool MovementController::tryMoveRight()
{
    if (active == nullptr || grid == nullptr)
    {
        return false;
    }
    int newX = active->getBoardX() + 1;
    int y = active->getBoardY();
    if (!grid->canPlaceShape(active->getType(), active->getRotation(), newX, y))
    {
        return false;
    }
    active->setPosition(newX, y);
    if (ghost != nullptr)
    {
        ghost->updateFrom(*active, *grid);
    }
    return true;
}

bool MovementController::tryMoveDown()
{
    if (active == nullptr || grid == nullptr)
    {
        return false;
    }
    int x = active->getBoardX();
    int newY = active->getBoardY() + 1;
    if (!grid->canPlaceShape(active->getType(), active->getRotation(), x, newY))
    {
        return false;
    }
    active->setPosition(x, newY);
    if (ghost != nullptr)
    {
        ghost->updateFrom(*active, *grid);
    }
    return true;
}

bool MovementController::tryRotateClockwise()
{
    if (active == nullptr || grid == nullptr)
    {
        return false;
    }

    int currentRotation = active->getRotation();
    int nextRotation = (currentRotation + 1) % 4;

    int baseX = active->getBoardX();
    int baseY = active->getBoardY();

    // Простые смещения (упрощённый «wall kick»): пробуем несколько вариантов.
    const int kickCount = 6;
    const int kickOffsets[kickCount][2] = {
        {0, 0},
        {-1, 0},
        {1, 0},
        {0, -1},
        {-2, 0},
        {2, 0},
    };

    for (int i = 0; i < kickCount; i++)
    {
        int tryX = baseX + kickOffsets[i][0];
        int tryY = baseY + kickOffsets[i][1];
        if (grid->canPlaceShape(active->getType(), nextRotation, tryX, tryY))
        {
            active->setRotation(nextRotation);
            active->setPosition(tryX, tryY);
            if (ghost != nullptr)
            {
                ghost->updateFrom(*active, *grid);
            }
            return true;
        }
    }

    return false;
}

void MovementController::hardDrop()
{
    if (active == nullptr || grid == nullptr)
    {
        return;
    }
    while (tryMoveDown())
    {
        // Падаем до упора.
    }
    lockPiece();
}

bool MovementController::tryHold()
{
    if (active == nullptr || grid == nullptr || sequence == nullptr || rules == nullptr)
    {
        return false;
    }
    if (!canHold)
    {
        return false;
    }

    canHold = false;
    int currentType = active->getType();

    if (holdPieceType < 0)
    {
        holdPieceType = currentType;
        return spawnNextPiece();
    }

    int buffer = holdPieceType;
    holdPieceType = currentType;
    return spawnPieceOfType(buffer);
}

void MovementController::lockPiece()
{
    if (active == nullptr || grid == nullptr || lineSystem == nullptr || rules == nullptr || sequence == nullptr)
    {
        return;
    }

    int colorIndex = active->getType() + 1;
    grid->mergePiece(
        active->getType(),
        active->getRotation(),
        active->getBoardX(),
        active->getBoardY(),
        colorIndex);

    lineSystem->process(*grid, *rules);

    canHold = true;

    if (!rules->isGameOver())
    {
        spawnNextPiece();
    }
}

int MovementController::getHoldPieceType() const
{
    return holdPieceType;
}

bool MovementController::getCanHold() const
{
    return canHold;
}
