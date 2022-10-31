/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_led.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions to init/deinit leds
** Correlated files:    led.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led/led.h"

/*----------------------------------------------------------------------------
  Function that initializes LEDs and switch them off
 *----------------------------------------------------------------------------*/

void LED_init(void) {

  LPC_PINCON->PINSEL4 &= 0xFFFF0000;	//PIN mode GPIO (00b value per P2.0 to P2.7)
	LPC_GPIO2->FIODIR   |= 0x000000FF;  //P2.0...P2.7 Output (LEDs on PORT2 defined as Output)
  /* LPC_GPIO2->FIOSET    = 0x000000FF;	//all LEDs on */
	LPC_GPIO2->FIOCLR    = 0x000000FF;  //all LEDs off

}

void LED_deinit(void) {

  LPC_GPIO2->FIODIR &= 0xFFFFFF00;  //P2.0...P2.7 Output LEDs on PORT2 defined as Output
}