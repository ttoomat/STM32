/*
 * auxiliary.c
 *
 *  Created on: Mar 19, 2025
 *      Author: tt
 */

//#include <stdlib.h> // string

#include <stdio.h>
#include <stdint.h>
#include <string.h>

//#include "main.h"

uint8_t led_status[] = {'0', '0'};
uint8_t led_number = 2;

void set_led_status(uint8_t* status) {
	for (uint8_t i = 0; i < led_number; ++i) {
		if (status[i] == '1')
			led_status[i] = '1';
		else
			led_status[i] = '0';
	}
}

uint8_t* get_led_status() {
	return led_status;
}

uint8_t data_interpretation(uint8_t *data, uint8_t size) {
	const uint8_t *ALON = (uint8_t *)"ALON",
			*ALOF = (uint8_t *)"ALOF",
			*DATA = (uint8_t *)"DATA",
			*PING = (uint8_t *)"PING",
			*ONV1 = (uint8_t *)"ONV1",
			*ONV2 = (uint8_t *)"ONV2";

	 if (memcmp(data, ALOF, size) == 0) return 1;
	 if (memcmp(data, ALON, size) == 0) return 2;
	 if (memcmp(data, ONV1, size) == 0) return 3;
	 if (memcmp(data, ONV2, size) == 0) return 4;
	 if (memcmp(data, PING, size) == 0) return 5;
	 if (memcmp(data, DATA, size) == 0) return 6;
	 return 0;
}


