#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include "game.h"

/* Input handling */
void input_init(void);
void input_cleanup(void);
bool input_get_direction(Direction *dir);
bool input_check_quit(void);

#endif /* INPUT_H */