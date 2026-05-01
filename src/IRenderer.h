#pragma once

class GridModel;
class ActivePiece;
class GhostPiece;
class RuleManager;
class MovementController;
class SequenceGenerator;

// Интерфейс, который позволит GameEngine не зависеть от способа отрисовки
class IRenderer {
public:
    virtual ~IRenderer() = default;

    // Метод, который каждый рендерер реализует по-своему
    virtual void renderFrame(
        const GridModel& grid,
        const ActivePiece& active,
        const GhostPiece& ghost,
        const RuleManager& rules,
        const MovementController& movement,
        SequenceGenerator& sequence,
        bool paused,
        bool gameOver) = 0;
};