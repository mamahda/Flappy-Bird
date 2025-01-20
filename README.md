# Flappy Bird Console Game: Documentation

This document explains how the Flappy Bird console game works and how to use the code.

---

## Overview

This game lets you control a bird in a console window, avoiding obstacles while trying to score as many points as possible. The bird moves up when you press a key and falls due to gravity.

---

## How to Run the Code

1. **Compile**:

   ```bash
   g++ -o flappybird flappybird.cpp -std=c++11
   ```

2. **Run**:
   ```bash
   ./flappybird
   ```

---

## How to Play

1. **Controls**: Press any key to move the bird up. The bird falls automatically.
2. **Goal**: Avoid hitting obstacles or the map's edges.
3. **Scoring**: Gain 1 point for every obstacle passed.
4. **Levels**: Difficulty increases every 5 points up to level 15.

---

## Code Structure

### Main Components

1. **`Obstacle` struct**: Stores obstacle positions.
2. **Functions**:
   - Game setup and updates.
   - Obstacle and bird movement.
   - Map rendering.
3. **Main Game Loop**:
   - Handles the gameplay, user input, and game restarts.

### Key Functions

- **`initMap`**: Sets up the game map and initial obstacle positions.
- **`obstacleMove`**: Moves obstacles and resets them when they exit the map.
- **`birdMove`**: Moves the bird, checks collisions, and updates the score.
- **`render`**: Draws the game map, score, and level on the console.
- **`setCursorPosition`**: Adjusts the cursor position for smooth display updates.

---

## Requirements

- ~~Windows system (uses `<windows.h>` for cursor control).~~ now you can play in linux too
- Console large enough for the game map.

---

Enjoy playing!
