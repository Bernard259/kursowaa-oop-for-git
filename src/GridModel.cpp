// GridModel.cpp
#include "GridModel.h"
#include "ActivePiece.h"

GridModel::GridModel()
{
    clear();
}

void GridModel::clear()
{
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            cells[row][col] = 0;
        }
    }
}

int GridModel::getCell(int row, int col) const
{
    if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH)
    {
        return 0;
    }
    return cells[row][col];
}

void GridModel::setCell(int row, int col, int value)
{
    if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH)
    {
        return;
    }
    cells[row][col] = value;
}

bool GridModel::canPlaceShape(int pieceType, int rotation, int boardX, int boardY) const
{
    for (int localRow = 0; localRow < 4; localRow++)
    {
        for (int localCol = 0; localCol < 4; localCol++)
        {
            if (!ActivePiece::isBlockAt(pieceType, rotation, localRow, localCol))
            {
                continue;
            }

            int gridRow = boardY + localRow;
            int gridCol = boardX + localCol;

            if (gridCol < 0 || gridCol >= WIDTH)
            {
                return false;
            }
            if (gridRow >= HEIGHT)
            {
                return false;
            }
            // Клетки выше верхней границы (gridRow < 0) не проверяем на занятость —
            // это зона появления фигуры.
            if (gridRow >= 0 && cells[gridRow][gridCol] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void GridModel::mergePiece(int pieceType, int rotation, int boardX, int boardY, int colorIndex)
{
    for (int localRow = 0; localRow < 4; localRow++)
    {
        for (int localCol = 0; localCol < 4; localCol++)
        {
            if (!ActivePiece::isBlockAt(pieceType, rotation, localRow, localCol))
            {
                continue;
            }
            int gridRow = boardY + localRow;
            int gridCol = boardX + localCol;
            if (gridRow >= 0 && gridRow < HEIGHT && gridCol >= 0 && gridCol < WIDTH)
            {
                cells[gridRow][gridCol] = colorIndex;
            }
        }
    }
}
