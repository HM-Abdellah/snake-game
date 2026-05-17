#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include "game.h"

/* Display functions */
void graphics_init(void);
void graphics_cleanup(void);
void graphics_clear_screen(void);
void graphics_draw_box(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void graphics_draw_point(uint16_t x, uint16_t y, char c);
void graphics_draw_string(uint16_t x, uint16_t y, const char *str);
void graphics_render_game(GameState *state);
void graphics_set_cursor(uint16_t x, uint16_t y);
void graphics_flush(void);

#endif /* GRAPHICS_H */