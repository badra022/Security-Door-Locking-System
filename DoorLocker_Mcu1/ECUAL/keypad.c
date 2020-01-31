/*
 * keypad.c
 *
 *  Created on: Dec 27, 2019
 *      Author: badra069
 */
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"keypad.h"
uint8 current_key;
/*************************************PRIVATE FUNCTIONS DECLARATION**************************************/
#if(N_COL == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_number);
#elif(N_COL == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_number);
#endif
void KEYPAD_init(void)
{
	CLEAR_UPPER(KEYPAD_PORT_DIR);	/*SET 0 1 2 3 PINS I/P PINS*/
	SET_UPPER(KEYPAD_PORT_OUT);		/*MAKE THEM PULLUPS*/
	SET_LOWER(KEYPAD_PORT_DIR);		/*make pins 4 5 6 7 o/p pins*/
	CLEAR_LOWER(KEYPAD_PORT_OUT);	/*out 0000 in pins 4 5 6 7*/
}
uint8 KEYPAD_getPressed(void)
{
	uint8 row , col;		/*to hold the current location in the keypad*/
	while(TRUE)
	{		/*looping till entering the key*/
		for(col = 0 ; col < N_COL ; col++)
		{
			KEYPAD_PORT_DIR = 1 << (col + N_ROW);
			KEYPAD_PORT_OUT = (!(1 << (col + N_ROW)));
			/*test the column with outing 0 in it and reading rows*/
			for(row = 0 ; row < N_ROW ; row++)
			{
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
				{
					_delay_ms(50);		/* for debouncing */
					if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
					{
						while(BIT_IS_CLEAR(KEYPAD_PORT_IN,row)){};
						/*waiting for the user to move his hand from the button*/
						#if(N_COL == 3)
						current_key = KEYPAD_4x3_adjustKeyNumber(row*N_COL + col + 1);
						return current_key;
						/*call the local function that return the key*/
						#elif(N_COL == 4)
						current_key = KEYPAD_4x4_adjustKeyNumber(row*N_COL + col + 1);
						return current_key;
						/*call the local function that return the key*/
						#endif
					}
				}
			}
		}
	}
}
#if(N_COL == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_number)
{
	switch(a_number)
	{
	case 1 : return '1';
				break;
	case 2 : return '2';
				break;
	case 3 : return '3';
				break;
	case 4 : return '4';
				break;
	case 5 : return '5';
				break;
	case 6 : return '6';
				break;
	case 7 : return '7';
				break;
	case 8 : return '8';
				break;
	case 9 : return '9';
				break;
	case 10: return '*';
				break;
	case 11: return '0';
				break;
	case 12: return '#';
				break;
	}
}
#elif(N_COL == 4)
uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_number)
{
	switch(a_number)
	{
	case 1 : return '7';
				break;
	case 2 : return '8';
				break;
	case 3 : return '9';
				break;
	case 4 : return '/';
				break;
	case 5 : return '4';
				break;
	case 6 : return '5';
				break;
	case 7 : return '6';
				break;
	case 8 : return 'x';
				break;
	case 9 : return '1';
				break;
	case 10: return '2';
				break;
	case 11: return '3';
				break;
	case 12: return '-';
				break;
	case 13: return 'c';
				break;
	case 14: return '0';
				break;
	case 15: return '=';
				break;
	case 16: return '+';
				break;
	}
	return '\0';
}
#endif
