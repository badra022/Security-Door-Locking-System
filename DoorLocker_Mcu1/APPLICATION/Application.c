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
#define NEW_PASSWORD		0x65
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
uint8 default_password[20] = "444444";
uint8 same = FALSE;
uint16 i;
uint8 input;
uint8 output;
uint8 DELAY_DONE;
uint8 cnt = 0;
uint8 flag = TRUE;
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

	/*
	LCD_displayOnColRow(0 , 4 , (uint8*)"welcome");
	_delay_ms(3000);
	LCD_clearScreen();
	 */
	UART_clearPort();
	//for MC1 receive and MC2 transmit
	UART_sendByte(MC1_READY);
	UART_receiveString(password);
	_delay_ms(100);
	LCD_displayString(password);

	UART_clearPort();

	for(int j = 0 ; j<20 ; j++)
	{
		if(password[j] != default_password[j])
		{
			flag = FALSE;
		}
	}
	_delay_ms(1000);
	if(flag) /*new launch*/
	{
		newpass : /*label*/
		same = FALSE;
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
		while(!same && cnt < 4)
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
				LCD_displayOnColRow(0 ,0 ,(uint8*)"Wrong password!");
				cnt++;
				_delay_ms(2000);
			}
			else
			{
				//while(UART_receiveByte() != MC2_READY){}
				UART_sendByte(NEW_PASSWORD);
				UART_sendString(password);
				//_delay_ms(5);
				UART_clearPort();
				LCD_clearScreen();
				LCD_displayString((uint8*)"success!");
				cnt = 0;
				_delay_ms(2000);
			}
		}
		if(cnt == 4)
		{
			LCD_clearScreen();
			LCD_displayOnColRow( 0 , 5 , (uint8*)"ALARM");
			SET_BIT(DDRD , 6);
			SET_BIT(PORTD , 6);
			int g = 12;
			while(g--)
			{
				_delay_ms(100);
			}
			CLEAR_BIT(PORTD , 6);
		}
	}
	else /*previously launched */
	{
		cnt = 0;
		while(!same && cnt < 4)
		{
			same = TRUE;
			LCD_clearScreen();
			LCD_displayOnColRow(0 , 0 , (uint8*)"enter the pass:");
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
				cnt++;
				LCD_clearScreen();
				LCD_displayOnColRow(0 ,0 ,(uint8*)"Wrong password!");
				_delay_ms(2000);
			}
			else
			{
				cnt = 0;
				LCD_clearScreen();
				LCD_displayString((uint8*)"welcome");
				_delay_ms(2000);
			}
		}
		if(cnt == 4)
		{
			LCD_clearScreen();
			LCD_displayOnColRow( 0 , 5 , (uint8*)"ALARM");
			SET_BIT(DDRD , 6);
			SET_BIT(PORTD , 6);
			int g = 12;
			while(g--)
			{
				_delay_ms(100);
			}
			CLEAR_BIT(PORTD , 6);
			goto newpass;
		}
	}
	while(TRUE)
	{

		/* Application code*/
		UART_clearPort();
		LCD_clearScreen();
		LCD_displayOnColRow(0 , 0 ,(uint8*)"+ : open door");
		LCD_displayOnColRow(1 , 0 ,(uint8*)"- : change pass");
		same = FALSE;
		cnt = 0;
		if(KEYPAD_getPressed() == '+')
		{

			while(!same && cnt < 4)
			{
				cnt = 0;
				same = TRUE;
				LCD_clearScreen();
				LCD_displayOnColRow(0 , 0 , (uint8*)"enter the pass:");
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
					cnt++;
					LCD_clearScreen();
					LCD_displayOnColRow(0 ,0 ,(uint8*)"Wrong password!");
					_delay_ms(2000);
				}
				else
				{
					cnt = 0;
					LCD_clearScreen();
					LCD_displayString((uint8*)"Correct");
					_delay_ms(2000);
				}
			}
			if(cnt == 4)
			{
				LCD_clearScreen();
				LCD_displayOnColRow( 0 , 5 , (uint8*)"ALARM");
				SET_BIT(DDRD , 6);
				SET_BIT(PORTD , 6);
				int g = 12;
				while(g--)
				{
					_delay_ms(100);
				}
				CLEAR_BIT(PORTD , 6);
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString((uint8*)"Opening");
				/* inform mc2 to move the motor here for 60 seconds */
				while(UART_receiveByte() != MC2_READY){}
				UART_sendByte(TRUE);
				//_delay_ms(5);
				UART_clearPort();
				/* any protocol can be shown in lcd or any thing in the HMI here */

			}
		}
		else if(current_key == '-')
		{
			cnt = 0;
			while(!same && cnt < 4)
			{
				same = TRUE;
				LCD_clearScreen();
				LCD_displayOnColRow(0 , 0 , (uint8*)"enter the pass:");
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
					cnt++;
					LCD_clearScreen();
					LCD_displayOnColRow(0 ,0 ,(uint8*)"Wrong password!");
					_delay_ms(2000);
				}
				else
				{
					cnt = 0;
					LCD_clearScreen();
					LCD_displayString((uint8*)"Correct");
					_delay_ms(2000);
				}
			}
			/******************************************/
			if(cnt == 4)
			{
				LCD_clearScreen();
				LCD_displayOnColRow( 0 , 5 , (uint8*)"ALARM");
				SET_BIT(DDRD , 6);
				SET_BIT(PORTD , 6);
				int g = 12;
				while(g--)
				{
					_delay_ms(100);
				}
				CLEAR_BIT(PORTD , 6);
			}
			else
			{
				same = FALSE;
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
				while(!same && cnt < 4)
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
						LCD_displayOnColRow(0 ,4 ,(uint8*)"Wrong password!");
						cnt++;
						_delay_ms(2000);
					}
					else
					{
						//while(UART_receiveByte() != MC2_READY){}
						UART_sendByte(NEW_PASSWORD);
						UART_sendString(password);
						//_delay_ms(5);
						UART_clearPort();
						LCD_clearScreen();
						LCD_displayString((uint8*)"success!");
						cnt = 0;
						_delay_ms(2000);
					}
				}
				if(cnt == 4)
				{
					LCD_clearScreen();
					LCD_displayOnColRow( 0 , 5 , (uint8*)"ALARM");
					SET_BIT(DDRD , 6);
					SET_BIT(PORTD , 6);
					int g = 12;
					while(g--)
					{
						_delay_ms(100);
					}
					CLEAR_BIT(PORTD , 6);
					goto newpass;
				}
			}
		}
	}
}
