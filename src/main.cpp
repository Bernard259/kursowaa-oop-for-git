#include "GameEngine.h"
#include "ScreenBuffer.h"

int main() {
    // 1. Создаем конкретный рендерер (сейчас это консоль)
    ScreenBuffer consoleRenderer;

    // 2. Передаем его в движок
    GameEngine engine(&consoleRenderer);

    // 3. Запускаем
    engine.run();

    return 0;
}