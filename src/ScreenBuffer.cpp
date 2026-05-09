#include "ScreenBuffer.h"
#include "ActivePiece.h"
#include "GhostPiece.h"
#include "GridModel.h"
#include "MovementController.h"
#include "RuleManager.h"
#include "SequenceGenerator.h"
#include <cstdio>
#include <cstring>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

ScreenBuffer::ScreenBuffer() {
    clearBuffer();
}

void ScreenBuffer::clearBuffer() {
    for (int row = 0; row < BUFFER_ROWS; row++) {
        for (int col = 0; col < BUFFER_COLS; col++) {
            buffer[row][col] = ' ';
        }
        buffer[row][BUFFER_COLS] = '\0';
    }
}

void ScreenBuffer::setCell(int row, int col, char value) {
    if (row < 0 || row >= BUFFER_ROWS || col < 0 || col >= BUFFER_COLS) return;
    buffer[row][col] = value;
}

void ScreenBuffer::drawPiecePreview(int originRow, int originCol, int pieceType, int rotation) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (ActivePiece::isBlockAt(pieceType, rotation, r, c)) {
                setCell(originRow + r, originCol + c, static_cast<char>('1' + pieceType));
            }
        }
    }
}

// Реализация метода интерфейса IRenderer
void ScreenBuffer::renderFrame(
    const GridModel& grid,
    const ActivePiece& active,
    const GhostPiece& ghost,
    const RuleManager& rules,
    const MovementController& movement,
    SequenceGenerator& sequence,
    bool paused,
    bool gameOver) 
{
    clearBuffer(); // Очищаем старый текст в памяти

    // Логика формирования текста (бывший compose)
    int row = 0;
    const char* title = "=== TETRIS (WinAPI + ASCII) ===";
    for (size_t i = 0; i < strlen(title); i++) setCell(row, (int)i, title[i]);

    char bestLine[64];
    std::snprintf(bestLine, sizeof(bestLine), "Рекорд: %d", rules.getBestScore());
    int bestLen = static_cast<int>(std::strlen(bestLine));
    int bestCol = BUFFER_COLS - bestLen - 1;
    if (bestCol < 0) {
        bestCol = 0;
    }
    for (int i = 0; bestLine[i] != '\0'; i++) setCell(row, bestCol + i, bestLine[i]);
    
    row += 2;
    char line[128];
    int totalSeconds = rules.getPlayTimeSeconds();
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    std::snprintf(line, sizeof(line), "Score: %d  Level: %d  Lines: %d  Time: %02d:%02d",
        rules.getScore(), rules.getLevel(), rules.getTotalLinesCleared(), minutes, seconds);
    for (int i = 0; line[i] != '\0'; i++) setCell(row, i, line[i]);

    // Отрисовка поля (GridModel)
    row += 4;
    int fieldStart = 2;
    for (int gr = 0; gr < GridModel::HEIGHT; gr++) {
        setCell(row + gr, fieldStart, '|');
        for (int gc = 0; gc < GridModel::WIDTH; gc++) {
            int cell = grid.getCell(gr, gc);
            setCell(row + gr, fieldStart + 1 + gc, cell == 0 ? '.' : (char)('0' + cell));
        }
        setCell(row + gr, fieldStart + 1 + GridModel::WIDTH, '|');
    }

    // Отрисовка активной фигуры и призрака
    if (!gameOver) {
        // Отрисовка призрака
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (ActivePiece::isBlockAt(active.getType(), active.getRotation(), r, c)) {
                    setCell(row + active.getBoardY() + r, fieldStart + 1 + active.getBoardX() + c, (char)('1' + active.getType()));
                }
            }
        }
    }

    if (paused) {
        const char* pMsg = "PAUSED";
        for (size_t i = 0; i < strlen(pMsg); i++) setCell(10, 20 + (int)i, pMsg[i]);
    }

    // Наконец, выводим всё это в консоль
    presentToConsole();
}

void ScreenBuffer::presentToConsole() const {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hOut, coord);
    for (int r = 0; r < BUFFER_ROWS; r++) {
        DWORD written;
        WriteConsoleA(hOut, buffer[r], BUFFER_COLS, &written, NULL);
        WriteConsoleA(hOut, "\n", 1, &written, NULL);
    }
}