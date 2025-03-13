/*
 * logic.h (003Snake)
 *
 *  Created on: 13 мар. 2025 г.
 *      Author: tt
 */

#ifndef INC_LOGIC_H_
#define INC_LOGIC_H_

enum dir {
	RIGHT, LEFT, UP, DOWN
};

void set_direction(enum dir new_direction);

/* Setup snake & apple position.
 */
void setup_snake();

/* Update snake position. Game process.
 */
void run_snake();

#endif /* INC_LOGIC_H_ */
