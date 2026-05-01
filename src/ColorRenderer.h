#pragma once
#include "IRenderer.h"
#include <string>
#include <vector>

class ColorRenderer : public IRenderer {
public:
    ColorRenderer();
    
    void renderFrame(
        const GridModel& grid,
        const ActivePiece& active,
        const GhostPiece& ghost,
        const RuleManager& rules,
        const MovementController& movement,
        SequenceGenerator& sequence,
        bool paused,
        bool gameOver) override;

private:
    void setupConsole();
    std::string getColorCode(int colorIndex);
    
    // Цвета: 0-пусто, 1-I, 2-O, 3-T, 4-S, 5-Z, 6-J, 7-L, 8-Ghost
    const std::vector<std::string> colors = {
        "\x1b[0m",      // Reset
        "\x1b[96m",     // Cyan (I)
        "\x1b[93m",     // Yellow (O)
        "\x1b[95m",     // Magenta (T)
        "\x1b[92m",     // Green (S)
        "\x1b[91m",     // Red (Z)
        "\x1b[94m",     // Blue (J)
        "\x1b[38;5;208m", // Orange (L)
        "\x1b[90m"      // Gray (Ghost)
    };
};