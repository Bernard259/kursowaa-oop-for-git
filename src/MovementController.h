// MovementController.h — движение, повороты, столкновения через GridModel, удержание (Hold).
#pragma once

class GridModel;
class ActivePiece;
class GhostPiece;
class SequenceGenerator;
class LineClearingSystem;
class RuleManager;

// Класс MovementController отвечает за движение фигуры и операции с ней.
// Он выполняет сдвиги, повороты, hard/soft drop, hold и фиксацию фигуры через GridModel.
class MovementController
{
public:
    MovementController();

    void setGrid(GridModel* gridPtr);
    void setActivePiece(ActivePiece* piecePtr);
    void setGhostPiece(GhostPiece* ghostPtr);
    void setSequence(SequenceGenerator* seqPtr);
    void setLineSystem(LineClearingSystem* linePtr);
    void setRules(RuleManager* rulesPtr);

    // Старт игры: сброс hold и первая фигура.
    void beginNewGame();

    // Следующая фигура из генератора.
    bool spawnNextPiece();

    bool tryMoveLeft();
    bool tryMoveRight();
    bool tryMoveDown();
    bool tryRotateClockwise();
    void hardDrop();

    // Вернуть true, если обмен с hold выполнен.
    bool tryHold();

    // Закрепить активную фигуру, очистить линии, выдать новую.
    void lockPiece();

    int getHoldPieceType() const;
    bool getCanHold() const;

private:
    bool spawnPieceOfType(int pieceType);

    GridModel* grid;
    ActivePiece* active;
    GhostPiece* ghost;
    SequenceGenerator* sequence;
    LineClearingSystem* lineSystem;
    RuleManager* rules;

    int holdPieceType;
    bool canHold;
};
