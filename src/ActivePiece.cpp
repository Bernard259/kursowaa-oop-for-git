// ActivePiece.cpp — формы фигур и повороты (таблица 4x4 для каждого состояния).
#include "ActivePiece.h"

// Формы: 7 типов × 4 поворота × 4 строки × 4 столбца. 1 — блок, 0 — пусто.
// Повороты идут по часовой стрелке (0 — начальное положение при спавне).
// static — видимость только в этом .cpp файле (внутреннее связывание).
static const int SHAPES[PIECE_COUNT][4][4][4] = {
        // I
        {
            {
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0},
            },
            {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
            },
        },
        // O (все повороты одинаковы для простоты отрисовки)
        {
            {
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
        },
        // T
        {
            {
                {0, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 0, 0, 0},
                {1, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
            },
        },
        // S
        {
            {
                {0, 1, 1, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 0, 0, 0},
                {0, 1, 1, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 0, 0, 0},
                {0, 0, 0, 0},
            },
        },
        // Z
        {
            {
                {1, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 0, 1, 0},
                {0, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 0, 0, 0},
                {1, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 0, 0},
                {1, 1, 0, 0},
                {1, 0, 0, 0},
                {0, 0, 0, 0},
            },
        },
        // J
        {
            {
                {1, 0, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 1, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 0, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
            },
        },
        // L
        {
            {
                {0, 0, 1, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
            },
            {
                {0, 0, 0, 0},
                {1, 1, 1, 0},
                {1, 0, 0, 0},
                {0, 0, 0, 0},
            },
            {
                {1, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
            },
        },
    };

ActivePiece::ActivePiece()
{
    type = PIECE_I;
    rotation = 0;
    boardX = 3;
    boardY = 0;
}

void ActivePiece::setType(int typeIndex)
{
    if (typeIndex >= 0 && typeIndex < PIECE_COUNT)
    {
        type = typeIndex;
    }
}

void ActivePiece::setRotation(int rotationIndex)
{
    if (rotationIndex >= 0 && rotationIndex < 4)
    {
        rotation = rotationIndex;
    }
}

void ActivePiece::setPosition(int x, int y)
{
    boardX = x;
    boardY = y;
}

int ActivePiece::getType() const
{
    return type;
}

int ActivePiece::getRotation() const
{
    return rotation;
}

int ActivePiece::getBoardX() const
{
    return boardX;
}

int ActivePiece::getBoardY() const
{
    return boardY;
}

int ActivePiece::getRotationCount(int pieceType)
{
    if (pieceType < 0 || pieceType >= PIECE_COUNT)
    {
        return 4;
    }
    return 4;
}

bool ActivePiece::isBlockAt(int pieceType, int rotation, int localRow, int localCol)
{
    if (pieceType < 0 || pieceType >= PIECE_COUNT)
    {
        return false;
    }
    int rot = rotation % 4;
    if (rot < 0)
    {
        rot += 4;
    }
    if (localRow < 0 || localRow >= 4 || localCol < 0 || localCol >= 4)
    {
        return false;
    }
    return SHAPES[pieceType][rot][localRow][localCol] != 0;
}
