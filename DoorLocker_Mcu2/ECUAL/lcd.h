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
#ifndef LCD_H_
#define LCD_H_
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"../COMPLEX DRIVERS/micro_config.h"
#include"../COMPLEX DRIVERS/common_macros.h"
#include"../COMPLEX DRIVERS/std_types.h"
/*******************************************STATIC CONFIGURATIONS***************************************/
#define LCD_BITS_MODE				8			/* 4 BIT MODE OR 8-BIT MODE*/
#if (LCD_BITS_MODE==4)
#define UPPER_PORT_PINS							/* 0 1 2 3 UPPER PINS*/
#endif
#define RS 							2
#define RW  						1
#define E   						0
#define LCD_DATA_OUT 				PORTA
#define LCD_DATA_IN  				PINA
#define LCD_DATA_DIR 				DDRA
#define LCD_CTRL_OUT 				PORTB
#define LCD_CTRL_IN  				PINB
#define LCD_CTRL_DIR 				DDRB
/*****************************NON_MODIFIABLE STATIC CONFIG**********************************************/
#if (LCD_BITS_MODE == 4)
#define LCD_4_BITS_MODE
#endif
/*********************************LCD COMMANDS*********************************************************/
#define SWITCH_4_BIT_MODE			0x02
#define DISPLAY_OFF_CURSOR_OFF 		0x08
#define DISPLAY_ON_CURSOR_ON   		0x0E
#define DISPLAY_ON_CURSOR_OFF   	0x0C
#define DISPLAY_ON_CURSOR_BLINKING  0x0F
#define SHIFT_LEFT					0x18
#define SHIFT_RIGHT					0x1C
#define TWO_LINE_8_BITS 			0x38
#define TWO_LINE_4_BITS 			0x28
#define CURSOR_OFF      			0x0c
#define CLEAR_SCREEN    			0x01
/*----------------------------FUNCTIONS PROTOTYPES--------------------------------------------------------*/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_init(void);
void LCD_displayString(const uint8 * str);
void LCD_displayInt(int a_number);
void LCD_displayOnColRow(uint8 row , uint8 col , const uint8 * str);
void LCD_goToColRow(uint8 row , uint8 col);
void LCD_clearScreen(void);
#endif /* LCD_H_ */
