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

volatile int down_0=0;
volatile int down_1=0;
volatile int down_2=0;

volatile int e1, e2;
volatile int count=0;


void RIT_IRQHandler (void)
{					
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed */
		; 
	}
	else{
			;
	}
	
	/* button management */
	if(down_0!=0){ 
			down_0++;				
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* KEY0 pressed */
			switch(down_0){
				case 3:				/* */
					init_timer(2,0x09BF3188); /* init timer 2, 6.541s = 0x09BF3188 */
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			if(down_0 >=3){
					reset_timer(2);
					enable_timer(2);
					count=1;
					e1=0;
					e2=0;				
			}
					down_0=0;
					NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
					LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	
	if(down_1!=0){ 
			down_1++;			
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			switch(down_1){
				case 3:				
					if(count)
						e1++;
					break;
				default:
					break;
			}
		}
		else {
			if(down_1>2){
			down_1=0;
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 1 pin selection */

			}
		down_1=0;	
		NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 1 pin selection */
		}	
	}
	if(down_2!=0){ 
			down_2++;			
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			switch(down_2){
				case 3:				
					if(count)
						e2++;
					break;
				default:
					break;
			}
		}
		else{
			if(down_2>2){
				down_2=0;
				NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
			}	
		
		down_2=0;	
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
