// GhostPiece.h — «призрак» показывает, куда упадёт фигура при текущем повороте.
#pragma once

class GridModel;
class ActivePiece;

// Класс GhostPiece отвечает за «призрак» фигуры.
// Он вычисляет конечную позицию падения активной фигуры без изменения игрового поля.
class GhostPiece
{
public:
    GhostPiece();

    // Пересчитать позицию призрака по активной фигуре и полю (максимально вниз).
    void updateFrom(const ActivePiece& active, const GridModel& grid);

    int getGhostBoardX() const;
    int getGhostBoardY() const;
    int getPieceType() const;
    int getRotation() const;

private:
    int ghostBoardX;
    int ghostBoardY;
    int pieceType;
    int rotation;
};
