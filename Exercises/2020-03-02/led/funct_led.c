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
/* (higher leds)LD4<---LD11(lower leds) */
const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };

/* (higher leds)LD4--->LD11(lower leds) */
/* const unsigned long led_mask[] = { 1UL<<7, 1UL<<6, 1UL<<5, 1UL<< 4, 1UL<< 3, 1UL<< 2, 1UL<< 1, 1UL<< 0 };
																				   LPC_GPIO2->FIOPIN |= led_mask[0] turn on LD4 
																					 LPC_GPIO2->FIOPIN |= led_mask[1] turn on LD5 ... */


extern unsigned char led_value;	/* defined in lib_led.c */

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On(uint8_t num) {
 
  LPC_GPIO2->FIOPIN |= led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off(uint8_t num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
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
	led_value = value;
}
