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
#include "labyrinth.h"

void rotate(void);

void run(void);
void check_new_position(void);
void win_function(void);

volatile _Bool win=0;

extern Robot r;		/* defined in labyrinth.c							*/

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
/* RIT : Debouncing and action for INT0 (START), KEY1 (ROTATE), KEY2 (RUN) */
void RIT_IRQHandler (void)
{			
	static uint8_t down0=0;
	static uint8_t down1=0;
	static uint8_t down2=0;
	
	switch(pressed_button){
		case int0:	/* START */
			if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* button pressed */
				down0=1;
			}
			else {	/* button released */
				if( down0 == 0 ){	/* Reenable button only if game hasn't started yet */
					NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
					LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
				}
				else{	/* down==1 */
					/* Game starts at release */
					BUTTON_init();									/* BUTTON Initialization           */
					enable_timer(0);								/* Start Direction Leds Timer			 */
					down0=0;
				}
				
				disable_RIT();
				reset_RIT();
			}
			break;
			
		case key1:	/* ROTATE */
			
			if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
				down1=1;
			}
			else {	/* button released */
				if( down1==1 ){
					rotate();
				}
				down1=0;			
				disable_RIT();
				reset_RIT();
				NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
			}
			break;
			
		case key2:	/* RUN */
			
			if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
				down2++;
				if( down2==1 && r.distance == 0 ){
					/* start led 5Hz without waiting for 1s to pass */
					enable_timer(1);
				}
				else if( down2 == 20 ){	/* run button still pressed after 50ms*20=1s */
					down2=0;
					if( r.distance != 0 ){
						run();
					}
				}
			}
			else {	/* button released */
				LED_Off(2);
				disable_timer(1);
				reset_timer(1);
				
				down2=0;			
				disable_RIT();
				reset_RIT();
				NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
			}
				


			break;
		default:
			break;
	}
	
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */

}

/******************************************************************************
** Function name:		rotate
**
** Descriptions:		turns off old led
**									change direction, distance and end flag of the robot
**									enable/disable direction led timing
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void rotate(void){	
	
	
	/* turn off old led */
	LED_Off((uint8_t) r.dir + 4);	/* (uint8_t) r.dir + 4 -> N=4=LD8, E=5=LD9, S=6=LD10, W=7=LD11 */
	
	/* change robot direction */
	r.dir=(DIRECTIONS) ((r.dir+1)%4);	/* EAST->SUD->WEST->NORD->EAST->SUD... */
	
	/* compute new distance */
	compute_distance();
	
	/* turn on new led depending on r.distance value */
	if( r.distance == 6 || r.end==1 ){
		if ( timer_status(0) == 1 ){
			/* Disable direction led timer since led always on */
			disable_timer(0);
			reset_timer(0);
		}
		LED_On((uint8_t) r.dir + 4);
	}
	else if ( r.distance <=5 && r.end == 0 && timer_status(0) == 0 ) {
		enable_timer(0);
	}
	return;
}

/******************************************************************************
** Function name:		run
**
** Descriptions:		enable running led timer
**									change distance and position of the robot
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void run(void){
	/* start led 1Hz */
	enable_timer(1);
	
	/* update position */
	switch(r.dir){
		case(NORD):
			r.pos.y--;
			break;
		case(EAST):
			r.pos.x++;
			break;
		case(SUD):
			r.pos.y++;
			break;
		case(WEST):
			r.pos.x--;
			break;
		default:
			break;
	}
	
	/* update distance */
	if ( r.distance == 6 )
		compute_distance();
	else
		r.distance--;
	
	/* check final position */
	check_new_position();
}
/******************************************************************************
** Function name:		check_new_position
**
** Descriptions:		check if player won or if direction timer needs to be enabled again
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void check_new_position(void){
	if(r.end == 1 && r.distance == 0){	
		win_function();		/* victory */
	}
	else if(r.end == 0 && r.distance == 5){
		enable_timer(0);	/* Direction timer must turn on again */
	}
	/*else{ direction leds will update themself when they will interrupt }*/
	
	return;
}

/******************************************************************************
** Function name:		win_function
**
** Descriptions:		
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void win_function(void){
	win=1;
	/* Timer 1 will turn all leds on and off */
	
	/* Disable buttons */
	NVIC_DisableIRQ(EINT2_IRQn);
	NVIC_DisableIRQ(EINT1_IRQn); 
	NVIC_DisableIRQ(EINT0_IRQn); 
	
	/* Disable timers */
	disable_RIT();
	disable_timer(0);
	
	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
