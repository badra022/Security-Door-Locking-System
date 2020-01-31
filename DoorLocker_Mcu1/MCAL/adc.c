 /******************************************************************************
 *
 * Module: adc
 *
 * File Name: adc.c
 *
 * Description: adc driver src file
 *
 * Author: Ahmed Mohamed
 *
 *******************************************************************************/

/*********************************************************************************
 * 									INCLUDES									 *
 *********************************************************************************/
#include"adc.h"
/*********************************************************************************
* 								Global variables								 *
 *********************************************************************************/
/*
 * pointer to void function to hold the address of the callback function
 * */
static void (*volatile ADC_interruptFunc_ptr)(void) = NULL;
/*
 * global variable that holds the final results after conversion
* 		can be accessed in all analog sensors drivers and main application
 */
volatile uint16 current_reading;
/*********************************************************************************
* 								Functions Definition							 *
 *********************************************************************************/
void ADC_init(const ADC_struct * config_ptr)
{
	/* setting initially
	 * 1. ADC0 channel
	 * 2. reference voltage
	 * 3. no left adjust for result
	 */
	ADMUX = (config_ptr->ref)<<6;
	/*
	 * enable adc
	 * */
	SET_BIT(ADCSRA , ADEN);
	/*
	 * setting ADIE with either 0 for polling or 1 for interrupt
	 * */
	SET_VALUE(ADCSRA , ADIE , config_ptr->type);
	/*
	 * setting the prescale value in ADCSRA register
	 * */
	ADCSRA =(ADCSRA & 0xF8) | config_ptr->prescaler;
}

void ADC_readChannel(const ADC_struct * config_ptr,ADC_channel a_channel)
{
	/*
	 * setting the channel that will be converted
	 * */
	ADMUX = (ADMUX & 0xE0) |a_channel;
	/*
	 * start conversion
	 * */
	SET_BIT(ADCSRA , ADSC);
	/*
	 * polling service routine
	 */
	if(config_ptr->type == POLLING)
	{
		/*
		 * wait until conversion at adc module is over
		 */
		while(BIT_IS_CLEAR(ADCSRA , ADIF)){};
		/*
		 * clearing the interrupt module flag
		 */
		SET_BIT(ADCSRA , ADIF);
		/*
		 * storing conversion result in current_reading global variable
		 */
		current_reading = ADC;
		/*
		 * callback function of the hardware sensor conversion for result
		 */
		if(ADC_interruptFunc_ptr != NULL)
			{
				ADC_interruptFunc_ptr();
			}
	}
}
void ADC_setCallBack(void (*a_ptr)(void))
{
	/*
	 * passing the address of the call back function
	 * */
	ADC_interruptFunc_ptr = a_ptr;
}
/*********************************************************************************
* 								Interrupt service routines							 *
 *********************************************************************************/
ISR(ADC_vect)
{
	/*
	 * storing conversion result in current_reading global variable
	 */
	current_reading = ADC;
	if(ADC_interruptFunc_ptr != NULL)
	{
		ADC_interruptFunc_ptr();
	}
}
