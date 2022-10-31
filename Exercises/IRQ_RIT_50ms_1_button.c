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

extern enum Button pressed_button;	/* defined in IRQ_button.c */

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler:
**									Manages debouncing and action for INT0 (START), KEY1 (ROTATE), KEY2 (RUN)
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
/* RIT : Debouncing and action for INT0, KEY1 , KEY2 */
void RIT_IRQHandler (void)
{
	/* Counting variables */
	static uint8_t down0=0;
	static uint8_t down1=0;
	static uint8_t down2=0;
	
	static uint8_t select=0;
	static uint8_t down=0;
	static uint8_t left=0;
	static uint8_t right=0;
	static uint8_t up=0;
	
	/* Buttons Actions */
	switch(pressed_button){
		case int0:
			if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* button pressed */
				down0=1;
			}
			else {	/* button released */
				if( down0==1 ){
					/* ACTION */
					down0=0;
				}
				/* if not used for polling */
				disable_RIT();
				reset_RIT();
				/* Reenable button  */
				NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
				
			}
			break;
			
		case key1:	
			
			if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
				down1=1;
			}
			else {	/* button released */
				if( down1==1 ){
					/* ACTION */
					down1=0;
				}
				/* if not used for polling */
				disable_RIT();
				reset_RIT();
				/* Reenable button  */
				NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
			}
			break;
			
		case key2:
			
			if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
				down2++;
				if( down2==1  ){
					/* ACTION */
				}
				else if( down2 == 20 ){	/* button still pressed after 50ms*20=1s */
					/* ACTION2 */
					down2=0;	/* Start counting again from the start without stopping */
				}
			}
			else {	/* button released */
				down2=0;			
				/* if not used for polling */
				disable_RIT();
				reset_RIT();
				/* Reenable button  */
				NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
			}
				
			break;
		default:
			break;
	}
	
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */

	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
