@echo off
REM Сборка MinGW g++ (из корня проекта KURSACH)
cd /d "%~dp0"
g++ -std=c++17 -O2 -Wall -Wextra -o tetris.exe ^
  src/main.cpp ^
  src/GameEngine.cpp ^
  src/ColorRenderer.cpp ^
  src/ScreenBuffer.cpp ^
  src/MovementController.cpp ^
  src/LineClearingSystem.cpp ^
  src/RuleManager.cpp ^
  src/SequenceGenerator.cpp ^
  src/KeyScanner.cpp ^
  src/CommandMapper.cpp ^
  src/GridModel.cpp ^
  src/ActivePiece.cpp ^
  src/GhostPiece.cpp
if errorlevel 1 exit /b 1
echo Сборка успешна: tetris.exe
exit /b 0
