 /******************************************************************************
 *
 * Module: Lcd
 *
 * File Name: lcd.h
 *
 * Description: lcd source file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"lcd.h"

/*--------------------------------------FUNCTION DEFINITIONS---------------------------------------------*/
void LCD_init(void)
{
	SET_BIT(LCD_CTRL_DIR , RS);	/* make RS pin o/p pin*/
	SET_BIT(LCD_CTRL_DIR , RW);	/* make RW pin o/p pin*/
	SET_BIT(LCD_CTRL_DIR , E);	/*make E pin o/p pin*/
#ifdef LCD_4_BITS_MODE
#ifdef UPPER_PORT_PINS
	SET_UPPER(LCD_DATA_DIR);	/*make upper(0 1 2 3) pins o/p pins for data out*/
#else
	SET_LOWER(LCD_DATA_DIR);	/*make lower(4 5 6 7) pins o/p pins for data out*/
#endif
	LCD_sendCommand(SWITCH_4_BIT_MODE);
	LCD_sendCommand(TWO_LINE_4_BITS);
#endif
#ifndef LCD_4_BITS_MODE
	SET_UPPER(LCD_DATA_DIR);
	SET_LOWER(LCD_DATA_DIR);				/* make data port o/p port*/
	LCD_sendCommand(TWO_LINE_8_BITS);		/* 2lines + 8 bits mode*/
#endif
	LCD_sendCommand(DISPLAY_ON_CURSOR_OFF);		/* Cursor off */
	LCD_sendCommand(CLEAR_SCREEN);		/* clear screen*/
}
void LCD_sendCommand(uint8 command)
{
	/*function definition*/
	CLEAR_BIT(LCD_CTRL_OUT , RS);	/*for command mode*/
	CLEAR_BIT(LCD_CTRL_OUT , RW);	/*for write mode*/
	_delay_ms(1);					/*for write timing diagram*/
	SET_BIT(LCD_CTRL_OUT , E);		/*to enable the lcd*/
	_delay_ms(1);					/*for write timing diagram*/
	#ifdef LCD_4_BITS_MODE
	#ifdef UPPER_PORT_PINS
	PUT_LOWER_IN_UPPER(LCD_DATA_OUT , command);
	#else
	PUT_LOWER_IN_LOWER(LCD_DATA_OUT , command);
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_OUT , E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_OUT , E);
	_delay_ms(1);
	#ifdef UPPER_PORT_PINS
	PUT_UPPER_IN_UPPER(LCD_DATA_OUT , command);
	#else
	PUT_UPPER_IN_LOWER(LCD_DATA_OUT , command);
	#endif
	#else
	LCD_DATA_OUT = command;			/*out the command variable*/
	#endif
	_delay_ms(1);					/*for write timing diagram*/
	CLEAR_BIT(LCD_CTRL_OUT , E);	/*for write timing diagram*/
	_delay_ms(1);					/*for write timing diagram*/
}

void LCD_displayCharacter(uint8 a_data)
{
	/*function definition*/
	SET_BIT(LCD_CTRL_OUT , RS);	/*for command mode*/
	CLEAR_BIT(LCD_CTRL_OUT , RW);	/*for write mode*/
	_delay_ms(1);					/*for write timing diagram*/
	SET_BIT(LCD_CTRL_OUT , E);		/*to enable the lcd*/
	_delay_ms(1);					/*for write timing diagram*/
	#ifdef LCD_4_BITS_MODE
	#ifdef UPPER_PORT_PINS
	PUT_LOWER_IN_UPPER(LCD_DATA_OUT , a_data);
	#else
	PUT_LOWER_IN_LOWER(LCD_DATA_OUT , a_data);
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_OUT , E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_OUT , E);
	_delay_ms(1);
	#ifdef UPPER_PORT_PINS
	PUT_UPPER_IN_UPPER(LCD_DATA_OUT , a_data);
	#else
	PUT_UPPER_IN_LOWER(LCD_DATA_OUT , a_data);
	#endif
	#else
	LCD_DATA_OUT = a_data;			/*out the command variable*/
	#endif
	_delay_ms(1);					/*for write timing diagram*/
	CLEAR_BIT(LCD_CTRL_OUT , E);	/*for write timing diagram*/
	_delay_ms(1);					/*for write timing diagram*/
}

void LCD_displayString(const uint8 * str)
{
	uint8 count = 0;
	while(str[count] != '\0')
	{
		LCD_displayCharacter(str[count]);
		count++;
	}
}

void LCD_goToColRow(uint8 row , uint8 col)
{
	uint8 address;
	switch(row)
	{
	case 0 :
		address = col;
		break;
	case 1 :
		address = 0x40 + col;
		break;
	case 2 :
		address = 0x10 + col;
		break;
	case 3 :
		address = 0x50 + col;
		break;
	}
	LCD_sendCommand(address | 0x80);
}
void LCD_displayInt(int a_number)
{
	char a_ascii[16];
	itoa(a_number , a_ascii , 10);
	LCD_displayString(a_ascii);
}

void LCD_displayOnColRow(uint8 row , uint8 col , const uint8 * str)
{
	LCD_goToColRow(row , col);
	LCD_displayString(str);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_SCREEN);
}
