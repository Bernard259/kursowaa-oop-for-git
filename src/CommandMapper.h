// CommandMapper.h — перевод клавиш в игровые команды (без таймеров и физики).
#pragma once

class KeyScanner;

// Класс CommandMapper отвечает за преобразование нажатых клавиш в игровые команды.
// Он сопоставляет клавиши управления и формирует флаги действий для игрового цикла.
class CommandMapper
{
public:
    CommandMapper();

    // Прочитать KeyScanner и заполнить поля команд (флаги).
    void updateFromKeys(const KeyScanner& keys);

    bool getMoveLeft() const;
    bool getMoveRight() const;
    bool getSoftDrop() const;
    bool getRotate() const;
    bool getHardDrop() const;
    bool getHold() const;
    bool getPause() const;
    bool getRestart() const;

private:
    bool moveLeft;
    bool moveRight;
    bool softDrop;
    bool rotate;
    bool hardDrop;
    bool hold;
    bool pause;
    bool restart;
};
