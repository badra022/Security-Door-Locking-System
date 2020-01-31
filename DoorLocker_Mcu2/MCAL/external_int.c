 /******************************************************************************
 *
 * Module: Lcd
 *
 * File Name: lcd.h
 *
 * Description: lcd header file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"external_int.h"
/*********************************************************************************
* 							Global variables									 *
 *********************************************************************************/
static volatile void (*g_INT0_interruptFunc_ptr)(void) = NULL;
static volatile void (*g_INT1_interruptFunc_ptr)(void) = NULL;
static volatile void (*g_INT2_interruptFunc_ptr)(void) = NULL;
/*********************************************************************************
* 								Function Definitions							 *
 *********************************************************************************/
void INT0_init(Int0_ctrl mode , Input_state state)
{
	MCUCR |= mode;
	SET_BIT(GICR , 6);
	CLEAR_BIT(DDRD , PD2);
	SET_VALUE(PORTD , PD2 , state);
}
void INT1_init(Int1_ctrl mode , Input_state state)
{
	MCUCR |= mode<<ISC10;
	SET_BIT(GICR , 7);
	CLEAR_BIT(DDRD , PD3);
	SET_VALUE(PORTD , PD3 , state);
}
void INT2_init(Int2_ctrl mode , Input_state state)
{
	SET_VALUE(MCUCSR , ISC2 , mode);
	SET_BIT(GICR , 5);
	CLEAR_BIT(DDRB , PB2);
	SET_VALUE(PORTB , PB2 , state);
}
void INT0_setCallBack(void (*a_ptr)(void))
{
	g_INT0_interruptFunc_ptr = a_ptr;
}
void INT1_setCallBack(void (*a_ptr)(void))
{
	g_INT1_interruptFunc_ptr = a_ptr;
}
void INT2_setCallBack(void (*a_ptr)(void))
{
	g_INT2_interruptFunc_ptr = a_ptr;
}
/*********************************************************************************
 * 								interrupt service routines						 *
 *********************************************************************************/
ISR(INT0_vect)
{
	if(g_INT0_interruptFunc_ptr != NULL)
	{
		g_INT0_interruptFunc_ptr();
	}
}
ISR(INT1_vect)
{
	if(g_INT1_interruptFunc_ptr != NULL)
	{
		g_INT1_interruptFunc_ptr();
	}
}
ISR(INT2_vect)
{
	if(g_INT2_interruptFunc_ptr != NULL)
	{
		g_INT2_interruptFunc_ptr();
	}
}
