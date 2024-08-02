#include "GameLogic.h"

GameLogic::GameLogic(int cols, int rows) : cols(cols), rows(rows), state(WAITING), cellsOpened(0), minesToFlag((int)(cols * rows * 0.1f)){
    srand(time(NULL));

    grid.resize(rows);
    for(int i = 0; i < rows; i++){
        grid[i].resize(cols);
    }

    gridInit();
}

void GameLogic::gridInit(){
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            grid[i][j] = {0, false, false, false};
        }
    }

    int amountOfMines = minesToFlag;
    while(amountOfMines > 0){
        int i = rand() % cols;
        int j = rand() % rows;
        if(!grid[i][j].hasMine){
            grid[i][j].hasMine = true;
            amountOfMines--;
        }
    }

    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            if(!grid[i][j].hasMine){
                grid[i][j].nearMines = countMinesCell(i, j);
            }
        }
    }
}

Cell GameLogic::getCell(int i, int j){
    return grid[i][j];
}

void GameLogic::openCell(int i, int j){
    if(grid[i][j].opened || grid[i][j].flagged)
        return;

    grid[i][j].opened = true;

    if(grid[i][j].hasMine){
        state = LOST;
    } else {

        if(grid[i][j].nearMines == 0){
            openNearCells(i, j);
        }
        cellsOpened++;

        if(cellsOpened == rows * cols - minesToFlag){
            state = WON;
        }
    }
}

void GameLogic::openNearCells(int i, int j){
    for(int offI = -1; offI <= 1; offI++){
        for(int offJ = -1; offJ <= 1; offJ++){
            if(offI == 0 && offJ == 0) 
                continue;
            if(!(i + offI >= 0 && i + offI < rows && j + offJ >= 0 && j + offJ < cols))
                continue;
            if(!grid[i + offI][j + offJ].opened)
                openCell(i + offI, j + offJ);
        }
    }
}

void GameLogic::flagCell(int i, int j){
    if(grid[i][j].opened) 
        return;
    
    grid[i][j].flagged = !grid[i][j].flagged;
}

int GameLogic::countMinesCell(int i, int j){
    int count = 0;
    for(int offI = -1; offI <= 1; offI++){
        for(int offJ = -1; offJ <= 1; offJ++){
            if(offI == 0 && offJ == 0) 
                continue;
            if(!(i + offI >= 0 && i + offI < cols && j + offJ >= 0 && j + offJ < rows)) 
                continue;
            if(grid[i + offI][j + offJ].hasMine)
                count++;
        }
    }
    return count;
}