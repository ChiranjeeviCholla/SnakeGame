# SnakeGame
1. Snake Game (C++ with raylib)

Snake Game is a classic arcade-style Snake game built from scratch using C++ and the raylib graphics library.
The project focuses on clean Object-Oriented Programming (OOP) design, efficient data structures, and a well-structured game loop.

This game is ideal for learning fundamentals of C++ game development, real-time input handling, and frame-independent movement.

2. Features

Object-Oriented Design
The game logic is divided into clear and manageable classes:

Snake

Food

Game
This improves readability, scalability, and maintainability.

Grid-Based Gameplay

25 × 25 grid

Each cell is 30 × 30 pixels

Total window size: 750 × 750

Efficient Snake Body Handling
Uses std::deque to store the snake’s body, allowing:

O(1) insertion at the head

O(1) removal from the tail

Collision Detection System

Food collision (snake eats food)

Boundary collision (game over on hitting window edges)

Self-collision (snake cannot cross itself)

Smart Food Spawning
Food is generated only in empty grid cells and never overlaps with the snake.

Input Validation
Arrow-key controls with logic to prevent instant 180-degree turns
(e.g., cannot move down while moving up).

Smooth Performance

Runs at a stable 60 FPS

Snake movement speed is independent of frame rate using a 200 ms update timer

3. Technical Details

Language: C++

Graphics Library: raylib

Window Resolution: 750 × 750 pixels

4. Assets:

Uses LoadTextureFromImage() for textures

Proper cleanup using destructors to avoid memory leaks

5. Controls
Key	Action
↑ Arrow	Move Up
↓ Arrow	Move Down
← Arrow	Move Left
→ Arrow	Move Right
Any Arrow	Restart after Game Over
6. Project Structure

Game Loop

Input handling

Game state updates

Rendering

Timing System

Uses GetTime() to control movement updates

Ensures consistent gameplay across different systems

Coordinate System

Origin (0, 0) at the top-left corner

X increases to the right

Y increases downward

7. Installation & Setup

Requirements

C++ compiler

raylib installed

Recommended IDE: Visual Studio Code

Assets

Place food.png inside a Graphics/ folder relative to the executable

Build

Compile main.cpp

Link against raylib and raymath

8. Credits

 Programming With Nick [Youtube]
