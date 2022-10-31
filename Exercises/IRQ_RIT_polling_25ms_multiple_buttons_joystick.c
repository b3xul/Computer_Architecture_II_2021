/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT/RIT.h"

#include "button_EXINT/button.h"
#include "led/led.h"
#include "timer/timer.h"

extern uint8_t down_0;
extern uint8_t down_1;
extern uint8_t down_2;

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler:
**									Manages debouncing and action for INT0, KEY1 , KEY2
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
/* RIT : Debouncing and action for INT0 , KEY1 , KEY2*/
void RIT_IRQHandler (void)
{					
	static uint8_t select=0;
	static uint8_t down=0;
	static uint8_t left=0;
	static uint8_t right=0;
	static uint8_t up=0;
	
	/* Debouncing Buttons 25ms*3-> latency 50-75ms */ 
	/* Buttons Actions */
	if(down_0!=0){ 
		down_0++;				
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* KEY0 pressed */
			if(down_0==3){
				/* ACTION pressed */
				down_0=0;
			}
		}
		else {	/* button released */
			if(down_0 >=3){
					/* ACTION Released*/
			}
			down_0=0;
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	
	if(down_1!=0){ 
		down_1++;			
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			if(down_1==3){
				/* ACTION pressed */
				down_1=0;
			}
		}
		else {
			if(down_1>=3){
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
			if(down_2==3){
				/* ACTION pressed */
				down_2=0;
			}
		}
		else{
			if(down_2>=3){
				down_2=0;
				NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
			}
		
			down_2=0;	
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
		}
	}
	
	/* Joystick Actions */
	/* SELECT */
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
		/* Pressed */
		select=1;
	}
	else{
		/* Released */
		if( select == 1){
			/* ACTION Release */
		}
		select=0;
	}
	
	/* DOWN */
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){
		/* Pressed */
		down++;
		if( down == 1 ){
			/* ACTION 1 Press */
		}
		else if ( down == 20 ){
			/* ACTION Continued Press */
			down=0;
		}
	}
	else{
		/* Released */
		down=0;
	}
	
	/* LEFT*/
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
		/* Pressed */
		left=1;
	}
	else{
		/* Released */
		/* ACTION Release */
		left=0;
	}
	
	/* RIGHT */
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
		/* Pressed */
		right=1;
	}
	else{
		/* Released */
		/* ACTION Release */
		right=0;
	}
	
	/* UP */
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){
		up=1;
	}
	else{
		/* Released */
		/* ACTION Release */
		up=0;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
