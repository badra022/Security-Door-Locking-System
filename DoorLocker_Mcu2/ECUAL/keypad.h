/*
 * keypad.h
 *
 *  Created on: Dec 27, 2019
 *      Author: badra069
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"../COMPLEX DRIVERS/micro_config.h"
#include"../COMPLEX DRIVERS/common_macros.h"
#include"../COMPLEX DRIVERS/std_types.h"

#define N_COL			4
#define N_ROW			4
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN	PINC
#define KEYPAD_PORT_DIR	DDRC
extern uint8 current_key;
/************************************************FUNCTIONS PROTOTYPES**********************************************/
void KEYPAD_init(void);
uint8 KEYPAD_getPressed(void);
#endif /* KEYPAD_H_ */
