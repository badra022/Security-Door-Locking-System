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
#ifndef EXTERNAL_INT_H_
#define EXTERNAL_INT_H_
/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"../COMPLEX DRIVERS/micro_config.h"
#include"../COMPLEX DRIVERS/common_macros.h"
#include"../COMPLEX DRIVERS/std_types.h"
/*********************************************************************************
* 								Types Declarations							 *
 *********************************************************************************/
typedef enum
{
	INT0_LOW , INT0_TOGGLE , INT0_FALLING , INT0_RAISING ,
}Int0_ctrl;

typedef enum
{
	INT1_LOW , INT1_TOGGLE , INT1_FALLING , INT1_RAISING ,
}Int1_ctrl;

typedef enum
{
	INT2_FALLING , INT2_RAISING ,
}Int2_ctrl;
typedef enum
{
	PULLDOWN , PULLUP ,
}Input_state;
/*********************************************************************************
* 								Function Declarations							 *
 *********************************************************************************/
void INT0_init(Int0_ctrl mode , Input_state state);
void INT1_init(Int1_ctrl mode , Input_state state);
void INT2_init(Int2_ctrl mode , Input_state state);
void INT0_setCallBack(void (*a_ptr)(void));
void INT1_setCallBack(void (*a_ptr)(void));
void INT2_setCallBack(void (*a_ptr)(void));

#endif /* EXTERNAL_INT_H_ */
