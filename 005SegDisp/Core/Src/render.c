/*
 * render.c
 *
 *  Created on: Mar 18, 2025
 *      Author: tt
 */

#include "main.h"

uint16_t segment_pins[] = {A_Pin, B_Pin, C_Pin, D_Pin, E_Pin, F_Pin, G_Pin, DP_Pin}; // A, B, C, D, E, F, G, DP pins
GPIO_TypeDef* segment_ports[] = {A_GPIO_Port, B_GPIO_Port, C_GPIO_Port, D_GPIO_Port,
		E_GPIO_Port, F_GPIO_Port, G_GPIO_Port, DP_GPIO_Port};

uint16_t display_pins[] = {D1_Pin, D2_Pin, D3_Pin, D4_Pin};
GPIO_TypeDef* display_ports[] = {D1_GPIO_Port, D2_GPIO_Port, D3_GPIO_Port, D4_GPIO_Port};

/* Codes of numbers 0-9 */
uint8_t num[10][8] = {{1, 1, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 0, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1, 0},
  {1, 1, 1, 1, 0, 0, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 0, 1, 1, 0, 1, 1, 0},
  {1, 0, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0, 1, 1, 0}};

uint8_t n_seg = 8, n_disp = 4; // number of display segments

void turn_off_display() {
	// HIGH на все дисплеи, LOW на все сегменты
	for (uint8_t i = 0; i < n_disp; i++) {
			HAL_GPIO_WritePin(display_ports[i], display_pins[i], GPIO_PIN_SET);
	}
	for (uint8_t i = 0; i < n_seg; i++) {
		HAL_GPIO_WritePin(segment_ports[i], segment_pins[i], GPIO_PIN_RESET);
	}
}

/* Number -- число от 0 до 9, digit -- номер дисплея от 0 до 3.
 */
void display_num(uint8_t number, uint8_t digit) {
	if (number > 9 || digit >= n_disp) return;
	turn_off_display();
	// LOW на номер дисплея
	HAL_GPIO_WritePin(display_ports[digit], display_pins[digit], GPIO_PIN_RESET);
	// HIGH на сегменты дисплея
	for (uint8_t i = 0; i < n_seg; i++) {
		if (num[number][i]) {
			HAL_GPIO_WritePin(segment_ports[i], segment_pins[i], GPIO_PIN_SET);
		}
	}
	if (digit == 1) HAL_GPIO_WritePin(segment_ports[7], segment_pins[7], GPIO_PIN_SET);
	HAL_Delay(1);
}

struct time {
  uint8_t h, m, s;
};

// перевод секунд в часы минуты секунды
struct time sec_to_time(uint32_t sec) {
  uint32_t minutes = sec / 60,
           hours = minutes / 60;
  struct time t;
  t.s = sec % 60;
  t.m = minutes % 60;
  t.h = hours;
  return t;
}

void display_time(uint32_t sec) {
	struct time t = sec_to_time(sec);
	uint8_t a = (t.m / 10) % 10,
				b = t.m % 10,
				c = (t.s / 10) % 10,
				d = t.s % 10;
		display_num(a, 0);
		display_num(b, 1);
		display_num(c, 2);
		display_num(d, 3);
}

void display_big_num(uint16_t number) {
	if (number > 9999) return;
	uint8_t a = (number / 1000) % 10,
			b = (number / 100) % 10,
			c = (number / 10) % 10,
			d = number % 10;
	display_num(a, 0);
	display_num(b, 1);
	display_num(c, 2);
	display_num(d, 3);
}

