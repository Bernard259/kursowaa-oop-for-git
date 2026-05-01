#include "ColorRenderer.h"
#include "GridModel.h"
#include "ActivePiece.h"
#include "GhostPiece.h"
#include "RuleManager.h"
#include "MovementController.h"
#include "SequenceGenerator.h"
#include <iostream>
#include <cstdio>
#include <windows.h>

ColorRenderer::ColorRenderer() {
    setupConsole();
}

void ColorRenderer::setupConsole() {
    // Включаем поддержку ANSI-кодов в Windows 10/11
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void ColorRenderer::renderFrame(
    const GridModel& grid,
    const ActivePiece& active,
    const GhostPiece& ghost,
    const RuleManager& rules,
    const MovementController& movement,
    SequenceGenerator& sequence,
    bool paused,
    bool gameOver) {
    (void)movement;
    (void)sequence;

    // Скрываем курсор и переносим его в (0,0)
    std::string out = "\x1b[?25l\x1b[H"; 

    out += "\x1b[97m=== NEON TETRIS ===\x1b[0m\n\n";
    int totalSeconds = rules.getPlayTimeSeconds();
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    char timeText[16];
    std::snprintf(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);

    out += "Score: \x1b[92m" + std::to_string(rules.getScore()) + "\x1b[0m | ";
    out += "Level: \x1b[93m" + std::to_string(rules.getLevel()) + "\x1b[0m | ";
    out += "Time: \x1b[96m";
    out += timeText;
    out += "\x1b[0m\n\n";

    // Рисуем поле
    out += "  \x1b[37m+--------------------+\x1b[0m\n";
    for (int r = 0; r < GridModel::HEIGHT; r++) {
        out += "  \x1b[37m|\x1b[0m"; // Боковая рамка
        for (int c = 0; c < GridModel::WIDTH; c++) {
            int cell = grid.getCell(r, c);
            
            // Проверяем, нет ли тут активной фигуры или призрака
            bool isActive = false;
            if (!gameOver) {
                // Ghost
                if (ActivePiece::isBlockAt(ghost.getPieceType(), ghost.getRotation(), r - ghost.getGhostBoardY(), c - ghost.getGhostBoardX())) {
                    out += colors[8] + "░░"; // Символ призрака
                    isActive = true;
                }
                // Active
                if (!isActive && ActivePiece::isBlockAt(active.getType(), active.getRotation(), r - active.getBoardY(), c - active.getBoardX())) {
                    out += colors[active.getType() + 1] + "██"; // Солидный блок
                    isActive = true;
                }
            }

            if (!isActive) {
                if (cell == 0) out += "  "; // Пустота
                else out += colors[cell] + "██"; // Застывшие блоки
            }
        }
        out += "\x1b[37m|\x1b[0m\n";
    }
    out += "  \x1b[37m+--------------------+\x1b[0m\n";

    if (paused) out += "\n\x1b[5;91m  *** PAUSED ***\x1b[0m\n";
    if (gameOver) out += "\n\x1b[91m  GAME OVER! Press R\x1b[0m\n";

    std::cout << out << std::flush;
}