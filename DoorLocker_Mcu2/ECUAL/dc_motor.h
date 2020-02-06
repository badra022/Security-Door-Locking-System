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
#include"../COMPLEX DRIVERS/micro_config.h"
#include"../COMPLEX DRIVERS/common_macros.h"
#include"../COMPLEX DRIVERS/std_types.h"
/*********************************************************************************
 * 							Definitions and Configurations						 *
 *********************************************************************************/
#define DC_MOTOR_DIR	DDRB
#define DC_MOTOR_PORT	PORTB
#define IN1				0
#define IN2				1
#define EN1				2
/*********************************************************************************
 * 								Function Declarations							 *
 *********************************************************************************/
void DCMOTOR_init(void);

void DCMOTOR_setSpeed(void);

void DCMOTOR_toggleMove(void);

void DCMOTOR_move(void);

void DCMOTOR_stop(void);



#endif /* DC_MOTOR_H_ */
