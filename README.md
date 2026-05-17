# Snake Game - x64 Assembly & C

A classic Snake game implementation for x86-64 architecture, combining C for game logic and x64 Assembly for performance-critical operations.

## Features

- Classic snake gameplay
- Score tracking
- Collision detection (optimized in Assembly)
- Keyboard controls (WASD or Arrow Keys)
- Smooth graphics rendering
- High-performance x64 Assembly routines

## Building

### Requirements
- GCC or Clang compiler
- NASM (Netwide Assembler)
- Make
- Linux environment (or Windows with WSL/MinGW)

### Build Instructions

```bash
make build
```

### Run

```bash
./bin/snake
```

### Clean

```bash
make clean
```

## Controls

- **W or UP ARROW** - Move Up
- **S or DOWN ARROW** - Move Down
- **A or LEFT ARROW** - Move Left
- **D or RIGHT ARROW** - Move Right
- **ESC or Q** - Quit Game

## Game Rules

1. Move the snake around the terminal
2. Eat the food (represented by @) to grow and score points
3. Avoid hitting the walls and yourself
4. The game ends when you collide with a wall or yourself

## Project Structure

```
snake-game/
├── src/
│   ├── main.c              # Main game loop and entry point
│   ├── game.c              # Game logic (movement, scoring)
│   ├── graphics.c          # Rendering functions
│   ├── input.c             # Input handling
│   └── collision.asm       # Assembly-optimized collision detection
├── include/
│   ├── game.h              # Game structures and constants
│   ├── graphics.h          # Graphics function declarations
│   └── input.h             # Input function declarations
├── Makefile                # Build configuration
└── README.md               # This file
```

## Performance Optimizations

The following operations are optimized using x64 Assembly:
- **Collision Detection** - Critical path for game responsiveness
- **Buffer Writes** - Fast screen updates

## Building for x64

The project is configured to compile for x86-64 architecture with proper calling conventions (System V AMD64 ABI for Linux).

## License

This project is open source and available under the MIT License.

## Author

Created by HM-Abdellah