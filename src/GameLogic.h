#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdlib.h>
#include <time.h>
#include <vector>

using std::vector;

struct Cell{
    int nearMines;
    bool hasMine;
    bool flagged;
    bool opened;
};

enum GameState{
    PLAYING,
    WAITING,
    LOST,
    WON
};

class GameLogic {
public:
    GameLogic(int cols, int rows);
    GameState state;

    void gridInit();

    Cell getCell(int i, int j);

    void openCell(int i, int j);
    void flagCell(int i, int j);

private:
    int cols, rows;
    vector<vector<Cell>> grid;

    int cellsOpened;
    int minesToFlag;

    void openNearCells(int i, int j);
    int countMinesCell(int i, int j);

};

#endif // GAMELOGIC_H