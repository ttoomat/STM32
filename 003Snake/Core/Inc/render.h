/*
 * render.h (003Snake)
 *
 *  Created on: Mar 10, 2025
 *      Author: tt
 */

#ifndef SRC_RENDER_H_
#define SRC_RENDER_H_

/* Game over matrix.
 */
static uint8_t you_lose[8][8] = {
		{1, 1, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 0, 0, 1, 1, 1},
		{0, 1, 1, 0, 0, 1, 1, 0},
		{0, 0, 1, 1, 1, 0, 1, 0},
		{0, 0, 0, 1, 1, 0, 0, 0},
		{0, 1, 1, 0, 1, 1, 0, 0},
		{1, 1, 1, 0, 0, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 1, 1}
};

static uint8_t good_game[8][8] = {
		{0, 0, 0, 1, 1, 0, 0, 0},
		{0, 1, 1, 0, 0, 1, 1, 0},
		{1, 1, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 1, 1},
		{0, 1, 1, 0, 0, 1, 1, 0},
		{0, 0, 0, 1, 1, 0, 0, 0}
};

void render_snake(uint8_t snake[64][2], volatile uint8_t length, uint8_t apple_x, uint8_t apple_y);

/* Draw matrix column by column.
 */
void draw_columns(uint8_t matrix[8][8]);

#endif /* SRC_RENDER_H_ */
