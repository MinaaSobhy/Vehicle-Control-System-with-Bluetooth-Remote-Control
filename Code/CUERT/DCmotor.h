

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include "common_macros.h"
#include "gpio.h"
#include "pwm_timer0.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

//Define ports
#define DCmotor_PORTA PORTB_ID
#define DCmotor_PORTB PORTB_ID

//Define pins
#define DCmotor_PINA PIN5_ID
#define DCmotor_PINB PIN4_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the DCmotor:
 * 1. Setup the DCmotor pins directions by use the GPIO driver.
 * 2. Setup the DCmotor pins to be initially LOW to stop the motor.
 */
void DCmotor_init(void);


/*
 * Description :
 * 1. Setup the Direction of the motion of the DCmotor.
 * 2. Setup the speed of the motor by calculating number of bits and send it to PWM Function.
 */

void DCmotor_info(uint8 speed,uint8 dirc);


#endif /* DCMOTOR_H_ */
