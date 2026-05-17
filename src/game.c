#include <stdlib.h>
#include <string.h>
#include "game.h"

/* External assembly function for collision detection */
extern int32_t check_collision_asm(const Point *head, const Point *snake, uint16_t length, uint16_t grid_width, uint16_t grid_height);

void game_init(GameState *state) {
    /* Initialize snake in the middle */
    state->length = INITIAL_SNAKE_LENGTH;
    state->direction = DIR_RIGHT;
    state->next_direction = DIR_RIGHT;
    state->score = 0;
    state->game_over = false;
    state->paused = false;
    
    /* Place snake at center */
    uint16_t start_x = GRID_WIDTH / 2;
    uint16_t start_y = GRID_HEIGHT / 2;
    
    for (uint16_t i = 0; i < state->length; i++) {
        state->snake[i].x = start_x - i;
        state->snake[i].y = start_y;
    }
    
    /* Generate initial food */
    state->food.x = (rand() % (GRID_WIDTH - 4)) + 2;
    state->food.y = (rand() % (GRID_HEIGHT - 4)) + 2;
}

void game_update(GameState *state) {
    if (state->paused || state->game_over) {
        return;
    }
    
    /* Update direction if valid */
    if ((state->next_direction == DIR_UP && state->direction != DIR_DOWN) ||
        (state->next_direction == DIR_DOWN && state->direction != DIR_UP) ||
        (state->next_direction == DIR_LEFT && state->direction != DIR_RIGHT) ||
        (state->next_direction == DIR_RIGHT && state->direction != DIR_LEFT)) {
        state->direction = state->next_direction;
    }
    
    /* Move snake - shift body and update head */
    Point new_head = state->snake[0];
    
    switch (state->direction) {
        case DIR_UP:
            new_head.y = (new_head.y - 1 < 1) ? GRID_HEIGHT - 2 : new_head.y - 1;
            break;
        case DIR_DOWN:
            new_head.y = (new_head.y + 1 >= GRID_HEIGHT - 1) ? 1 : new_head.y + 1;
            break;
        case DIR_LEFT:
            new_head.x = (new_head.x - 1 < 1) ? GRID_WIDTH - 2 : new_head.x - 1;
            break;
        case DIR_RIGHT:
            new_head.x = (new_head.x + 1 >= GRID_WIDTH - 1) ? 1 : new_head.x + 1;
            break;
    }
    
    /* Check collision using Assembly function */
    if (check_collision_asm(&new_head, state->snake, state->length, GRID_WIDTH, GRID_HEIGHT)) {
        state->game_over = true;
        return;
    }
    
    /* Check food collision */
    bool ate_food = (new_head.x == state->food.x && new_head.y == state->food.y);
    
    /* Shift snake body */
    if (!ate_food && state->length > 0) {
        for (uint16_t i = state->length - 1; i > 0; i--) {
            state->snake[i] = state->snake[i - 1];
        }
    }
    
    /* Place new head */
    state->snake[0] = new_head;
    
    /* Handle food */
    if (ate_food) {
        state->score += 10;
        if (state->length < MAX_SNAKE_LENGTH) {
            state->length++;
        }
        
        /* Generate new food */
        state->food.x = (rand() % (GRID_WIDTH - 4)) + 2;
        state->food.y = (rand() % (GRID_HEIGHT - 4)) + 2;
    }
}

void game_render(GameState *state __attribute__((unused))) {
    /* Rendered by graphics module */
}

bool game_is_over(GameState *state) {
    return state->game_over;
}

void game_cleanup(void) {
    /* Cleanup if needed */
}
