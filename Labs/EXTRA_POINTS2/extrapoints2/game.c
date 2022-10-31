/*----------------------------------------------------------------------------
 * Name:    game.c
 * Purpose: implement the single-player game Blind Labyrinth
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Francesco SATTOLO - PoliTO - last modified 17/01/2021
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "GLCD/GLCD.h"
#include "TouchPanel/TouchPanel.h"
#include "RIT/RIT.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

#include "labyrinth.h"

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {

	SystemInit();  												/* System Initialization (i.e., PLL)  */
	LCD_Initialization();	
	TP_Init();
	/* RIT : JOYSTICK AND TOUCH SCREEN POLLING */
	init_RIT(0x004C4B40);									/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */
																				/* T = 50msec						 							*/
																				/* T = K / Fr = 5000000 / 100MHz      */
																				/* T = K / Fr = 0x004C4B40 / 100MHz   */
	TouchPanel_Calibrate();
	
	LCD_Clear(BACKGROUND_COLOR);
	GUI_Text(61, 10, (uint8_t *) "Blind Labyrinth", TEXT_COLOR, BACKGROUND_COLOR);
	DrawLabyrinth(LAB_OFFSET_X, LAB_OFFSET_Y);
	GUI_Text(0, 224, (uint8_t *) " Touch the labyrinth to start ", TEXT_COLOR, BACKGROUND_COLOR);
	DrawButton(RESET_BUTTON_OFFSET_X, BUTTONS_OFFSET_Y, (uint8_t *) "RESET");
	DrawButton(CLEAR_BUTTON_OFFSET_X, BUTTONS_OFFSET_Y, (uint8_t *) "CLEAR");

	enable_RIT();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
