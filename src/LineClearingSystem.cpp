// LineClearingSystem.cpp
#include "LineClearingSystem.h"
#include "GridModel.h"
#include "RuleManager.h"

LineClearingSystem::LineClearingSystem()
{
}

bool LineClearingSystem::isRowFull(const GridModel& grid, int row) const
{
    for (int col = 0; col < GridModel::WIDTH; col++)
    {
        if (grid.getCell(row, col) == 0)
        {
            return false;
        }
    }
    return true;
}

void LineClearingSystem::removeRowAndShiftDown(GridModel& grid, int rowToRemove)
{
    for (int row = rowToRemove; row > 0; row--)
    {
        for (int col = 0; col < GridModel::WIDTH; col++)
        {
            grid.setCell(row, col, grid.getCell(row - 1, col));
        }
    }
    for (int col = 0; col < GridModel::WIDTH; col++)
    {
        grid.setCell(0, col, 0);
    }
}

int LineClearingSystem::process(GridModel& grid, RuleManager& rules)
{
    int cleared = 0;
    int row = GridModel::HEIGHT - 1;
    while (row >= 0)
    {
        if (isRowFull(grid, row))
        {
            removeRowAndShiftDown(grid, row);
            cleared = cleared + 1;
            // После сдвига на этой же позиции снова проверить (могла «съехать» ещё одна полная линия).
        }
        else
        {
            row = row - 1;
        }
    }

    if (cleared > 0)
    {
        rules.onLinesCleared(cleared);
    }
    else
    {
        rules.onNoLinesCleared();
    }

    return cleared;
}
