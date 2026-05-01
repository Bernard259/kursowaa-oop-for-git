// CommandMapper.cpp
#include "CommandMapper.h"
#include "KeyScanner.h"

CommandMapper::CommandMapper()
{
    moveLeft = false;
    moveRight = false;
    softDrop = false;
    rotate = false;
    hardDrop = false;
    hold = false;
    pause = false;
    restart = false;
}

void CommandMapper::updateFromKeys(const KeyScanner& keys)
{
    moveLeft = keys.isDown('A');
    moveRight = keys.isDown('D');
    softDrop = keys.isDown('S');
    rotate = keys.isDown('W');
    hardDrop = keys.isDown(VK_SPACE);
    hold = keys.isDown(VK_SHIFT);
    pause = keys.isDown('P');
    restart = keys.isDown('R');
}

bool CommandMapper::getMoveLeft() const
{
    return moveLeft;
}

bool CommandMapper::getMoveRight() const
{
    return moveRight;
}

bool CommandMapper::getSoftDrop() const
{
    return softDrop;
}

bool CommandMapper::getRotate() const
{
    return rotate;
}

bool CommandMapper::getHardDrop() const
{
    return hardDrop;
}

bool CommandMapper::getHold() const
{
    return hold;
}

bool CommandMapper::getPause() const
{
    return pause;
}

bool CommandMapper::getRestart() const
{
    return restart;
}
