#include "button.h"
#include "lpc17xx.h"
#include "../RIT/RIT.h"	

extern int down_KEY2; //UNCOMMENT only if multiple buttons or joystick

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
//	if(LPC_RIT->RICTRL != (LPC_RIT->RICTRL | (1<<3))){
//		enable_RIT();
//	}
	//down_INT0=1;											//UNCOMMENT ONLY IF MULTPLE BUTTONS OR JOYSTICK
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
//	if(LPC_RIT->RICTRL != (LPC_RIT->RICTRL | (1<<3))){
//		enable_RIT();
//	}
	//down_KEY1=1;
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	down_KEY2=1;
	NVIC_DisableIRQ(EINT2_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 24);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


