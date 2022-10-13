/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Nada Amged
 *
 *******************************************************************************/

#include "avr/io.h"
#include "adc.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/



/* ADC driver should configure to operate using the internal reference voltage 2.56
voltage and prescaler F_CPU/8.*/
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 * Inputs: (const ADC_ConfigType * Config_Ptr) a Pointer to structure has the configuration of the ADC
 */
void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 11 to choose to connect the internal reference voltage 2.56
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */

	ADMUX = ((ADMUX & 0x3F) | ((Config_Ptr -> ref_volt)<< REFS0));
	/*ADMUX =((Config_Ptr -> ref_volt)<< 6));*/


	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) | (Config_Ptr -> prescaler);

}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 * Inputs: (uint8 channel_num) The channel number which the device is connected to.
 */
uint16 ADC_readChannel(uint8 channel_num)
{

	ADMUX = (ADMUX & 0xE0) | (ADMUX | channel_num); /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) then set the required channel*/
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it*/
	return ADC; /* Read the digital value from the data register */
}
