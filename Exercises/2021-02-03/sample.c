/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: 
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Francesco Sattolo - PoliTO - last modified 18/02/2021 */
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

 _Bool acquisizione;
	
int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization (only key2)  */
	joystick_init();											/* Joystick Initialization            */
	
	/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */	
	/* RIT Initialization 25 msec-> K=(25*10^-3) s*(100*10^6) Hz=2.500.000=0x02625A0 */
	/* init_RIT(0x02625A0); */
	init_RIT(0x02625A0);
	
	/* POLLING enable_RIT(); */
	
	/* TIMER3 */
	/* TIMER MR0 Initialization 1 s-> K=(1) s*(25*10^6) Hz=25.000.000=0x017D7840 */
	/* TIMER MR1 Initialization 2 s-> K=(2) s*(25*10^6) Hz=50.000.000=0x02FAF080 */
	/*(TimerNo,      MR0,      MR1,      MR2,      MR3,PrescaleValue)*/
	init_timer(3,0x017D7840,0x02FAF080,0,0,0);
	
	acquisizione=0;	/* monitor mode */
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
