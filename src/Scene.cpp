#include "Scene.h"

Scene::Scene(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), cols(10), rows(10), 
                                                cellWidth(screenWidth / cols), cellHeight(screenHeight / rows), game(GameLogic(cols, rows)) {
    InitWindow(screenWidth, screenHeight, "Minesweeper");
    SetTargetFPS(60);
}

Scene::~Scene(){
    CloseWindow();
}

void Scene::gameInit(){
    if(game.state != PLAYING){
        game = GameLogic(cols, rows);
        game.state = PLAYING;
    }
}

void Scene::setDifficulty(int difficultyLevel) {
    switch (difficultyLevel) {
        case 1:
            cols = 10;
            rows = 10;
            break;
        case 2:
            cols = 14;
            rows = 14;
            break;
        case 3:
            cols = 20;
            rows = 20;
            break;
    }
    cellWidth = screenWidth / cols;
    cellHeight = screenHeight / rows;
    game = GameLogic(cols, rows);
    game.state = PLAYING;
}

void Scene::drawTitleScreen(){
    char* title = (char*) "Minesweeper";
    char* author = (char*) "By Vetterli65";
    DrawText(title, screenWidth / 2 - MeasureText(title, 20) / 2, screenHeight / 2 - 150, 20, BLACK);
    DrawText(author, screenWidth / 2 - MeasureText(author, 20) / 2, screenHeight / 2 - 120, 20, BLACK);

    if (GuiButton((Rectangle){ (float) screenWidth / 2 - 50, (float) screenHeight / 2 - 80, 100, 30 }, "Easy")) {
        setDifficulty(1);
    }
    DrawText("10x10 grid with fewer mines.", (float) screenWidth / 2 - MeasureText("10x10 grid with fewer mines.", 20) / 2, screenHeight / 2 - 40, 20, DARKGRAY);

    if (GuiButton((Rectangle){ (float) screenWidth / 2 - 50, (float) screenHeight / 2 - 10, 100, 30 }, "Medium")) {
        setDifficulty(2);
    }
    DrawText("14x14 grid with moderate mines.", screenWidth / 2 - MeasureText("14x14 grid with moderate mines.", 20) / 2, screenHeight / 2 + 30, 20, DARKGRAY);

    if (GuiButton((Rectangle){ (float) screenWidth / 2 - 50, (float) screenHeight / 2 + 60, 100, 30 }, "Hard")) {
        setDifficulty(3);
    }
    DrawText("20x20 grid with many mines.", screenWidth / 2 - MeasureText("20x20 grid with many mines.", 20) / 2, screenHeight / 2 + 100, 20, DARKGRAY);
}

void Scene::run(){
    while(!WindowShouldClose()){
        if(game.state == PLAYING){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                Vector2 mPosition = GetMousePosition();
                int i = mPosition.x / cellWidth;
                int j = mPosition.y / cellHeight;
                if(!game.getCell(i, j).flagged && i >= 0 && i < cols && j >= 0 && j < rows){
                    game.openCell(i, j);
                }
            } else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                Vector2 mPosition = GetMousePosition();
                int i = mPosition.x / cellWidth;
                int j = mPosition.y / cellHeight;
                if(i >= 0 && i < cols && j >= 0 && j < rows){
                    game.flagCell(i, j);
                }
            }
        } else if(game.state == LOST || game.state == WON){
            if(IsKeyPressed(KEY_R)){
                gameInit();
            }
            if(IsKeyPressed(KEY_F)){
                game.state = WAITING;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if(game.state == WAITING){
                drawTitleScreen();
            } else {

                for(int i = 0; i < cols; i++){
                    for(int j = 0; j < rows; j++){
                        drawCell(i, j, game.getCell(i, j));
                    }
                }

                if(game.state == LOST){
                    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(WHITE, 0.8f));
                    char* text = (char*) "YOU LOST!";
                    char* textR = (char*) "Press R to restart";
                    char* textF = (char*) "Press F to go main menu";
                    DrawText(text, screenWidth / 2 - MeasureText(text, 20) / 2, screenHeight / 2 + 10, 20, BLACK);
                    DrawText(textR, screenWidth / 2 - MeasureText(textR, 20) / 2, screenHeight * 0.75f - 10, 20, BLACK);
                    DrawText(textF, screenWidth / 2 - MeasureText(textF, 20) / 2, screenHeight * 0.75f + 10, 20, BLACK);
                } else if(game.state == WON){
                    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(WHITE, 0.8f));
                    char* text = (char*) "YOU WON!";
                    char* textR = (char*) "Press R to restart";
                    char* textF = (char*) "Press F to go main menu";
                    DrawText(text, screenWidth / 2 - MeasureText(text, 20) / 2, screenHeight / 2 + 10, 20, BLACK);
                    DrawText(textR, screenWidth / 2 - MeasureText(textR, 20) / 2, screenHeight * 0.75f - 10, 20, BLACK);
                    DrawText(textF, screenWidth / 2 - MeasureText(textF, 20) / 2, screenHeight * 0.75f + 10, 20, BLACK);
                }
            }
        EndDrawing();
    }
}

void Scene::drawCell(int i, int j, Cell cell){
    if(cell.opened){
        if(cell.hasMine){
            DrawRectangle(i * cellWidth, j * cellHeight, cellWidth, cellHeight, RED);
        } else {
            DrawRectangle(i * cellWidth, j * cellHeight , cellWidth, cellHeight, GRAY);
            switch (cell.nearMines){
            case 0:
                break;
            case 1:
                DrawText(TextFormat("%d", cell.nearMines), i * cellWidth + 15, j * cellWidth + 4, cellHeight - 8, BLUE);
                break;
            case 2:
                DrawText(TextFormat("%d", cell.nearMines), i * cellWidth + 15, j * cellWidth + 4, cellHeight - 8, GREEN);
                break;
            case 3:
                DrawText(TextFormat("%d", cell.nearMines), i * cellWidth + 15, j * cellWidth + 4, cellHeight - 8, RED);
            default:
                break;
            }

        }
    } else if(cell.flagged){
        int flagX = i * cellWidth + cellWidth / 2 - 10;
        int flagY = j * cellWidth + cellHeight / 2 - 20; 
        int flagWidth = 20;
        int flagHeight = 40;

        DrawRectangle(flagX, flagY, flagWidth, flagHeight / 2, RED);
        DrawRectangle(flagX - 2, flagY, 4, flagHeight, DARKGRAY);
    }
    DrawRectangleLines(i * cellWidth, j * cellHeight, cellWidth, cellHeight, BLACK);
}