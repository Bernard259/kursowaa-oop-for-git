// GhostPiece.cpp
#include "GhostPiece.h"
#include "ActivePiece.h"
#include "GridModel.h"

GhostPiece::GhostPiece()
{
    ghostBoardX = 0;
    ghostBoardY = 0;
    pieceType = PIECE_I;
    rotation = 0;
}

void GhostPiece::updateFrom(const ActivePiece& active, const GridModel& grid)
{
    pieceType = active.getType();
    rotation = active.getRotation();
    ghostBoardX = active.getBoardX();

    int y = active.getBoardY();
    // Двигаем вниз, пока позиция допустима.
    while (grid.canPlaceShape(pieceType, rotation, ghostBoardX, y + 1))
    {
        y = y + 1;
    }
    ghostBoardY = y;
}

int GhostPiece::getGhostBoardX() const
{
    return ghostBoardX;
}

int GhostPiece::getGhostBoardY() const
{
    return ghostBoardY;
}

int GhostPiece::getPieceType() const
{
    return pieceType;
}

int GhostPiece::getRotation() const
{
    return rotation;
}
