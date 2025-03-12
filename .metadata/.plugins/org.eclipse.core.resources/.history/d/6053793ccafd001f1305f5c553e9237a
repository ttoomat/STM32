/*
 * render.h
 *
 *  Created on: Mar 10, 2025
 *      Author: tt
 */

#ifndef SRC_RENDER_H_
#define SRC_RENDER_H_

int music[8][8] = {
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 1, 0, 1, 0},
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
};

int tea[8][8] = {
		{0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 0, 0, 0, 1, 0, 1},
		{0, 1, 0, 0, 0, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 0, 0},
};

/* Turn on particular Led on Led Matrix.
 * ARGUMENTS:
 *   - char row (1..8)
 *   - char column (1..8)
 */
void led_row_col(char row, char column);

/* Draw matrix column by column.
 */
void draw_columns(int matrix[8][8]);

/* Display a matrix 8x8.
 * Matrix elements -- 0/1
 */
//void draw_matrix(int matrix[8][8]);

#endif /* SRC_RENDER_H_ */
