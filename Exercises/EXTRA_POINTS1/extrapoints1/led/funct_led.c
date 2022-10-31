/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions to turn leds on/off
** Correlated files:    led.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led/led.h"

#define LED_NUM     8                   /* Number of user LEDs                */
const unsigned long led_mask[] = { 1UL<<7, 1UL<<6, 1UL<<5, 1UL<< 4, 1UL<< 3, 1UL<< 2, 1UL<< 1, 1UL<< 0 };
																				/* LPC_GPIO2->FIOPIN |= led_mask[0] turn on LD4 
																					 LPC_GPIO2->FIOPIN |= led_mask[1] turn on LD5 ... */

/*----------------------------------------------------------------------------
Function that turns on requested LED (NORD=0 -> TURN ON LD8 EAST=1 -> TURN ON LD9 ..)
 *----------------------------------------------------------------------------*/
void LED_On(uint8_t num) {
 
  LPC_GPIO2->FIOPIN |= led_mask[num];
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED (NORD=0 -> TURN ON LD8 EAST=1 -> TURN ON LD9 ..)
 *----------------------------------------------------------------------------*/
void LED_Off(uint8_t num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(uint8_t value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}
