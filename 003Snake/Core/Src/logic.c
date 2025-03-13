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

enum dir {
	RIGHT, LEFT, UP, DOWN
};

// game global variables
uint8_t snake_length = 3; // current snake length
uint8_t coords = 2; // number of coordinates
uint8_t snake[64][2] = {{3, 3}, {3, 2}, {3, 1}}; // initial snake
uint8_t game_flag = 1; // this flag is 0 when the game is finished
uint8_t apple_x, apple_y; // snake's target coordinates

enum dir direction = DOWN;

/* Set a target for snake.
 * Call this function in setup & when apple is eaten.
 */
void generate_apple() {
	srand(clock()); // setup random
	apple_x = rand() % 8;
	apple_y = rand() % 8;
	// apple cannot spawn in snake
	for (int i = 0; i < snake_length; ++i) {
		if (apple_x == snake[i][0] && apple_y == snake[i][1]) {
			generate_apple();
		}
	}
}

/* Move snake according to the direction.
 */
// TODO: if snake is ###@, it cannot turn left, but it is not game over...
void move_snake() {
	// в массиве snake надо подвинуть все элементы на 1 назад, а на первое место поставить последний в зависимости от dir
	for (int i = snake_length - 1; i > 0; --i) {
		snake[i][0] = snake[i - 1][0];
		snake[i][1] = snake[i - 1][1];
	}
	switch (direction) {
	// TODO: если змейка с границами, то % 8 не надо. И после move любом случае надо прогонять check_intersections
	case DOWN:{
		snake[0][0] = (snake[1][0] + 1) % 8;
		snake[0][1] = snake[1][1];
		break;
	}
	case UP: {
		snake[0][0] = (snake[1][0] - 1 + 8) % 8;
		snake[0][1] = snake[1][1];
		break;
	}
	case LEFT: {
		snake[0][0] = snake[1][0];
		snake[0][1] = (snake[1][1] - 1 + 8) % 8;
		break;
	}
	case RIGHT: {
		snake[0][0] = snake[1][0];
		snake[0][1] = (snake[1][1] + 1) % 8;
		break;
	}
	}
	// чтоб картинка поотображалась
	int cnt = 20; // убогий таймер...
	while (cnt > 0) {
	  render_snake(snake, snake_length);
	  cnt--;
	}
	//render_snake(snake, snake_length);
}

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

uint8_t check_apple() {
	return (snake[0][0] == apple_x && snake[0][1] == apple_y);
}

/* Make the snake longer.
 */
void longer_snake() {
	if (snake_length >= 63)
		end_game(1);
	else {
	  snake_length += 1;
	  render_snake(snake, snake_length);
	}
}

void setup_snake() {
	//render_snake(snake, snake_length);
	// чтоб картинка поотображалась
	int cnt = 20; // убогий таймер...
	while (cnt > 0) {
	  render_snake(snake, snake_length);
	  cnt--;
	}
	// gen apple
}

void run_snake() {
	if (game_flag) {
        move_snake();
		if (check_intersection()) {
			end_game(0);
			return;
		}
		//if (check_apple()) {
		//	longer_snake();
		//}
		run_snake();
	}
}
