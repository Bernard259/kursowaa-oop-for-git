// SequenceGenerator.h — «мешок» из 7 фигур (равномерное распределение).
#pragma once

#include "ActivePiece.h"

// Класс SequenceGenerator отвечает за выдачу следующей фигуры по системе «мешка».
// Он гарантирует равномерное распределение: в каждом мешке по одной фигуре каждого типа.
class SequenceGenerator
{
public:
    SequenceGenerator();

    // Взять следующую фигуру (сдвигает указатель в мешке).
    int nextPieceType();

    // Посмотреть следующую фигуру, не забирая (для окна «Next»).
    // Не const: при пустом мешке выполняется дозаполнение.
    int peekNextPieceType();

    void reset();

private:
    void refillBag();
    void shuffleBag();
    void ensureBagNotEmpty();

    int bag[PIECE_COUNT];
    int bagPosition;
};
