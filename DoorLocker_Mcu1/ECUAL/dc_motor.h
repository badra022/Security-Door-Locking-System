 /******************************************************************************
 *
 * Module: dc_motor
 *
 * File Name: dc_motor.h
 *
 * Description: dc motor header file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"../MCAL/timer0.h"
/*********************************************************************************
 * 							Definitions and Configurations						 *
 *********************************************************************************/
#define DC_MOTOR_DIR	DDRB
#define DC_MOTOR_PORT	PORTB
#define IN1				2
#define IN2				1
#define EN1				OC0
/*********************************************************************************
 * 								Function Declarations							 *
 *********************************************************************************/
void DCMOTOR_init(void);
void DCMOTOR_setSpeed(uint8 speed);
void DCMOTOR_toggleMove(void);
void DCMOTOR_move(void);
void DCMOTOR_stop(void);


#endif /* DC_MOTOR_H_ */
