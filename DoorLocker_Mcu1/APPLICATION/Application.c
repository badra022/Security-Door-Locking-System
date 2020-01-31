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
#include"../ECUAL/lcd.h"
#include"../ECUAL/keypad.h"
#include"../MCAL/uart.h"
#include"../MCAL/timer0.h"
/*********************************************************************************
 * 									APPLICATION									 *
 *********************************************************************************/
uint8 input;
uint8 output;
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


void delay_init(void)
{
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
	TIMER0_configType TIMER0_configStruct = {	TIMER0_CTC ,
												TIMER0_NORMAL_OUTPUT ,
												TIMER0_F_CPU_64 ,
												ENABLE ,
												DISABLE ,
												 125 ,
												 0};

	TIMER0_init(&TIMER0_configStruct);
}

void eachSecDelay(void)
{
	g_t0tick--;

	/* you can write a count down counter
	 * that will get executed each 1 second here*/
}
void delay_sec(uint8 ticks)
{
	/******************
	for(uint8 i = 0 ; i< ticks ; i++)
	{
		while(BIT_IS_CLEAR(TIFR , OCF0)){}
		SET_BIT(TIFR , OCF0);
	}
	*******************/
	/* set the number of seconds the timer will count*/
	g_t0tick = ticks;
	/* put the code that decrement the number of seconds counted in the ISR*/
	TIMER0_setCallBackCompareMode(eachSecDelay);

	/* start the timer and initialize the TCNT0 container*/
	TIMER0_start(TIMER0_F_CPU_64);

	GLOBAL_INTERRUPT_ENABLE();

	/* wait until all the seconds in ticks variable are counted(CAN BE INTERRUPTED)*/
	while(g_t0tick){}

	/* stop the timer clock signals */
	TIMER0_stop();

}
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

#define PASSWORD_ADDRESS 	0x10
#define MC2_READY			0x00
#define MC1_READY			0x01
uint8 password[20];
uint16 i;
int main(void)
{
	/*initializaiton code*/
	LCD_init();
	KEYPAD_init();
	delay_init();
	Mcu2_init();
	GLOBAL_INTERRUPT_ENABLE();
	LCD_displayOnColRow(0 , 4 , "welcome");
	_delay_ms(5000);
	//LCD_displayString("hey!");
	LCD_clearScreen();
	//wait until mcu2 checks for existing pass in the address
	while(UART_receiveByte() != MC2_READY){}
	input = UART_receiveByte();
	if(input)
	{
		LCD_displayString("please enter the");
		//LCD_displayOnColRow(1 , 0 , "password: ");
		i=0;
		LCD_goToColRow(1 , 0);
		while(KEYPAD_getPressed() != '=')
		{
			LCD_displayCharacter('*');
			password[i] = current_key;
			i++;
		}
		i=0;

	}
	else
	{
		LCD_displayString("please enter new");
		//LCD_displayOnColRow(1 , 0 , "password: ");
		i=0;
		while(KEYPAD_getPressed() != '=')
		{
			password[i] = current_key;
			i++;
		}
		i=0;
	}

	/*i=0;
	while(UART_receiveByte() != MC2_READY){}
	UART_sendString(password);*/
	while(TRUE)
	{
		/* Application code*/

	}



}
//current task -> test the timer0 module with delay function in another small project
