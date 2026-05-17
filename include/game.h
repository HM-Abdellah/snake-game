#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

/* Game constants */
#define GRID_WIDTH 80
#define GRID_HEIGHT 24
#define MAX_SNAKE_LENGTH 1000
#define INITIAL_SNAKE_LENGTH 3
#define GAME_SPEED 100  /* milliseconds between frames */

/* Direction enum */
typedef enum {
    DIR_UP = 0,
    DIR_DOWN = 1,
    DIR_LEFT = 2,
    DIR_RIGHT = 3
} Direction;

/* Point structure */
typedef struct {
    uint16_t x;
    uint16_t y;
} Point;

/* Game state structure */
typedef struct {
    Point snake[MAX_SNAKE_LENGTH];
    uint16_t length;
    Direction direction;
    Direction next_direction;
    Point food;
    uint32_t score;
    bool game_over;
    bool paused;
} GameState;

/* Function declarations */
void game_init(GameState *state);
void game_update(GameState *state);
void game_render(GameState *state);
bool game_is_over(GameState *state);
void game_cleanup(void);

#endif /* GAME_H */