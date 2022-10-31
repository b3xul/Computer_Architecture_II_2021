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
		case 1:	/* MR0 interrupt */
			/* ACTION */
			LPC_TIM0->IR = 1;			/* clear interrupt flag */
			break;
			
		case 2: /* MR1 interrupt */
			/* ACTION */
			LPC_TIM0->IR = 2;			/* clear interrupt flag */
			break;
			
		case 4: /* MR2 interrupt (2Hz) distance=3,4,5 */
			/* ACTION */
			LPC_TIM0->IR = 4;			/* clear interrupt flag */
			break;
			
		case 8: /* MR3 interrupt */
			/* ACTION */
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
		case 1:	/* MR0 interrupt */
			/* ACTION */
		
			LPC_TIM1->IR = 1;			/* clear interrupt flag */
			break;
		
		case 2: /* MR1 interrupt */
			/* ACTION */
			
			LPC_TIM1->IR = 2;			/* clear interrupt flag */
			break;
			
		case 4:	/* MR2 interrupt (1Hz) distance!=0 */
			/* ACTION */
		
			LPC_TIM1->IR = 4;			/* clear interrupt flag */
			break;
		
		case 8: /* MR3 interrupt */
			/* ACTION */
		
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
	switch( LPC_TIM2->IR ){
		case 1:	/* MR0 interrupt */
			/* ACTION */
		
			LPC_TIM2->IR = 1;			/* clear interrupt flag */
			break;
		
		case 2: /* MR1 interrupt */
			/* ACTION */
			
			LPC_TIM2->IR = 2;			/* clear interrupt flag */
			break;
			
		case 4:	/* MR2 interrupt (1Hz) distance!=0 */
			/* ACTION */
		
			LPC_TIM2->IR = 4;			/* clear interrupt flag */
			break;
		
		case 8: /* MR3 interrupt */
			/* ACTION */
		
			LPC_TIM2->IR = 8;			/* clear interrupt flag */
			break;
		
		default:
			break;
	}
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
	static _Bool blink=0;
	switch( LPC_TIM3->IR ){
		case 1:	/* MR0 interrupt */
			/* ACTION */
			if(!blink){
				LED_On(0);	//LD11
				blink=1;
			}
			else if(blink){
				LED_Off(0);
				blink=0;
			}
			LPC_TIM3->IR = 1;			/* clear interrupt flag */
			break;
		
		case 2: /* MR1 interrupt */
			/* ACTION */
			
			LPC_TIM3->IR = 2;			/* clear interrupt flag */
			break;
			
		case 4:	/* MR2 interrupt (1Hz) distance!=0 */
			/* ACTION */
		
			LPC_TIM3->IR = 4;			/* clear interrupt flag */
			break;
		
		case 8: /* MR3 interrupt */
			/* ACTION */
		
			LPC_TIM3->IR = 8;			/* clear interrupt flag */
			break;
		
		default:
			break;
	}
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
