/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           button.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_button, IRQ_button .c files
** Correlated files:    lib_button.c, IRQ_button.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __BUTTON_H
#define __BUTTON_H

void BUTTON_init(void);

void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);

#endif /* end __BUTTON_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
