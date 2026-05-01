// KeyScanner.cpp
#include "KeyScanner.h"

KeyScanner::KeyScanner()
{
    keyA = false;
    keyD = false;
    keyS = false;
    keyW = false;
    keySpace = false;
    keyShift = false;
    keyP = false;
    keyR = false;
}

void KeyScanner::refresh()
{
    // Старший бит (0x8000) у GetAsyncKeyState означает «клавиша сейчас нажата».
    keyA = (GetAsyncKeyState('A') & 0x8000) != 0;
    keyD = (GetAsyncKeyState('D') & 0x8000) != 0;
    keyS = (GetAsyncKeyState('S') & 0x8000) != 0;
    keyW = (GetAsyncKeyState('W') & 0x8000) != 0;
    keySpace = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
    keyShift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    keyP = (GetAsyncKeyState('P') & 0x8000) != 0;
    keyR = (GetAsyncKeyState('R') & 0x8000) != 0;
}

bool KeyScanner::isDown(int virtualKey) const
{
    if (virtualKey == 'A')
    {
        return keyA;
    }
    if (virtualKey == 'D')
    {
        return keyD;
    }
    if (virtualKey == 'S')
    {
        return keyS;
    }
    if (virtualKey == 'W')
    {
        return keyW;
    }
    if (virtualKey == VK_SPACE)
    {
        return keySpace;
    }
    if (virtualKey == VK_SHIFT)
    {
        return keyShift;
    }
    if (virtualKey == 'P')
    {
        return keyP;
    }
    if (virtualKey == 'R')
    {
        return keyR;
    }
    return (GetAsyncKeyState(virtualKey) & 0x8000) != 0;
}
