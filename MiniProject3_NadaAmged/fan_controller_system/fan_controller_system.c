/*
 * fan_controller_system.c
 *
 *  Created on: Oct 8, 2022
 *      Author: Nada Amgad
 */
#include "std_types.h"
#include "dc_motor.h"
#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"


int main(void){

	uint8 temp;
	ADC_ConfigType adc_config = {INTERNAL , F_CPU_8};
	ADC_init(&adc_config); /* initialize ADC driver */
	LCD_init(); /* initialize LCD driver */
	DcMotor_Init();
	/* Display this string "Temp =   C" only once on LCD at the first row */
	LCD_moveCursor(1,0);
	LCD_displayString("Temp =     C");

	while(1)
	{

		temp = LM35_getTemperature();
		LCD_moveCursor(0,0);
		if(temp < 30){
			LCD_displayString("FAN is OFF");
			DcMotor_Rotate(STOP, 0);
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if((temp >= 30) && (temp < 60)){
			LCD_displayString("FAN is ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(CLOCKWISE, 25);
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if((temp >= 60) && (temp < 90)){
			LCD_displayString("FAN is ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(CLOCKWISE, 50);
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if (temp >= 90 && (temp < 120)){
			LCD_displayString("FAN is ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(CLOCKWISE, 75);
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if(temp >= 120){
			LCD_displayString("FAN is ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(CLOCKWISE, 100);
			LCD_moveCursor(1,7);
			LCD_intgerToString(temp);

		}
	}
	return 0;
}
