#ifndef SCENE_H
#define SCENE_H

#include <raylib.h>
#include <raygui.h>
#include <string.h>
#include "GameLogic.h"

class Scene {
public:
    Scene(int screenWidth, int screenHeight);
    ~Scene();
    void run();

private:
    int screenWidth, screenHeight;
    int cols, rows;
    int cellWidth, cellHeight;
    GameLogic game;

    void gameInit();
    void setDifficulty(int difficultyLevel);
    void drawTitleScreen();
    void drawCell(int i, int j, Cell cell);

};

#endif // SCENE_H