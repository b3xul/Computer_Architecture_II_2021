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

extern uint8_t down_0;	/* defined in IRQ_button.c */
extern uint8_t down_1;	/* defined in IRQ_button.c */
extern uint8_t down_2;	/* defined in IRQ_button.c */

extern _Bool acquisizione;	/* defined in sample.c */

#define N 5

unsigned char valore_iniziale;
unsigned int tempo_totale;
unsigned int tempi_variazioni[N];
unsigned char numero_variazioni=0;

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
	uint8_t i;
	/* Debouncing Buttons 25ms*3-> latency 50-75ms */ 
	/* Buttons Actions */
	if(down_2!=0){
		down_2++;			
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			if(down_2==3){
				/* ACTION pressed */
				acquisizione=1;
				for(i=0;i<N;i++)
					tempi_variazioni[i]=0;
				enable_timer(3);
				LED_On_All();
				valore_iniziale=((LPC_GPIO1->FIOPIN & (1<<29)) == 0)?1:0;	//if up is pressed (pin==0) value is 1
				down_2=0;	/* Key2 disabled until monitor mode */
			}
		}
		else{
		
				/* stop RIT until real key2 press */
				disable_RIT();
				reset_RIT();
			/* else RIT still active for polling */
			down_2=0;
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 2 pin selection */
		}
	}
	
	/* Joystick Actions */

	/* UP */
	if(acquisizione){
		if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){
			/* up pressed -> value is 1*/
			if( (valore_iniziale==0 && numero_variazioni%2==0) ||			/* value 0-> even number of variations -> press(value 1) trigger variation */
				  (valore_iniziale==1 && numero_variazioni%2==1)    ){	/* value 1-> odd number of variations -> press(value 1) trigger variation */
				tempi_variazioni[numero_variazioni]=LPC_TIM3->TC;
				numero_variazioni++;
			}
		}
		else{
			/* up not pressed -> value is 0*/
			if( (valore_iniziale==0 && numero_variazioni%2==1) ||			/* value 0-> odd number of variations -> not press(value 0) trigger variation */
				  (valore_iniziale==1 && numero_variazioni%2==0)    ){	/* value 1-> even number of variations -> not press(value 0) trigger variation */
				tempi_variazioni[numero_variazioni]=LPC_TIM3->TC;
				numero_variazioni++;
			}
		}
		if(numero_variazioni==N){
			acquisizione=0;
			tempo_totale=LPC_TIM3->TC;
		}
			
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
