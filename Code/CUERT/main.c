
#include "main.h"


void main()
{

	//LCD and motors Initializations
	LCD_init();
	stepmotor_init();
	DCmotor_init();

	//Starting timer
	SREG |= (1<<7);
	Timer1_Init();

	//initializing titles on LCD
	LCD_clearScreen();
	LCD_moveCursor(1,0);
	LCD_displayString("Time:  :  :  AM");
	LCD_moveCursor(0,8);
	LCD_displayString("Dir:");
	LCD_moveCursor(0,0);
	LCD_displayString("Spd:   %");

	//Defining variables
	uint8 speed; // store DC motor speed
	uint8 DCdirc;// store DC motor direction
	uint8 angle; // store stepper motor angle
	uint8 stepdirc; // store stepper motor direction
	uint8 hours=00; //store the current hours passed
	uint8 min=00; // store the current minutes passed
	uint8 AM=1; // store the state of the day weather AM or PM
	uint8 input[8]={0}; //store the input data from the user
	uint8 i; // a counter for the loops

	//UART Initialization
	/* 1. size of the character = 8 bits
	 * 2. Disable parity check
	 * 3. Use one stop bit (E)
	 * 4. Choose 9600 bit/sec baud rate
	 */
	UART_ConfigType UART_Configuration = { EIGHT_BIT , DISABLED , ONE_BIT , 9600 };
	UART_init(&UART_Configuration);



	while (1)
	{
		// a loop to display the current time
		if (sec<10)
		{
			LCD_moveCursor(1,12);
			LCD_intgerToString(sec);
		}
		else if (sec == 60)
		{
			sec =0;
			LCD_moveCursor(1,11);
			LCD_intgerToString(00);
			min++;
		}
		else if (sec>60)
		{
			sec -=60;
			LCD_moveCursor(1,11);
			LCD_intgerToString(00);
			min++;
		}
		else
		{
			LCD_moveCursor(1,11);
			LCD_intgerToString(sec);
		}

		if (min<10)
		{
			LCD_moveCursor(1,9);
			LCD_intgerToString(min);
		}
		else if (min == 60)
		{
			min=0;
			LCD_moveCursor(1,8);
			LCD_intgerToString(00);
			hours++;
		}
		else
		{
			LCD_moveCursor(1,8);
			LCD_intgerToString(min);
		}

		if (hours < 10)
		{
			LCD_moveCursor(1,6);
			LCD_intgerToString(hours);
		}
		else if (hours == 12)
		{
			hours = 0;
			LCD_moveCursor(1,5);
			LCD_intgerToString(00);
			if (AM == 1)
			{
				LCD_moveCursor(1,13);
				LCD_displayString("PM");
				AM=0;
			}
			else
			{
				LCD_moveCursor(1,13);
				LCD_displayString("AM");
				AM=1;
			}
		}
		else
		{
			LCD_moveCursor(1,5);
			LCD_intgerToString(hours);
		}


		//check if the user start to write the input
		if (!BIT_IS_CLEAR(UCSRA,RXC))
		{	//if the user started, start to store the values in theinput array
			UART_receiveString(input);
			//setting LCD with new values
			LCD_clearScreen();
			LCD_moveCursor(1,0);
			LCD_displayString("Time:  :  :  AM");
			LCD_moveCursor(0,9);
			LCD_displayString("Dir:");
			LCD_moveCursor(0,0);
			LCD_displayString("Spd:   %");

			//Initializing angle and direction of stepper motor
			//convert the string to numbers to be calculated
			for ( i =4 ; i<6 ; i++ )
			{
				input[i]-=48;
			}
			angle = input[4] * 10  + input[5];
			stepdirc = input [6];


			if (stepdirc == 'L')
			{
				LCD_moveCursor(0,13);
				LCD_intgerToString(-angle);
			}
			else if (stepdirc == 'R')
			{
				LCD_moveCursor(0,13);
				LCD_intgerToString(angle);
			}

			//initializing stepper motor with its values(speed and direction)
			stepmotor_info(angle,stepdirc);

			//Initializing speed and direction of DC motor
			//convert the string to numbers to be calculated
			for ( i =0 ; i<3 ; i++ )
			{
				input[i]-=48;
			}
			speed = input[0] * 100 + input[1] * 10 + input[2];


			LCD_moveCursor(0,4);
			LCD_intgerToString(speed);

			DCdirc= input[3];

			//initializing DC motor with its values(speed and direction)
			DCmotor_info(speed,DCdirc);


		}


	}
}

