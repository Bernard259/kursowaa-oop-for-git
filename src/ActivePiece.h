// ActivePiece.h — тип фигуры, поворот и координаты на поле.
#pragma once

// Индексы типов фигур (удобно для массива и «мешка»).
enum PieceType
{
    PIECE_I = 0,
    PIECE_O = 1,
    PIECE_T = 2,
    PIECE_S = 3,
    PIECE_Z = 4,
    PIECE_J = 5,
    PIECE_L = 6,
    PIECE_COUNT = 7
};

// Класс ActivePiece отвечает за текущую падающую фигуру.
// Он хранит тип, поворот и позицию, а также даёт доступ к форме блоков в матрице 4x4.
class ActivePiece
{
public:
    ActivePiece();

    void setType(int typeIndex);
    void setRotation(int rotationIndex);
    void setPosition(int boardX, int boardY);

    int getType() const;
    int getRotation() const;
    int getBoardX() const;
    int getBoardY() const;

    // Сколько различных поворотов имеет фигура (у O — фактически один вид, но храним 4 копии).
    static int getRotationCount(int pieceType);

    // Есть ли блок в локальной 4x4 сетке (локальные строка/столбец 0..3).
    static bool isBlockAt(int pieceType, int rotation, int localRow, int localCol);

private:
    int type;
    int rotation;
    int boardX;
    int boardY;
};
