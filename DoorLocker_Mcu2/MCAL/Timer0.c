 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.c
 *
 * Description: Timer0 src file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/

/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"timer0.h"
#include"../ECUAL/lcd.h"
/*********************************************************************************
* 									Global Variables							 *
 *********************************************************************************/
static void (*volatile g_T0CompareInterruptFunc_ptr)(void) = NULL;
static void (*volatile g_T0OverflowInterruptFunc_ptr)(void) = NULL;
volatile uint8 g_t0tick = 0;
/*********************************************************************************
* 									Functions Definition						 *
 *********************************************************************************/
void TIMER0_setCallBackCompareMode(void (*a_ptr)(void))
{
	g_T0CompareInterruptFunc_ptr = a_ptr;
}
void TIMER0_setCallBackOverflowMode(void (*a_ptr)(void))
{
	g_T0OverflowInterruptFunc_ptr = a_ptr;
}
void TIMER0_init(const TIMER0_configType * config_ptr)
{
	TCCR0 = 0;
	TCCR0 = config_ptr->mode;
	if(config_ptr->mode == TIMER0_NORMAL || config_ptr->mode == TIMER0_CTC)
	{
		SET_BIT(TCCR0 , FOC0);
	}
	else
	{
		CLEAR_BIT(TCCR0 , FOC0);
	}
	TCCR0 |= ((config_ptr->output_mode) << 4) | config_ptr ->clock;
	TCNT0 = config_ptr->initial_value;
	OCR0 = config_ptr->compare_value;
	if(config_ptr->output_mode != TIMER0_NORMAL_OUTPUT )
	{
		SET_BIT(DDRB , 3);
		CLEAR_BIT(PORTB , 3);
	}
	TIMSK |= config_ptr->overflow_interrupt | ((config_ptr ->compare_interrupt)<<OCIE0);
}
void TIMER0_start(TIMER0_clock clk)
{
	TCNT0 = 0;
	TCCR0 |= clk;
}
void TIMER0_setCompareValue(uint8 value)
{
	OCR0 = value;
}
void TIMER0_stop(void)
{
	CLEAR_BIT(TCCR0 , 0);
	CLEAR_BIT(TCCR0 , 1);
	CLEAR_BIT(TCCR0 , 2);
}
/*********************************************************************************
* 								Interrupt service routines							 *
 *********************************************************************************/
ISR(TIMER0_COMP_vect)
{
	LCD_displayString("hey!");
	g_t0tick--;

	if(g_T0CompareInterruptFunc_ptr != NULL)
	{
		g_T0CompareInterruptFunc_ptr();
	}
}
ISR(TIMER0_OVF_vect)
{
	if(g_T0OverflowInterruptFunc_ptr != NULL)
	{
		g_T0OverflowInterruptFunc_ptr();
	}
}
