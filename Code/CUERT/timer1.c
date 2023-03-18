#include "timer1.h"


uint8 sec=00;


ISR(TIMER1_COMPA_vect)
{
	//increment the value of the variable sec each time the timer fire the ISR
	sec++;

}

void Timer1_Init(void)
{
	TCNT1 = 0;		/* Set timer1 initial count to zero */

	OCR1A = 15625;    /* Set the Compare value to 15625 ((1MHz/64 = 15625 ) represent the number of ticks in one second */

	TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=0 (Non-PWM)
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A = (1<<FOC1A);

	/* Configure timer control register TCCR1B
	 * 1. Non PWM mode FOC =0
	 * 2. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 3. Prescaler = F_CPU/64 CS10=1 CS11=1 CS12=0
	 */
	TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10);
}






