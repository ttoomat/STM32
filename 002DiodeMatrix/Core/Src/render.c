/*
 * render.c
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

/* Turn on particular Led on Led Matrix.
 * ARGUMENTS:
 *   - char row (1..8)
 *   - char column (1..8)
 */
void led_row_col(int row, int column) {
  if (row < 0 || row > 7 || column < 0 || column > 7) return;
  HAL_GPIO_WritePin(row_ports[row], rows[row], GPIO_PIN_SET);
  HAL_GPIO_WritePin(col_ports[column], cols[column], GPIO_PIN_RESET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(row_ports[row], rows[row], GPIO_PIN_RESET);
  HAL_GPIO_WritePin(col_ports[column], cols[column], GPIO_PIN_SET);
}

/* Draw matrix column by column.
 */
void draw_columns(int matrix[8][8]) {
	for (int j = 0; j < 8; ++j) {
		// activate the row
		HAL_GPIO_WritePin(col_ports[j], cols[j], GPIO_PIN_RESET);
		// draw all rows of the column
		for (int i = 0; i < 8; ++i) {
			if (matrix[i][j]) {
				HAL_GPIO_WritePin(row_ports[i], rows[i], GPIO_PIN_SET);
			}
		}
		HAL_Delay(1);
		// turn off all the leds of this column
		for (int i = 0; i < 8; ++i) {
			HAL_GPIO_WritePin(row_ports[i], rows[i], GPIO_PIN_RESET);
		}
		//deactivate the row
		HAL_GPIO_WritePin(col_ports[j], cols[j], GPIO_PIN_SET);
	}
}

/* Display a matrix 8x8.
 * Matrix elements -- 0/1
 * проблема -- видно мигание
 */
void draw_matrix(int matrix[8][8]) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (matrix[i][j])
				led_row_col(i, j);
		}
	}
}
