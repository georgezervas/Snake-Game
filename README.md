# Snake Game (C++)
A classic Snake Game written in C++ using the Simple Game Graphics (SGG) library. This project focuses on Object-Oriented Programming and state management.

## Features
* **Graph-based Movement:** The game board uses a graph-based node system. Everything that happens on the graph while playing actually happens between the nodes.
* **Core Gameplay:** The snake can move around in 4 directions (**right**, **left**, **up**, **down**). If the head node "eats" the food, a new node is added to its tail. Obviously, if the head node hits the wall (the outside of the grid) or one of the tail's nodes, the player loses.
* **Game States:** 4 possible situations on screen: **Start screen**, **Playing**, **Pause**, and **Game Over**.
* **Audio:** Simple and beautiful music has been implemented. Can be found in the assets folder!

## Technologies
* **Language:** C++
* **Graphics:** SGG
* **IDE:** Visual Studio

## Setup Instructions

### a) Via Visual Studio (Recommended)
1. **Open** `SnakeGame.slnx`
2. **Select** x64 (or x86)
3. **Press** `F5` or `Ctrl + Shift + B` to build and run the game directly from the IDE.

### b) Direct Execution (For Players)
1. Go to the **Releases** section on the right side of this GitHub page.
2. Download the `SnakeGame-v1.0.zip` file.
3. Extract it and run the `SnakeGame.exe` directly.
