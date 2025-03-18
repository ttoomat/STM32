/*
 * render.h
 *
 *  Created on: Mar 18, 2025
 *      Author: tt
 */

#ifndef INC_RENDER_H_
#define INC_RENDER_H_

void turn_off_display();

void display_big_num(uint16_t number);

void display_time(uint32_t sec);

void display_num(uint8_t number, uint8_t digit);

#endif /* INC_RENDER_H_ */
