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

  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */

  LPC_SC->EXTMODE = 0x4;	
														
  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT2_IRQn, 2);				 /* priority, the lower the higher     */

}
