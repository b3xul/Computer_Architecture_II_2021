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

extern uint8_t down_1;	/* defined in IRQ_button.c */

#define N 4

extern unsigned char get_and_sort(unsigned char* VETT, int VAL, int n); /* defined in ASM_function.s */

unsigned char VAL;
unsigned char VETT[N]={0};
int my_index=0;

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
	int timer_counter;
	static _Bool started=0;
	static _Bool blink=0;
	static uint8_t blink_counter=0;
	
	/* Debouncing Buttons 25ms*3-> latency 50-75ms */ 
	/* Buttons Actions */
	
	if(down_1!=0){
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			down_1++;
		}
		else {
			if(down_1>=3){
				if(started==0){
					started=1;
					blink=0;
					blink_counter=0;
					for(my_index=0; my_index<N; my_index++){
						VETT[my_index]=0;
					}
					my_index=0;
				}
				/* ACTION released */
				else{
					disable_timer(1);
					timer_counter=LPC_TIM1->TC;
					enable_timer(1);
					VAL=get_and_sort(VETT, timer_counter, N);
					my_index++;
					LED_Out(my_index);
				}
			}
			down_1=0;	
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 1 pin selection */
		}
	}
	if( my_index==N ){
		/* VETT is full */
		reset_and_disable(1);
		started=0;
		blink=1;
		my_index=0;	/* also used to show vett[i] */
		LED_Out(VETT[0]);
	}
	
	if(blink==1){
		blink_counter++;
		if(blink_counter==40){
			my_index++;
			if(my_index==N){
				my_index=-1;
				LED_Out(0);
			}
			else{
				LED_Out(VETT[my_index]);
			}
			blink_counter=0;
			
			
		}
			
	}
		
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
