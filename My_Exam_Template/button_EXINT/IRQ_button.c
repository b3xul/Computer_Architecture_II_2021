/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_button.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions to manage EINT0, EINT1, EINT2 interrupts
** Correlated files:    button.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "lpc17xx.h"
#include "button_EXINT/button.h"

#include "RIT/RIT.h"

volatile uint8_t down_0=0;
volatile uint8_t down_1=0;
volatile uint8_t down_2=0;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	down_0=1;
	
	enable_RIT();										/* enable RIT to count 25ms				 */
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable INT0 interrupts			 	 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection 	 */
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}

void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	down_1=1;
	
	enable_RIT();										/* enable RIT to count 25ms				 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable KEY1 interrupts			 	 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection 	 */
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	down_2=1;
	
	enable_RIT();										/* enable RIT to count 25ms				 */
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable KEY2 interrupts			 	 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* GPIO pin selection 	 */
	
	LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */
}


