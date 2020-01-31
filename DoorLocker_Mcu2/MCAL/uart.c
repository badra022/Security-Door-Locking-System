 /******************************************************************************
 *
 * Module: uart
 *
 * File Name: uart.c
 *
 * Description: uart src file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/

#include"uart.h"
#define BAUD_PRESCALE (((F_CPU / (8 * BAUD_RATE))) - 1)

/*********************************************************************************
 * 								Global variables								 *
 *********************************************************************************/

volatile uint8 g_UART_CurrentReading = 0;
static volatile void (* g_UART_receiveByteFunc_ptr)(void) = NULL;

/*********************************************************************************
 * 								Function Definitions							 *
 *********************************************************************************/

void UART_init(const UART_ConfigType * a_ptr)
{
	UCSRA = (a_ptr->Parity_enable <<PE) | (a_ptr->Speed << U2X);

	#ifdef RECEIVE_INTERRUPT

	SET_BIT(UCSRB , RXCIE);

	GLOBAL_INTERRUPT_ENABLE();

	#endif

	#ifndef RECEIVE_INTERRUPT

	CLEAR_BIT(UCSRB , RXCIE);

	#endif

	UCSRC = (a_ptr->Char_Size << UCSZ0) | (a_ptr->Parity_type << UPM0) |
			(1<<URSEL) | (a_ptr->type << UMSEL) | (a_ptr->Stop_bit << USBS);

	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;

	SET_BIT(UCSRB , TXEN);

	SET_BIT(UCSRB , RXEN);

}

void UART_sendByte(uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA , UDRE));

	UDR = data;
}
#ifndef RECEIVE_INTERRUPT
uint8 UART_receiveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA ,RXC));

	g_UART_CurrentReading = UDR;

	return UDR;
}
#endif
void UART_setReceiveCallBack(volatile void (*a_ptr)(void))
{
	g_UART_receiveByteFunc_ptr = a_ptr;
}
void UART_sendString(const uint8 * str)
{
	uint8 count = 0;

	while(str[count] != '\0')
	{
		UART_sendByte(str[count]);
		count++;
	}
}
void UART_receiveString(uint8 * str)
{
	uint8 count = 0;

	do
	{
		str[count] = UART_receiveByte();
		count++;
	}while(str[count] != '*');

	str[count] = '\0';
	/****************ANOTHER METHOD****************************************
	 * do
	 * {
	 * 		*str = UART_receiveByte();
	 * 		str++;
	 * 	}while(*str != '*');
	 *
	 * 	*str = '\0';
	 ***********************************************************************/
}

/*********************************************************************************
 * 								interrupt service routines						 *
 *********************************************************************************/
#ifdef RECEIVE_INTERRUPT
ISR(USART_RXC_vect)
{
	g_UART_CurrentReading = UDR;

	if(g_UART_receiveByteFunc_ptr == NULL)
	{
		g_UART_receiveByteFunc_ptr();
	}
}
#endif
