#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "input.h"

static bool quit_requested = false;

void input_init(void) {
    /* Input system initialized in graphics_init */
    quit_requested = false;
}

void input_cleanup(void) {
    /* Cleanup if needed */
}

bool input_get_direction(Direction *dir) {
    unsigned char ch;
    ssize_t bytes = read(STDIN_FILENO, &ch, 1);
    
    if (bytes <= 0) {
        return false;
    }
    
    switch (ch) {
        case 'w':
        case 'W':
            *dir = DIR_UP;
            return true;
        case 's':
        case 'S':
            *dir = DIR_DOWN;
            return true;
        case 'a':
        case 'A':
            *dir = DIR_LEFT;
            return true;
        case 'd':
        case 'D':
            *dir = DIR_RIGHT;
            return true;
        case 27:  /* ESC key */
        case 'q':
        case 'Q':
            quit_requested = true;
            return false;
        default:
            return false;
    }
}

bool input_check_quit(void) {
    return quit_requested;
}
