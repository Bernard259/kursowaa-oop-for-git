// SequenceGenerator.cpp
#include "SequenceGenerator.h"
#include <cstdlib>
#include <ctime>

static void shuffleArray(int* values, int count)
{
    for (int i = count - 1; i > 0; i--)
    {
        int j = (rand() % (i + 1));
        int tmp = values[i];
        values[i] = values[j];
        values[j] = tmp;
    }
}

SequenceGenerator::SequenceGenerator()
{
    bagPosition = 0;
    srand(static_cast<unsigned int>(time(nullptr)));
    reset();
}

void SequenceGenerator::reset()
{
    bagPosition = 0;
    refillBag();
}

void SequenceGenerator::refillBag()
{
    for (int i = 0; i < PIECE_COUNT; i++)
    {
        bag[i] = i;
    }
    shuffleBag();
    bagPosition = 0;
}

void SequenceGenerator::shuffleBag()
{
    shuffleArray(bag, PIECE_COUNT);
}

void SequenceGenerator::ensureBagNotEmpty()
{
    if (bagPosition >= PIECE_COUNT)
    {
        refillBag();
    }
}

int SequenceGenerator::peekNextPieceType()
{
    ensureBagNotEmpty();
    return bag[bagPosition];
}

int SequenceGenerator::nextPieceType()
{
    ensureBagNotEmpty();
    int value = bag[bagPosition];
    bagPosition = bagPosition + 1;
    return value;
}
