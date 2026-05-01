// LineClearingSystem.h — поиск полных рядов, удаление и сдвиг вниз.
#pragma once

class GridModel;
class RuleManager;

// Класс LineClearingSystem отвечает за очистку заполненных линий.
// Он удаляет полные ряды, сдвигает блоки вниз и сообщает RuleManager результат.
class LineClearingSystem
{
public:
    LineClearingSystem();

    // Просканировать поле, удалить полные линии. Вернуть число удалённых рядов (0..4).
    int process(GridModel& grid, RuleManager& rules);

private:
    bool isRowFull(const GridModel& grid, int row) const;
    void removeRowAndShiftDown(GridModel& grid, int row);
};
