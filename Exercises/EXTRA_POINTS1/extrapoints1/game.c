/*----------------------------------------------------------------------------
 * Name:    blind_labyrinth.c
 * Purpose: implement the single-player game Blind Labyrinth
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Francesco SATTOLO - PoliTO - last modified 09/01/2021
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

#include "labyrinth.h"

extern uint8_t labyrinth[Y][X];					/* defined in labyrinth.c							*/
extern Robot r;													/* defined in labyrinth.c							*/


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
	
	/* RIT : Debouncing and action for INT0 (START), KEY1 (ROTATE), KEY2 (RUN) */
	init_RIT(0x004C4B40);									
																				/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */
																				/* T = 50msec						 							*/
																				/* T = K / Fr = 5000000 / 100MHz      */
																				/* T = K / Fr = 0x004C4B40 / 100MHz   */
	
	/* TIMER0 : Direction LEDS timing */
		/*(TimerNo,      MR0,      MR1,      MR2,      MR3,PrescaleValue)*/
	init_timer(0,0x017D784,0x02FAF08,0x05F5E10,0x0BEBC20,0);	
																				/* T = 0.0625s off, 0.0625s on (MR0=8Hz)*/
																				/* T = K / Fr = 1562500 / 25MHz      	*/
																				/* T = K / Fr = 0x017D784 / 25MHz    	*/
	
																				/* T = 0.125s off, 0.125s on (MR1=4Hz)*/
																				/* T = K / Fr = 3125000 / 25MHz      	*/
																				/* T = K / Fr = 0x02FAF08 / 25MHz    	*/
																																					
																				/* T = 0.25s off, 0.25s on (MR2=2Hz)	*/
																				/* T = K / Fr = 6250000 / 25MHz      	*/
																				/* T = K / Fr = 0x05F5E10 / 25MHz    	*/	

																				/* T = 0.5s														*/
																				/* T = K / Fr = 12500000 / 25MHz      */
																				/* T = K / Fr = 0x0BEBC20 / 25MHz    	*/
	
	/* TIMER1 : Running LED timing */
		/*(TimerNo,      MR0,      MR1,      MR2,       MR3,PrescaleValue)*/
	init_timer(1,0x02625A0,0x04C4B40,0x0BEBC20,0x017D7840,0);	
																				/* T = 0.1s off, 0.1s on (MR0=5Hz)		*/
																				/* T = K / Fr = 2500000 / 25MHz     		*/
																				/* T = K / Fr = 0x02625A0 / 25MHz    	*/
																				
																				/* T = 0.2s 													*/
																				/* T = K / Fr = 5000000 / 25MHz     		*/
																				/* T = K / Fr = 0x04C4B40 / 25MHz    	*/
																				
																				/* T = 0.5s off, 0.5s on (MR1=1Hz)		*/
																				/* T = K / Fr = 12500000 / 25MHz      */
																				/* T = K / Fr = 0x0BEBC20 / 25MHz    	*/
																				
																				/* T = 1s 														*/
																				/* T = K / Fr = 25000000 / 25MHz     	*/
																				/* T = K / Fr = 0x017D7840 / 25MHz    */

	/* Init INT0 Button */
	LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */
	
	LPC_SC->EXTMODE = 0x1;
	
	NVIC_SetPriority(EINT0_IRQn, 0);				 /* decreasing priority	from EINT2->0	 */
	NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
