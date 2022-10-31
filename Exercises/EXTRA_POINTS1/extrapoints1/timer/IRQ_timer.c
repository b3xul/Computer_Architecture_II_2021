/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions to manage T0, T1, T2, T3 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer/timer.h"

#include "led/led.h"
#include "RIT/RIT.h"
#include "labyrinth.h"

extern Robot r;	/* defined in labyrinth.c							*/
extern _Bool win;	/* defined in IRQ_RIT.c							*/
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer 0 interrupt handler
**									Manages Direction leds
**									0-MR0-MR1 -> led off-led on 8Hz
**									0-MR1-MR2 -> led off-led on 4Hz
**									0-MR2-MR3 -> led off-led on 2Hz
**									The advantage of this approach is that the even if the timer would stop for changing a 4Hz led for example,
**									it reads the value of direction and distance at that moment and reacts immediatly to display the new led,
**									instead of stopping entirely the timer to start a new one.
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

	/* TIMER0 : Direction LEDS timing */
void TIMER0_IRQHandler (void)
{
	switch( LPC_TIM0->IR ){
		case 1:	/* MR0 interrupt (8Hz) distance=0 */
			if( r.distance == 0 ){
				LED_On((uint8_t) r.dir + 4);
			}
			LPC_TIM0->IR = 1;			/* clear interrupt flag */
			break;
			
		case 2: /* MR1 interrupt (4Hz) distance=1,2 */
			if( r.distance == 0 ){
				LED_Off((uint8_t) r.dir + 4);
				reset_timer(0);
			}
			else if ( r.distance == 1 || r.distance == 2 ){
				LED_On((uint8_t) r.dir + 4);
			}
			LPC_TIM0->IR = 2;			/* clear interrupt flag */
			break;
			
		case 4: /* MR2 interrupt (2Hz) distance=3,4,5 */
			if( r.distance == 1 || r.distance == 2 ){
				LED_Off((uint8_t) r.dir + 4);
				reset_timer(0);
			}
			else if ( r.distance == 3 || r.distance == 4 || r.distance == 5 ){
				LED_On((uint8_t) r.dir + 4);
			}
			LPC_TIM0->IR = 4;			/* clear interrupt flag */
			break;
			
		case 8: /* MR3 interrupt */
			if ( r.distance == 3 || r.distance == 4 || r.distance == 5 ){
				LED_Off((uint8_t) r.dir + 4);
			}
			reset_timer(0);
			LPC_TIM0->IR = 8;			/* clear interrupt flag */
		
		default:
			break;
	}
	
  
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer 1 interrupt handler
**									Manages Running led
**									0-MR0-MR1 -> led off-led on 5Hz
**									0-MR2-MR3 -> led off-led on 1Hz
** parameters:			None
** Returned value:		None
**
******************************************************************************/

/* TIMER1 : Debouncing and action for KEY2 (RUN) */
void TIMER1_IRQHandler (void)
{
	switch( LPC_TIM1->IR ){
		case 1:	/* MR0 interrupt (5Hz) distance=0 */
			if( r.distance == 0 && win==0 )
				LED_On(2);	/* LD6 Running led */
			
			LPC_TIM1->IR = 1;			/* clear interrupt flag */
			break;
		
		case 2: /* MR1 interrupt */
			if( r.distance == 0 && win==0 ){
				LED_Off(2);
				reset_timer(1);
			}
			
			LPC_TIM1->IR = 2;			/* clear interrupt flag */
			break;
			
		case 4:	/* MR2 interrupt (1Hz) distance!=0 */
			if ( win == 0 )
				LED_On(2);	/* running */
			else
				LED_Out(255);	/* turn on all leds */
			
			LPC_TIM1->IR = 4;			/* clear interrupt flag */
			break;
		
		case 8: /* MR3 interrupt */
			
			if( win == 0 )
				LED_Off(2);
			else
				LED_Out(0); /* turn off all leds */
			
			reset_timer(1);

			LPC_TIM1->IR = 8;			/* clear interrupt flag */
			break;
		
		default:
			break;
	}
  return;
}


/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer 2 interrupt handler
** parameters:			None
** Returned value:		None
**
******************************************************************************/
/* TIMER2 : Running LED timing */
void TIMER2_IRQHandler (void)
{
	LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)
{
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
