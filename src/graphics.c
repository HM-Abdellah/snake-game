#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "graphics.h"

static struct termios original_termios;

void graphics_init(void) {
    /* Disable canonical mode and echo */
    struct termios raw;
    tcgetattr(STDIN_FILENO, &original_termios);
    raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void graphics_cleanup(void) {
    /* Restore terminal settings */
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

void graphics_clear_screen(void) {
    printf("\033[2J\033[H");
}

void graphics_set_cursor(uint16_t x, uint16_t y) {
    printf("\033[%d;%dH", y, x);
}

void graphics_draw_point(uint16_t x, uint16_t y, char c) {
    graphics_set_cursor(x, y);
    putchar(c);
}

void graphics_draw_string(uint16_t x, uint16_t y, const char *str) {
    graphics_set_cursor(x, y);
    printf("%s", str);
}

void graphics_draw_box(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    /* Draw corners */
    graphics_draw_point(x1, y1, '+');
    graphics_draw_point(x2, y1, '+');
    graphics_draw_point(x1, y2, '+');
    graphics_draw_point(x2, y2, '+');
    
    /* Draw horizontal lines */
    for (uint16_t x = x1 + 1; x < x2; x++) {
        graphics_draw_point(x, y1, '-');
        graphics_draw_point(x, y2, '-');
    }
    
    /* Draw vertical lines */
    for (uint16_t y = y1 + 1; y < y2; y++) {
        graphics_draw_point(x1, y, '|');
        graphics_draw_point(x2, y, '|');
    }
}

void graphics_render_game(GameState *state) {
    /* Draw border */
    graphics_draw_box(0, 0, GRID_WIDTH - 1, GRID_HEIGHT - 1);
    
    /* Draw snake */
    for (uint16_t i = 0; i < state->length; i++) {
        char c = (i == 0) ? '@' : 'o';
        graphics_draw_point(state->snake[i].x, state->snake[i].y, c);
    }
    
    /* Draw food */
    graphics_draw_point(state->food.x, state->food.y, '*');
    
    /* Draw UI */
    char score_str[32];
    snprintf(score_str, sizeof(score_str), "Score: %u", state->score);
    graphics_draw_string(2, GRID_HEIGHT + 1, score_str);
    
    char length_str[32];
    snprintf(length_str, sizeof(length_str), "Length: %u", state->length);
    graphics_draw_string(2, GRID_HEIGHT + 2, length_str);
    
    if (state->game_over) {
        graphics_draw_string(GRID_WIDTH / 2 - 5, GRID_HEIGHT / 2, "GAME OVER");
    }
}

void graphics_flush(void) {
    fflush(stdout);
}
