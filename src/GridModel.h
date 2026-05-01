// GridModel.h — игровое поле 10x20 и зафиксированные блоки.
#pragma once

// Класс GridModel отвечает за состояние игрового поля 10x20.
// Он хранит зафиксированные блоки, проверяет коллизии и встраивает фигуру в сетку.
class GridModel
{
public:
    // Размеры видимого поля (классический Tetris).
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    GridModel();

    // Полная очистка поля (рестарт).
    void clear();

    // Доступ к сетке для отрисовки и систем очистки линий.
    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);

    // Проверка: можно ли разместить блок фигуры в координатах доски.
    // Использует статическую форму фигуры из ActivePiece (см. ActivePiece::isBlockAt).
    bool canPlaceShape(int pieceType, int rotation, int boardX, int boardY) const;

    // Закрепить фигуру на поле (копирует блоки в сетку).
    void mergePiece(int pieceType, int rotation, int boardX, int boardY, int colorIndex);

private:
    // Храним цвет (1..7), 0 — пустая клетка.
    int cells[HEIGHT][WIDTH];
};
