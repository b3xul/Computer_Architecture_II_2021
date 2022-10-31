/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int down_KEY2 = 0; //UNCOMMENT IF JOYSTICK IS USED
volatile unsigned char started = 0;
volatile unsigned int VAR = 0;
volatile int result = 0;
extern int search_in_pool (unsigned int VAR);


void RIT_IRQHandler (void)
{					

	if(!started){
		LED_Off_All();
		reset_timer(1);
		init_timer(1, 0x54F8EE0);						/* Timer 1 init -> 3.564 * 25 *10^6 */
		started = 1;
	}
	
	if(down_KEY2!=0){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			down_KEY2++;				
			switch(down_KEY2){
				case 3:
					if(started==2){
						disable_timer(1);
						VAR = LPC_TIM1->TC;
						result = search_in_pool(VAR);
						enable_timer(3);
					}
					else if(started==1){
						enable_timer(1);
						started++;
					}
					break;
				default:
					break;
			}
		}
		else {
			if(down_KEY2>2){
				down_KEY2=0;
				NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
			}
		
		down_KEY2=0;	
		NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
		}
	}

	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
