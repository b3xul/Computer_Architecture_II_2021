/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           led.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_led, funct_led .c files
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#ifndef __LED_H
#define __LED_H

#include <inttypes.h>

/* lib_led */
void LED_init(void);
void LED_deinit(void);

/* funct_led */
void LED_On (uint8_t num);
void LED_Off (uint8_t num);
void LED_Out (uint8_t value);
void LED_On_All (void);
void LED_Off_All (void);

#endif /* end __LED_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
