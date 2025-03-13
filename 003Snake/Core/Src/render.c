/*
 * render.c (003Snake)
 *
 *  Created on: Mar 10, 2025
 *      Author: tt
 */

#include "main.h"

uint16_t rows[] = {R1_Pin, R2_Pin, R3_Pin, R4_Pin, R5_Pin, R6_Pin, R7_Pin, R8_Pin};
uint16_t cols[] = {C1_Pin, C2_Pin, C3_Pin, C4_Pin, C5_Pin, C6_Pin, C7_Pin, C8_Pin};
GPIO_TypeDef *row_ports[] = {R1_GPIO_Port, R2_GPIO_Port, R3_GPIO_Port,
    R4_GPIO_Port, R5_GPIO_Port, R6_GPIO_Port, R7_GPIO_Port, R8_GPIO_Port};
GPIO_TypeDef *col_ports[] = {C1_GPIO_Port, C2_GPIO_Port, C3_GPIO_Port, C4_GPIO_Port,
    C5_GPIO_Port, C6_GPIO_Port, C7_GPIO_Port, C8_GPIO_Port};

/* Draw matrix column by column.
 */
void draw_columns(uint8_t matrix[8][8]) {
	for (uint8_t j = 0; j < 8; ++j) {
		// activate the row
		HAL_GPIO_WritePin(col_ports[j], cols[j], GPIO_PIN_RESET);
		// draw all rows of the column
		for (uint8_t i = 0; i < 8; ++i) {
			if (matrix[i][j]) {
				HAL_GPIO_WritePin(row_ports[i], rows[i], GPIO_PIN_SET);
			}
		}
		HAL_Delay(1);
		// turn off all the leds of this column
		for (uint8_t i = 0; i < 8; ++i) {
			HAL_GPIO_WritePin(row_ports[i], rows[i], GPIO_PIN_RESET);
		}
		//deactivate the row
		HAL_GPIO_WritePin(col_ports[j], cols[j], GPIO_PIN_SET);
	}
}

/* TODO: add apple
 */
void render_snake(uint8_t snake[64][2], uint8_t length) {
	uint8_t frame[8][8] = {
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0}
	};
	for (uint8_t i = 0; i < 3; ++i) {
		uint8_t row = snake[i][0],
		    col = snake[i][1];
		frame[row][col] = 1;
	}
	draw_columns(frame);
/*
    // чтоб картинка поотображалась
	int cnt = 20; // убогий таймер...
	while (cnt > 0) {
	  render_snake(snake, length);
	  cnt--;
	}*/
	/*
	clock_t time = clock();

	while ((clock() - time) / CLOCKS_PER_SEC < 1) {
	render_snake(snake, snake_length);
	}
	*/
}


