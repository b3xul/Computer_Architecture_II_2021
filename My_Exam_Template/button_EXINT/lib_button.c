/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_button.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions to init KEY1, KEY2 buttons ( no INT0, initialized in game.c )
** Correlated files:    button.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "lpc17xx.h"
#include "button_EXINT/button.h"

void BUTTON_init(void) {

  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* INT0 -> PORT2.10 defined as input  */

  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* Key1 -> PORT2.11 defined as input  */
  
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* Key2 ->PORT2.12 defined as input   */

  LPC_SC->EXTMODE = 0x7;	/* 0x1: INT0, 0x2:Key1, 0x4:Key2 */
	
	/* priority, the lower the higher     */
  NVIC_SetPriority(EINT2_IRQn, 3);
	NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT1_IRQn, 2);			 
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT0_IRQn, 1);			 
  NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
					 
}
