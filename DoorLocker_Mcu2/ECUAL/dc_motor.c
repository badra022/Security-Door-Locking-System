 /******************************************************************************
 *
 * Module: dc motor
 *
 * File Name: dc_motor.c
 *
 * Description: dc_motor src file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"dc_motor.h"
/*********************************************************************************
 * 								Function Definitions							 *
 *********************************************************************************/
void DCMOTOR_init(void)
{
	SET_BIT(DC_MOTOR_DIR , IN1);
	SET_BIT(DC_MOTOR_DIR , IN2);
	SET_BIT(DC_MOTOR_DIR , EN1);
}
void DCMOTOR_setSpeed(void)
{
	SET_BIT(DC_MOTOR_PORT , EN1);
}
void DCMOTOR_move(void)
{
	SET_BIT(DC_MOTOR_PORT , IN1);
	CLEAR_BIT(DC_MOTOR_PORT , IN2);
}
void DCMOTOR_toggleMove(void)
{
	TOGGLE_BIT(DC_MOTOR_PORT , IN2);
	TOGGLE_BIT(DC_MOTOR_PORT , IN1);
}
void DCMOTOR_stop(void)
{
	CLEAR_BIT(DC_MOTOR_PORT , IN2);
	CLEAR_BIT(DC_MOTOR_PORT , IN1);
}
