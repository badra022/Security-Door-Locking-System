/******************************************************************************
 *
 * Module: timer0 , uart , i2c
 *
 * File Name: application.h
 *
 * Description: app src file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"../ECUAL/lcd.h"
#include"../ECUAL/keypad.h"
#include"../MCAL/uart.h"
#include"../MCAL/timer0.h"
#include"../MCAL/timer1.h"
/***************************************************************************************
 * 									GLOBAL VARIABLES									*
 ***************************************************************************************/
#define PASSWORD_ADDRESS 	(uint16)0x10
#define MC2_READY			0x00
/* to inform MC1 that MC2 ready to receive */
#define MC1_READY			0x01
/* to inform MC2 that MC1 ready to receive */
/*****************************************************************************
 *  so the protocol goes as follows
 * 1. if MC1 finished some code and want to transmit byte or string to MC2
 * 	it must check at MC2_READY flag , once it's received it can transmit the data to MC2
 * 2. if MC2 finished some code and want to transmit byte or string to MC2
 * 	it must check at MC1_READY flag , once it's received it can transmit the data to MC1
 *****************************************************************************/
uint8 password[20];
uint16 i;
uint8 input;
uint8 output;
uint8 DELAY_DONE;
/*********************************************************************************
 * 									APPLICATION									 *
 *********************************************************************************/

/****************************DESCRIPTION*********************************
 * the user interface Mcu that takes the inputs from the keypad
 * and displays the status to the user(interact with the user)
 *
 * 1. at the start it checks for a password exist in eeprom or not
 * 2. if the password exist it will show the options list
 * 3. if not it will ask for a new password
 * 4. if option change password -> ask for new password , confirm , and 3 trials
 * 5. then return to options list
 * 6. if option open door -> enter the pass , 3 trials
 * 7. if password match -> rotate the motor clockwise 15 seconds
 * 		then rotate it unti-cw for 15 seconds indicating the closing again
 * 		during this step the lcd displaying th status of the door -> opening or closing
 * 8. any check for password has 3 trials if exceeded it will activate the buzzer for 60 sec
 ************************************************************************/



void Mcu2_init(void)
{
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

	UART_ConfigType UART_configStruct = {	UART_PARITY_BIT_DISABLE ,
											UART_PARITY_DISABLE ,
											UART_1_STOP_BIT ,
											UART_8_BIT ,
											UART_2X ,
											UART_ASYNCHRONOUS_OPERATION ,};

	UART_init(&UART_configStruct);
}
/***********************************test*********************************************/
uint8 DELAY_DONE;
void toggle(void)
{
	// toggle the led
	g_t1tick--;
	if(!g_t1tick)
	{
		DELAY_DONE = TRUE;
	}

}
void TIMER1_delay_init(void)
{

/******************************************************
 * [name] : TIMER1_configType
 * [Type] : Structure
 * [Function] : TIMER1 Module Dynamic configuration
 * [Members] :
 * 			mode TIMER1_NORMAL or TIMER1_CTC (16bit only so it's not a conig for me)
 * 			output_mode TIMER1_NORMAL_OUTPUT or TIMER1_TOGGLE_OUTPUT etc..
 * 			compare_interrupt enable or disable
 * 			overflow_interrupt enable or disable
 * 			compare_value 0 -> 65535
 * 			initial_value 0 -> 65535
 ***************************************************/



	TIMER1_configType TIMER1_configStruct = { 	TIMER1_CTC ,
												TIMER0_F_CPU_1024 ,
												ENABLE ,
												DISABLE ,
												7812 ,
												0	};
		TIMER1_init(&TIMER1_configStruct);
		TIMER1_setCallBackCompareMode(toggle);

}
void TIMER1_delay(uint8 seconds)
{
	DELAY_DONE = FALSE;
	g_t1tick =seconds;
	TIMER1_start(TIMER0_F_CPU_1024);
	while(!DELAY_DONE){}
}
/***********************************test*********************************************/
/***************************************************************************************
 * 									MAIN  FUNCTION										*
 ***************************************************************************************/
int main(void)/*MCU1*/
{
	/*initializaiton code*/
	LCD_init();
	KEYPAD_init();
	TIMER1_delay_init();
	Mcu2_init();
	GLOBAL_INTERRUPT_ENABLE();
	LCD_displayOnColRow(0 , 4 , (uint8*)"welcome");
	TIMER1_delay(3);
	LCD_displayString((uint8*)"hey!");
	//LCD_displayString((uint8*)"hey!");
	LCD_clearScreen();
	/******************************************************************
	 * permanent task : try timer1 for the delay and figure the bug in timer0 another time
	 ******************************************************************/


	/*continue */

	while(TRUE)
	{

		/* Application code*/

	}

}
