
# **Documentation for Bird Game Code**

## **Overview**
This is a simple console-based game written in C++ where a player controls a bird (`&`) that must avoid obstacles (`|`). The game includes functions to initialize the game map, move obstacles, move the bird, render the map, and manage game mechanics.

---

## **File Structure**

### **Headers and Libraries**
1. **`#include <iostream>`** - For input/output operations.
2. **`#include <conio.h>`** - For detecting keyboard input (`getch()` and `kbhit()`).
3. **`#include <time.h>`** - For generating random numbers (`srand` and `rand`).
4. **`#include <windows.h>`** - For cursor positioning (`SetConsoleCursorPosition`) and delays (`Sleep`).
5. **`#include <sstream>`** - For efficient string manipulation in `render`.

---

## **Main Function**

### **Structure**
1. Initializes game variables:
   - `score` (int): Tracks the player's score.
   - `hp` (bool): Represents the bird's health (alive or dead).
   - `x` (int): The bird's vertical position.
   - `Obs[3]`: Array of 3 obstacles.
   - `map[20][30]`: 2D array representing the game field.

2. The game runs in a loop as long as the user chooses to retry (`repeat`).

3. **Key Actions in the Loop:**
   - Obstacles move (`obstacleMove`).
   - Bird moves based on player input (`birdMove`).
   - Map is updated and displayed (`render`).

4. At game over:
   - Displays the current score and the high score.
   - Prompts the player to retry.

---

## **Functions**

### 1. **`void initMap(string map[20][30], Obstacle Obs[3])`**
Initializes the game map and sets the initial positions of the obstacles.

- **Parameters:**
  - `map[20][30]`: The 2D array representing the game field.
  - `Obs[3]`: Array of obstacles.

- **Steps:**
  1. Obstacles are placed at specific horizontal positions (`Obs[i].x`) and random vertical positions (`Obs[i].y`).
  2. Borders and blank spaces are drawn in the map.

---

### 2. **`void obstacleMove(string map[20][30], Obstacle Obs[3])`**
Handles the movement of obstacles.

- **Parameters:**
  - `map[20][30]`: The game map.
  - `Obs[3]`: Array of obstacles.

- **Steps:**
  1. Clears the current obstacle positions from the map.
  2. Moves each obstacle one step left.
  3. Resets obstacles to the right side of the screen once they reach the left boundary.
  4. Updates the map with the new obstacle positions.

---

### 3. **`void birdMove(string map[20][30], Obstacle Obs[3], int *x, bool *hp, int *score)`**
Handles the bird's movement and collision detection.

- **Parameters:**
  - `map[20][30]`: The game map.
  - `Obs[3]`: Array of obstacles.
  - `x`: Pointer to the bird's vertical position.
  - `hp`: Pointer to the bird's health (true = alive, false = dead).
  - `score`: Pointer to the player's score.

- **Steps:**
  1. Detects keyboard input to move the bird upward.
  2. The bird gradually moves downward (gravity effect).
  3. Checks for collisions with obstacles or the map boundaries.
  4. Updates the score when the bird successfully avoids obstacles.

---

### 4. **`void render(string map[20][30], int score)`**
Displays the current state of the game.

- **Parameters:**
  - `map[20][30]`: The game map.
  - `score`: The player's current score.

- **Steps:**
  1. Constructs a string representation of the game map.
  2. Includes the score at the bottom of the map.
  3. Uses `setCursorPosition` to refresh the display without scrolling.

---

### 5. **`void setCursorPosition(int x, int y)`**
Positions the cursor at a specified location on the console for smooth rendering.

- **Parameters:**
  - `x`: The horizontal coordinate.
  - `y`: The vertical coordinate.

- **Details:**
  - Uses `SetConsoleCursorPosition` from the Windows API to control the cursor position.

---

## **Gameplay Instructions**
1. Use any key to move the bird upward.
2. Avoid the obstacles (`|`) as they move from right to left.
3. The score increases when the bird successfully passes an obstacle.
4. The game ends if the bird collides with an obstacle or the borders.

---

## **Known Issues**
1. **Randomization:** `(rand() - 1) % 12 + 2` is incorrect for generating obstacle positions. Use `(rand() % 12) + 2` instead.
2. **Compatibility:** This code is designed for Windows due to its dependency on `<windows.h>`.

--- 

## **Possible Improvements**
1. **Refactoring:** Use constants for map dimensions and obstacle properties for easier adjustments.
2. **Cross-Platform Support:** Replace Windows-specific functions with standard cross-platform libraries.
3. **Enhanced Gameplay:**
   - Add difficulty levels.
   - Introduce power-ups or penalties.

---
