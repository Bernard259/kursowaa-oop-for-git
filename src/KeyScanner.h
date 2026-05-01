// KeyScanner.h — только чтение состояния клавиш через WinAPI (без игровой логики).
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Класс KeyScanner отвечает только за чтение состояния клавиш через WinAPI.
// Он не содержит игровой логики и просто даёт актуальные флаги нажатий.
class KeyScanner
{
public:
    KeyScanner();

    // Вызывать один раз за кадр: обновляет снимок «нажато / не нажато».
    void refresh();

    // Проверка виртуального кода клавиши (например 'A', VK_SPACE).
    bool isDown(int virtualKey) const;

private:
    // Последнее считанное состояние (для простоты храним только используемые клавиши).
    bool keyA;
    bool keyD;
    bool keyS;
    bool keyW;
    bool keySpace;
    bool keyShift;
    bool keyP;
    bool keyR;
};
