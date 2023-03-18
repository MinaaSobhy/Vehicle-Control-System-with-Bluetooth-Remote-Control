
#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

//Define ports
#define STEPmotor_PORTA PORTA_ID
#define STEPmotor_PORTB PORTA_ID
#define STEPmotor_PORTC PORTA_ID
#define STEPmotor_PORTD PORTA_ID

//Define pins
#define STEPmotor_PINA PIN0_ID
#define STEPmotor_PINB PIN1_ID
#define STEPmotor_PINC PIN2_ID
#define STEPmotor_PIND PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Stepper motor:
 * 1. Setup the stepper motor pins directions by use the GPIO driver.
 * 2. Setup the stepper motor pins to be initially LOW to stop the motor.
 */
void stepmotor_init(void);

/*
 * Description :
 * 1. Setup the Direction of the motion of the stepper motor.
 * 2. Setup the angle of the motor by checking any previous values and store the new required value.
 */
void stepmotor_info (uint8 angle , uint8 dirct);
/*
 * Description :
 * storing the values of the current directions to attract the magnet towards it and rotate in
 * ACW direction
 */
void left (uint8 angle);
/*
 * Description :
 * storing the values of the current directions to attract the magnet towards it and rotate in
 * CW direction
 */
void right(uint8 angle);
/*
 * Description :
 * the rotation function to store the values in the port and rotate the motor
 */
void rotate(uint8 angle);


#endif /* STEPMOTOR_H_ */
