#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "graphics.h"
#include "input.h"

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused))) {
    GameState state;
    
    /* Initialize game systems */
    srand(time(NULL));
    graphics_init();
    input_init();
    game_init(&state);
    
    graphics_clear_screen();
    printf("\n\n\n\n    ===== SNAKE GAME =====\n");
    printf("    Controls: W/A/S/D or Arrow Keys\n");
    printf("    ESC or Q to Quit\n");
    printf("    Starting in 3 seconds...\n\n");
    
    sleep(3);
    
    /* Main game loop */
    while (!state.game_over && !input_check_quit()) {
        /* Update game state */
        game_update(&state);
        
        /* Render game */
        graphics_clear_screen();
        graphics_render_game(&state);
        graphics_flush();
        
        /* Handle input */
        Direction new_dir;
        if (input_get_direction(&new_dir)) {
            state.next_direction = new_dir;
        }
        
        /* Game loop timing */
        usleep(GAME_SPEED * 1000);
    }
    
    /* Cleanup */
    graphics_clear_screen();
    game_cleanup();
    input_cleanup();
    graphics_cleanup();
    
    if (state.game_over) {
        printf("\n\n    GAME OVER!\n");
        printf("    Final Score: %u\n", state.score);
        printf("    Snake Length: %u\n\n", state.length);
    } else {
        printf("\n\n    Thanks for playing!\n\n");
    }
    
    return 0;
}
