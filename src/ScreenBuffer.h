#pragma once
#include "IRenderer.h"

// Класс ScreenBuffer теперь реализует интерфейс IRenderer.
class ScreenBuffer : public IRenderer {
public:
    ScreenBuffer();

    // Основной метод для отрисовки кадра в консоли
    void renderFrame(
        const GridModel& grid,
        const ActivePiece& active,
        const GhostPiece& ghost,
        const RuleManager& rules,
        const MovementController& movement,
        SequenceGenerator& sequence,
        bool paused,
        bool gameOver) override;

private:
    void clearBuffer();
    void setCell(int row, int col, char value);
    void drawPiecePreview(int originRow, int originCol, int pieceType, int rotation);
    void presentToConsole() const;

    static const int BUFFER_ROWS = 28;
    static const int BUFFER_COLS = 72;
    char buffer[BUFFER_ROWS][BUFFER_COLS + 1];
};