#include "stepmotor.h"

/*setting up global variables to keep their values after leaving the function
  as it will be needed to return to initial state to set up a new angle */
uint8 anglecount =0;
uint8 motor_steps[4];

/* setting output pins for the motor and set an initializing value for them */
void stepmotor_init(void)
{
	// Configure first 4 pins in PORTA as output pins
	GPIO_setupPinDirection(STEPmotor_PORTA,STEPmotor_PINA, PIN_OUTPUT);
	GPIO_setupPinDirection(STEPmotor_PORTB,STEPmotor_PINB, PIN_OUTPUT);
	GPIO_setupPinDirection(STEPmotor_PORTC,STEPmotor_PINC, PIN_OUTPUT);
	GPIO_setupPinDirection(STEPmotor_PORTD,STEPmotor_PIND, PIN_OUTPUT);

	// Clear first four bits in PORTA to stop the motor at the beginning */
	GPIO_writePin(STEPmotor_PORTA,STEPmotor_PINA, LOGIC_LOW);
	GPIO_writePin(STEPmotor_PORTB,STEPmotor_PINB, LOGIC_LOW);
	GPIO_writePin(STEPmotor_PORTC,STEPmotor_PINC, LOGIC_LOW);
	GPIO_writePin(STEPmotor_PORTD,STEPmotor_PIND, LOGIC_LOW);
}

/* setting the angle and the direction of the motor according to the input */
void stepmotor_info (uint8 angle , uint8 dirct)
{
	if ( angle < 0 || angle > 45 || (dirct != 'R' && dirct != 'L'))
	{
		//don't do anything as a safety for the motor if the input was wrong
	}
	else
	{
		uint8 prevangle; // variable to store previous angle

		/*check if the angle of the motor have been changed previously
		  as the angle count will store its value */
		if (anglecount != 0)
			{
			prevangle = anglecount;
			anglecount =0;
			/*know the previous angle direction from the value store in the array
			and rotate in the opposite direction to  reach angle 0 */
			if (motor_steps[0] == 12)
				left(prevangle);
			else
				right(prevangle);
			}

		anglecount =0;
		/* if there is no previous actions or after resting motor to angle zero
		move to the required angle*/
		if (dirct == 'R')
			right(angle);
		else if (dirct == 'L')
			left(angle);

	}
}

//storing the values of the current directions to attract the magnet towards it and rotate in ACW direction
void left (uint8 angle)
{
	motor_steps[0]=3;
	motor_steps[1]=6;
	motor_steps[2]=12;
	motor_steps[3]=9;
	rotate(angle);
}

//storing the values of the current directions to attract the magnet towards it and rotate in CW direction
void right(uint8 angle)
{
	motor_steps[0]=12;
	motor_steps[1]=6;
	motor_steps[2]=3;
	motor_steps[3]=9;
	rotate(angle);
}

//the rotation function to store the values in the port and rotate the motor
void rotate(uint8 angle)
{
	uint8 counter =1; // as both ACW and CW have the same value in the array to avoid any errors

	//start the motion
	PORTA = (motor_steps[0] & 0x0F) | (PORTA & 0xF0);
	_delay_ms(30);

	/*exit the loop when the angel count == angle required which indicate reaching the
	required angle */
	while (anglecount != angle)
	{
		PORTA = (motor_steps[counter] & 0x0F) | (PORTA & 0xF0);
		_delay_ms(30);
		counter++;
		if(counter == 4)
		{
			//start from the beginning after finish the full motor rotation.
			counter = 0;
		}
		anglecount++;
	}

	//to solve an error we have to add another step
	PORTA = (motor_steps[counter] & 0x0F) | (PORTA & 0xF0);
}


