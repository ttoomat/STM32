/*
 * logic.c (003Snake)
 *
 *  Created on: Mar 10, 2025
 *      Author: tt
 */

// TODO: winking apple in order to differentiate it from the snake.

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for better random

#include "stm32f4xx_hal.h" // for Hal delay
#include "render.h"

// game global variables
uint8_t snake_length = 3;
uint8_t coords = 2;
uint8_t snake[64][2] = {{3, 3}, {3, 2}, {3, 1}};
uint8_t game_flag = 1;


uint8_t g[8][8] = {
		{0, 0, 0, 1, 1, 0, 0, 0},
		{0, 1, 1, 0, 0, 1, 1, 0},
		{1, 1, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 1, 1},
		{0, 1, 1, 0, 0, 1, 1, 0},
		{0, 0, 0, 1, 1, 0, 0, 0}
};
/* A target for the snake.
 */
/*
struct apple {
	uint8_t x, y;
};
*/


/* Set a target for snake.
 * Call this function in setup & when apple is eaten.
 */
void generate_apple(uint8_t* apple_x, uint8_t* apple_y) {
	srand(clock());
	*apple_x = rand() % 8;
	*apple_y = rand() % 8;
	// TODO: apple only in free space

}

/* Move snake according to the direction.
 */
void move_snake();

void end_game(uint8_t res) {
	game_flag = 0;
	if (res) {
		draw_columns(good_game);
	}
	else {
		draw_columns(you_lose);
	}
	// чтоб картинка висела вечно
	end_game(res);
}



uint8_t check_intersection() {
	return 0;
}

/* Make the snake longer.
 */
void longer_snake() {
	if (snake_length >= 63)
		end_game(1);
	else {
	  snake_length += 1;
	  int cnt = 10; // убогий таймер...
	  while (cnt > 0) {
		  render_snake(snake, snake_length);
		  cnt--;
	  }
	  /*
	  clock_t time = clock();
	  // чтоб картинка поотображалась
	  while ((clock() - time) / CLOCKS_PER_SEC < 1) {
	    render_snake(snake, snake_length);
	  }
	  */
	}
	// copy snake to other array
	// allocate memory for new bigger snake
	// the first point is new, others are copy of previous snake
}

void setup_snake() {
	render_snake(snake, snake_length);
	// generate & show matrix from the struct apple * /(apple_x, apple_y) and int** snake, int* snake_length, int* coords
    // run: every 300ms move snake + check button -- multithreading? (no, just interrupts) + regenerate apple when needed

}

void run_snake() {
	if (game_flag) {
		longer_snake();
        // move_snake();
		if (check_intersection()) {
			end_game(0);
			return;
		}
		run_snake();
	}
}
