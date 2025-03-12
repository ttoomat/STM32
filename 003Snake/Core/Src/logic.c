/*
 * logic.c
 *
 *  Created on: Mar 10, 2025
 *      Author: tt
 */

// TODO: winking apple in order to differentiate it from the snake.

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for better random

/* A target for the snake.
 */
/*
struct apple {
	int x, y;
};
*/

/* A structure for snake.
 * Linked list and coordinates.
 */
/*
struct snake {
	struct snake * next;
	int c, r;
};
*/

/* Set a target for snake.
 * Call this function in setup & when apple is eaten.
 */
void generate_apple(int* apple_x, int* apple_y) {
	*apple_x = rand(clock()) % 8;
	*apple_y = rand(clock()) % 8;
	// TODO: apple only in free space
}

/* Snake setup.
 */
int** little_snake(int* rows, int* cols) {
    *rows = 3;
    *cols = 2;

    // allocate memory
    int** snake = (int**)malloc(*rows * sizeof(int*));
    for (int i = 0; i < *rows; ++i) {
        snake[i] = (int*)malloc(*cols * sizeof(int));
    }
    // initialize
    snake[0][0] = 3; snake[0][1] = 3;
    snake[1][0] = 3; snake[1][1] = 2;
    snake[2][0] = 3; snake[2][1] = 1;
    return snake;
}

/* Move snake according to the direction.
 */
void move_snake(int** snake, int* length, int* coords) {
	//
}

/* Make the snake longer.
 */
void longer_snake(int** snake, int* length, int* coords) {
	length += 1;
	// copy snake to other array
	// allocate memory for new bigger snake
	// the first point is new, others are copy of previous snake
}

void setup() {
	int* snake_length;
	int* coords;
	int** snake = little_snake(snake_length, coords);
	// generate & show matrix from the struct apple * /(apple_x, apple_y) and int** snake, int* snake_length, int* coords
    // run: every 300ms move snake + check button -- multithreading? (no, just interrupts) + regenerate apple when needed
}
