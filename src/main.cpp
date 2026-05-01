#include "GameEngine.h"
#include "ColorRenderer.h" // Подключаем новый цветной рендерер

int main() {
    // Выбираем, какой интерфейс использовать
    ColorRenderer renderer; 
    
    // Движок примет ColorRenderer, потому что он наследует IRenderer
    GameEngine engine(&renderer);
    
    engine.run();
    return 0;
}