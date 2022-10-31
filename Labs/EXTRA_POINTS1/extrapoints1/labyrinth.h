/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           labyrinth.h
** Last modified Date:  2021-01-09
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the labyrinth.c file
** Correlated files:    labyrinth.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#ifndef __LABYRINTH_H
#define __LABYRINTH_H

#include <inttypes.h>

#define X 15
#define Y 13

typedef enum Directions {NORD, EAST, SUD, WEST} DIRECTIONS; /* NORD=0, EAST=1, SUD=2, WEST=3 */

typedef struct position { uint8_t y; uint8_t x; } Position;

typedef struct robot { Position pos;
											 DIRECTIONS dir;
											 _Bool end;					/* ==1 if going forward reaches exit */
											 uint8_t distance; } Robot;	/* 	dist==6 means infinite distance */
			
												
void compute_distance( void );

#endif /* end __LABYRINTH_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/

