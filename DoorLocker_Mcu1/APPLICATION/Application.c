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

void UART_clearPort(void)
{
	UDR = 0;
}

void Mc2_init(void)
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
	UART_clearPort();
}

/***************************************************************************************
 * 									GLOBAL VARIABLES									*
 ***************************************************************************************/
#define PASSWORD_ADDRESS 	0x0010
#define MC2_READY			0xFC
/* to inform MC1 that MC2 ready to receive */
#define MC1_READY			0xAB
/* to inform MC2 that MC1 ready to receive */
/*****************************************************************************
 *  so the protocol goes as follows
 * 1. if MC1 finished some code and want to transmit byte or string to MC2
 * 	it must check at MC2_READY flag , once it's received it can transmit the data to MC2
 * 2. if MC2 finished some code and want to transmit byte or string to MC2
 * 	it must check at MC1_READY flag , once it's received it can transmit the data to MC1
 *****************************************************************************/
uint8 password[20];
uint8 same = FALSE;
uint16 i;
uint8 input;
uint8 output;
uint8 DELAY_DONE;
/***************************************************************************************
 * 									MAIN  FUNCTION										*
 ***************************************************************************************/
//LCD_displayString((uint8*)"hey!");

/*****************************************
 *
 	//for MC1 receive and MC2 transmit
  	while(UART_receiveByte() != MC2_READY){}
	UART_sendByte(MC1_READY);

	//for MC1 transmit and MC2 receive
	send(MC1_READY);
	while(UART_receiveByte() != MC2_READY){}
 *****************************************/

int main(void)/*MCU1*/
{
	/*initializaiton code*/

	KEYPAD_init();
	LCD_init();
	Mc2_init();
 	//for MC1 receive and MC2 transmit
	UART_sendByte(MC1_READY);
	UART_receiveString(password);
	LCD_displayString(password);


#if 0
	LCD_displayOnColRow(0 , 4 , (uint8*)"welcome");
	_delay_ms(3000);
	LCD_clearScreen();*/

	uint8 new_launch = FALSE;
	UART_clearPort();

	//for MC1 receive and MC2 transmit
	while(UART_receiveByte() != MC2_READY){}
	LCD_displayString((uint8*)"hey!");
	UART_sendByte(MC1_READY);
	LCD_displayString((uint8*)"hey!");
	new_launch = UART_receiveByte();
	LCD_displayString((uint8*)"hey!");

	if(password == 0x00) /*new launch*/
	{
		LCD_clearScreen();
		LCD_displayOnColRow(0 , 0 , (uint8*)"enter new pass:");
		int i = 0;
		LCD_goToColRow(1 , 0);
		while(KEYPAD_getPressed() != '=')
		{
			LCD_displayCharacter('*');
			password[i] = current_key;
			i++;
		}
		while(!same)
		{
			same = TRUE;
			LCD_clearScreen();
			LCD_displayOnColRow(0 , 0 , (uint8*)"confirm :");
			int i = 0;
			LCD_goToColRow(1 , 0);
			while(KEYPAD_getPressed() != '=')
			{
				LCD_displayCharacter('*');
				if(current_key != password[i])
				{
					same = FALSE;
				}
				i++;
			}
			if(!same)
			{
				LCD_clearScreen();
				LCD_displayOnColRow(0 ,4 ,(uint8*)"Wrong");
				_delay_ms(2000);
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString((uint8*)"welcome");
				_delay_ms(2000);
			}
		}
	}
	else /*previously launched */
	{
		LCD_clearScreen();
		LCD_displayOnColRow(0 , 0 , (uint8*)"enter the pass:");
		int i = 0;
		LCD_goToColRow(1 , 0);
		while(KEYPAD_getPressed() != '=')
		{
			LCD_displayCharacter('*');
			password[i] = current_key;
			i++;
		}
		while(!same)
		{
			same = TRUE;
			LCD_clearScreen();
			LCD_displayOnColRow(0 , 0 , (uint8*)"confirm :");
			int i = 0;
			LCD_goToColRow(1 , 0);
			while(KEYPAD_getPressed() != '=')
			{
				LCD_displayCharacter('*');
				if(current_key != password[i])
				{
					same = FALSE;
				}
				i++;
			}
			if(!same)
			{
				LCD_clearScreen();
				LCD_displayOnColRow(0 ,4 ,(uint8*)"Wrong");
				_delay_ms(2000);
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString((uint8*)"welcome");
				_delay_ms(2000);
			}
		}
	}
#endif
	while(TRUE)
	{
		/* Application code*/


	}

}
