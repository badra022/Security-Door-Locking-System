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
extern volatile uint16 g_t0tick;
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
	TIMER0_PIN_FALLING_EDGE , /* T0 pin in the MCU*/
	TIMER0_PIN_RAISING_EDGE , /* T0 pin in the MCU*/
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
/**********************************************************
 * [FUNCTION NAME] : TIMER0_init
 * [FUNCTION TYPE] : void
 * [TASK] :
 * 		1.setting the FOC0 bit according to the mode selected
 * 		2.initiating the counter value with a selected init value
 * 		3.setting a compare value in the OCR0
 * 		4.setting the mode of the OC0 pin as selected in the config structure
 * 		5.setting OC0 as output pin if a pwm mode selected in the config struct
 * 		6.setting OVF interrupt or COM interrupt as selected in the config struct
 * 		7.finally starting the timer
 * [ARGS] :
 *	pointer to the configuration structure :
 *		indicating a constant configurations from the user in the main application
 ***********************************************************/
void TIMER0_setCompareValue(uint8 value);
/**********************************************************
 * [FUNCTION NAME] : TIMER0_setCompareValue
 * [FUNCTION TYPE] : void
 * [TASK] : setting a new compare value in the OCR0
 * [ARGS] :
 * 	an unsigned character value :
 * 		indicating the compare value to be set in the OCR0
 ***********************************************************/
void TIMER0_start(TIMER0_clock clk);
/**********************************************************
 * [FUNCTION NAME] : TIMER0_start
 * [FUNCTION TYPE] : void
 * [TASK] : starting the timer with a certain clock (PRESCALER) and initiating the TCNT0
 * [ARGS] :
 * 	unsigned character value :
 * 		indicating the value to be set in the TCCR0 register to set the selected prescaler
 ***********************************************************/
void TIMER0_stop(void);
/**********************************************************
 * [FUNCTION NAME] : TIMER0_stop
 * [FUNCTION TYPE] : void
 * [TASK] : settingg the prescaler of the timer clock as NON
 * 			thus No clock provided(STOPPING)
 ***********************************************************/
void TIMER0_setCallBackCompareMode(void (*a_ptr)(void));
/**********************************************************
 * [FUNCTION NAME] : TIMER0_setCallBackCompareMode
 * [FUNCTION TYPE] : void
 * [TASK] : setting the code of the compare match interrupt service routine (ISR)
 * [ARGS] :
 * 	pointer to void function which takes void arguments :
 * 		indicating the code that will be executed in the ISR of the compare match
 ***********************************************************/
void TIMER0_setCallBackOverflowMode(void (*a_ptr)(void));
/**********************************************************
 * [FUNCTION NAME] : TIMER0_setCallBackOverflowMode
 * [FUNCTION TYPE] : void
 * [TASK] : setting the code of the overflow interrupt service routine (ISR)
 * [ARGS] :
 * 	pointer to void function which takes void arguments :
 * 		indicating the code that will be executed in the ISR of the overflow
 ***********************************************************/
#endif /* TIMER0_H_ */
