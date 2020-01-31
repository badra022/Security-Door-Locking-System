 /******************************************************************************
 *
 * Module: uart
 *
 * File Name: uart.h
 *
 * Description: uart header file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
#ifndef MCAL_UART_H_
#define MCAL_UART_H_
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"../COMPLEX DRIVERS/micro_config.h"
#include"../COMPLEX DRIVERS/common_macros.h"
#include"../COMPLEX DRIVERS/std_types.h"
/*********************************************************************************
 * 							MODULE STATIC DEFINITIONS							 *
 *********************************************************************************/
/*
#define		RXC		7
#define		TXC		6
#define		UDRE	5
#define		FE		4
#define		DOR		3
#define		PE		2
#define		U2X		1
#define		MPCM	0
#define		RXCIE	7
#define		TXCIE	6
#define		UDRIE	5
#define		RXEN	4
#define		TXEN	3
#define		UCSZ2	2
#define		UCSZ1	2
#define		UCSZ0	1
#define		RXB8	1
#define		TXB8	0
#define		URSEL	7
#define		UMSEL	6
#define		UPM1	5
#define		UPM0	4
#define		USBS	3
#define		UCPOL	0
*/
/*********************************************************************************
* 								MODULE STATIC CONFIG							 *
 *********************************************************************************/
/*#define RECEIVE_INTERRUPT*/
#define BAUD_RATE		9600UL
/*********************************************************************************
* 								MODULE DYNAMIC CONFIG							 *
 *********************************************************************************/
typedef enum
{
	UART_PARITY_BIT_DISABLE ,
	UART_PARITY_BIT_ENABLE ,
}UART_parityBit;

typedef enum
{
	UART_PARITY_DISABLE ,
	UART_EVEN_PARITY = 2 ,
	UART_ODD_PARITY ,
}UART_parityType;

typedef enum
{
	UART_1_STOP_BIT ,
	UART_2_STOP_BIT ,
}UART_stopBit;

typedef enum
{
	UART_5_BIT ,
	UART_6_BIT ,
	UART_7_BIT ,
	UART_8_BIT ,
}UART_characterSize;

typedef enum
{
	UART_X ,
	UART_2X ,
}UART_Transmition_Speed;

typedef enum
{
	UART_ASYNCHRONOUS_OPERATION ,
	UART_SYNCHRONOUS_OPERATION ,
}UART_operation_type;
/**************************************************
 * [name] : UART_ConfigType
 * [Type] : Structure
 * [Function] : UART Module Dynamic configuration
 * [Members] :
 * 			Parity_enable enable or disable
 * 			Parity_type odd disable or even
 * 			stop_bit 1 or 2
 * 			character_size 5,6,7,8bits char
 * 			speed x or U2x
 * 			type  Sync or Async
 ***************************************************/
typedef struct
{
	UART_parityBit 			Parity_enable ;
	UART_parityType 		Parity_type ;
	UART_stopBit 			Stop_bit ;
	UART_characterSize		Char_Size ;
	UART_Transmition_Speed 	Speed ;
	UART_operation_type 	type ;
}UART_ConfigType;
/*********************************************************************************
 * 							MODULE SHARED GLOBAL VARIABLES						 *
 *********************************************************************************/
extern volatile uint8 g_UART_CurrentReading;
/*********************************************************************************
 * 								FUNCTIONS DECLARATIONS							 *
 *********************************************************************************/
void UART_init(const UART_ConfigType * a_ptr);

void UART_sendByte(uint8 data);

void UART_setReceiveCallBack(void (*a_ptr)(void));

void UART_sendString(const uint8 * str);

void UART_receiveString(uint8 * str);

#ifndef RECEIVE_INTERRUPT
uint8 UART_receiveByte(void);
#endif

#endif /* MCAL_UART_H_ */
