/*
 * auxiliary.h
 *
 *  Created on: Mar 19, 2025
 *      Author: tt
 */

#ifndef INC_AUXILIARY_H_
#define INC_AUXILIARY_H_

void set_led_status(uint8_t* status);
uint8_t* get_led_status();

uint8_t data_interpretation(uint8_t *data, uint8_t size);

#endif /* INC_AUXILIARY_H_ */
