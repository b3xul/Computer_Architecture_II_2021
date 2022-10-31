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

#define N 5
extern int count_negative_and_odd(int v[N], int n);	/* defined in ASM_function.s */
int v[N]={-2,-5,2,3,-135};

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();											/* Joystick Initialization            */
	
	/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */
	/* RIT Initialization 25 msec-> K=(25*10^-3) s*(100*10^6) Hz=2.500.000=0x02625A0 */
	init_RIT(0x02625A0);
	/*POLLING: enable_RIT();							 RIT enabled												*/
	
	/* TIMER Initialization 50 msec-> K=(50*10^-3) s*(25*10^6) Hz=..=0x..      	*/
	/*(TimerNo,      MR0,      MR1,      MR2,      MR3,PrescaleValue)*/
	init_timer(0,0x017D784,0,0,0,0);
	
	/*Blinking->lib_timer I,R!!!*/
	init_timer(3,0x097D784,0,0,0,0);
	enable_timer(3);

	/*LIB_TIMER!*/
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
