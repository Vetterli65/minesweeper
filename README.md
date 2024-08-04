# Minesweeper Project

<img src="https://github.com/user-attachments/assets/fa5898f0-b625-4e48-83e9-4c5406ac0fe9" width="400" />
<img src="https://github.com/user-attachments/assets/09596a4c-5273-4214-94a0-c8459121b927" width="400" />
<img src="https://github.com/user-attachments/assets/4c791575-9ec2-4e54-8e77-b8143b6e64b0" width="400" />
<img src="https://github.com/user-attachments/assets/0c9812d0-8401-461d-987a-d653748f61a1" width="400" />


Minesweeper is a classic puzzle game where player must clear a rectangular board containing hidden mines without detonating any of them. 
This project implements the Minesweeper game and provides a graphical interface to tune the settings.

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
