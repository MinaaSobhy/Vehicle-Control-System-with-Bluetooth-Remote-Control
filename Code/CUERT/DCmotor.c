
#include "DCmotor.h"


/* setting output pins for the motor and set an initializing value for them */
void DCmotor_init(void)
{
	/* configure pins (PB4 and PB5) as output pins */
	GPIO_setupPinDirection(DCmotor_PORTA,DCmotor_PINA, PIN_OUTPUT);
	GPIO_setupPinDirection(DCmotor_PORTB,DCmotor_PINB, PIN_OUTPUT);


	/* Clear the two bits to stop the motor at the beginning */
	GPIO_writePin(DCmotor_PORTA,DCmotor_PINA, LOGIC_LOW);
	GPIO_writePin(DCmotor_PORTB,DCmotor_PINB, LOGIC_LOW);
}

/* setting the speed and the direction of the motor according to the input */
void DCmotor_info(uint8 speed,uint8 dirc)
{
	if (speed > 100 || speed < 0)
	{
		//don't do anything as a safety for the motor if the input was wrong
	}
	else
	{	/*rotate the motor ACW if the input is 'F'
	 	  by setting mode: PINA:High , PINB:LOW
	 	  or rotate CW if the input is 'B'
	 	  by setting mode: PINA:LOW , PINB:HIGH*/
		if (dirc == 'F')
		{
			GPIO_writePin(DCmotor_PORTA,DCmotor_PINA, LOGIC_HIGH);
			GPIO_writePin(DCmotor_PORTB,DCmotor_PINB, LOGIC_LOW);
		}
		else if (dirc=='B')
		{
			GPIO_writePin(DCmotor_PORTA,DCmotor_PINA, LOGIC_LOW);
			GPIO_writePin(DCmotor_PORTB,DCmotor_PINB, LOGIC_HIGH);
		}

		/* convert the speed form percentage to bits according to the register size(256)*/
		uint8 speed_bit = speed * (256/100);
		/* calling PWM function to generate the speed required by the motor */
		PWM_Timer0_Start(speed_bit);
	}

}
