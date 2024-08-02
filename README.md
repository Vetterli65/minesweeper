# Minesweeper Project

Minesweeper is a classic puzzle game where player must clear a rectangular board containing hidden mines without detonating any of them. 
This project implements the Minesweeper game and provides a graphical interface for an engaging gaming experience.

## Features

- Implementation of the Minesweeper game logic
- Graphical user interface using raylib and raygui
- Three difficulty levels: Easy, Medium, and Hard

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Vetterli65/minesweeper.git
   cd minesweeper
   ```
2. Ensure you have the necessary dependencies installed. This project requires:
    * A C++ compiler for Linux e.g., g++, clang++ or for windows a MinGW
    * Raylib and RayGUI included as dependencies in Cmake file
3. Naviagate to the build directory and build project:
    * For Linux
    ```bash
    cd build-linux
    cmake ..
    make
    ```
    * For Windows
    ```bash
    cd build-windows
    cmake -DCMAKE_TOOLCHAIN_FILE=../mingw-toolchain.cmake
    make
4. Run the executable:
    ```bash
    ./minesweeper
    ```

## Usage

The **main.cpp** file contains an example of how to set up and run the Minesweeper game. Below is a brief explanation of the key components and how to use them.

### Example

The example in **main.cpp** demonstrates setting up the game and running it with a graphical interface.

```cpp
#include "Scene.h"

int main(){
    Scene scene(700, 700);
    scene.run();
}
```

### Difficulty Levels

The game offers three difficulty levels, selectable from the title screen:
* Easy: 10x10 grid with fewer mines.
* Medium: 14x14 grid with moderate mines.
* Hard: 20x20 grid with many mines.

### References

* Andrew Hamel Codes, "Making Minesweeper in Raylib with C" 