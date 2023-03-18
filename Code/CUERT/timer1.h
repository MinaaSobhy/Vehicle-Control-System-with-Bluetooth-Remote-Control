

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"

//to use the variable (sec) in the main function
extern uint8 sec;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the timer:
 * 1. Set timer1 initial count to zero
 * 2. Set the Compare value to 15625.
 * 3. Enable Timer1 Compare A Interrupt
 * 4. Configure timer control register TCCR1A
 * 5. Configure timer control register TCCR1B
 */
void Timer1_Init(void);

#endif /* TIMER1_H_ */
