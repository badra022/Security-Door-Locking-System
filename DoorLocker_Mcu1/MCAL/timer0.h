 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.h
 *
 * Description: Timer0 header file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"../COMPLEX DRIVERS/micro_config.h"
#include"../COMPLEX DRIVERS/common_macros.h"
#include"../COMPLEX DRIVERS/std_types.h"
/*********************************************************************************
* 								Types Declarations							 *
 *********************************************************************************/
extern volatile uint8 g_t0tick;
typedef enum
{
	TIMER0_NORMAL = 0x00 ,
	TIMER0_PWM_PHASE_CORRECT = 0x40 ,
	TIMER0_CTC = 0x08 ,
	TIMER0_FAST_PWM = 0x48 ,
}TIMER0_mode;

typedef enum
{
	TIMER0_NORMAL_OUTPUT ,
	TIMER0_TOGGLE_OUTPUT,
	TIMER0_CLEAR_OUTPUT ,
	TIMER0_SET_OUTPUT ,
}TIMER0_Compare_output_mode;

typedef enum
{
	TIMER0_NON ,
	TIMER0_F_CPU ,
	TIMER0_F_CPU_8 ,
	TIMER0_F_CPU_64 ,
	TIMER0_F_CPU_256 ,
	TIMER0_F_CPU_1024 ,
	TIMER0_PIN_FALLING_EDGE ,
	TIMER0_PIN_RAISING_EDGE ,
}TIMER0_clock;
/**************************************************
 * [name] : TIMER0_configType
 * [Type] : Structure
 * [Function] : TIMER0 Module Dynamic configuration
 * [Members] :
 * 			mode TIMER0_NORMAL or TIMER0_PWM_PHASE_CORRECT or TIMER0_CTC etc..
 * 			output_mode TIMER0_NORMAL_OUTPUT or TIMER0_TOGGLE_OUTPUT etc..
 * 			clock TIMER0_NON , F_CPU , 8 , 64 , 256 , 1024
 * 			compare_interrupt enable or disable
 * 			overflow_interrupt enable or disable
 * 			compare_value 0 -> 255
 * 			initial_value 0 -> 255
 ***************************************************/
typedef struct
{
	TIMER0_mode mode;
	TIMER0_Compare_output_mode output_mode;
	TIMER0_clock clock;
	uint8 compare_interrupt;
	uint8 overflow_interrupt;
	uint8 compare_value;
	uint8 initial_value;
}TIMER0_configType;

/*********************************************************************************
* 								Function Declarations							 *
 *********************************************************************************/
void TIMER0_init(const TIMER0_configType * config_ptr);

void TIMER0_setCompareValue(uint8 value);

void TIMER0_start(TIMER0_clock clk);

void TIMER0_stop(void);

void TIMER0_setCallBackCompareMode(void (*a_ptr)(void));

void TIMER0_setCallBackOverflowMode(void (*a_ptr)(void));

#endif /* TIMER0_H_ */
