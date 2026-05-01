#include "GameEngine.h"

GameEngine::GameEngine(IRenderer* rendererInstance) 
    : renderer(rendererInstance), movement(grid, activePiece, ghostPiece, sequence, rules, lineClearer) 
{
    paused = false;
    // ... инициализация остальных флагов ...
    restartRound();
}

void GameEngine::run() {
    while (true) {
        if (keyScanner.isPressed(VK_ESCAPE)) break;

        // ... логика обновления игры (ввод, гравитация) ...

        // Вызов отрисовки через интерфейс
        renderer->renderFrame(grid, activePiece, ghostPiece, rules, movement, sequence, paused, rules.isGameOver());

        Sleep(16); // Ограничение FPS
    }
}

// ... реализация остальных методов (restartRound и т.д.) ...