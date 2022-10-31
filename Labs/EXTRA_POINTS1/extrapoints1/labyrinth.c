/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           labyrinth.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions that checks position in the labyrinth
** Correlated files:    labyrinth.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "labyrinth.h"

/*----------------------------------------------------------------------------
  LABYRINTH GLOBAL DATA STRUCTURE
 *----------------------------------------------------------------------------*/
volatile uint8_t labyrinth[Y][X]=	{ {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
																		{0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
																		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
																		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
																		{1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
																		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
																		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
																		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
																		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																		{2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2} };

/*----------------------------------------------------------------------------
  ROBOT GLOBAL DATA STRUCTURE
 *----------------------------------------------------------------------------*/
volatile Robot r = { {7, 7},	/* Position pos */
											EAST,		/* DIRECTIONS dir */
											0,			/* _Bool end */
											5};			/* uint_8t distance */

/*----------------------------------------------------------------------------
  Function that computes distance from the next obstacle/wall
 *----------------------------------------------------------------------------*/
void compute_distance(){
	int8_t i;
	int8_t dist=0;
	
	r.end=0;
	switch(r.dir){
		case(NORD):
			/*----------------------------------------------------------------------------
				NORD
			 *----------------------------------------------------------------------------*/
			
			for( i=r.pos.y ; i >= r.pos.y-5 ; i-- ){
				if( i==0 || labyrinth[i-1][r.pos.x] == 1 )
					break;
				dist++;
			}

			if (labyrinth[i][r.pos.x]==2)
				r.end=1;
			
			break;
		case(EAST):
			/*----------------------------------------------------------------------------
				EAST
			 *----------------------------------------------------------------------------*/
			
			for( i=r.pos.x ; i <= r.pos.x+5 ; i++ ){
				if( i==X-1 || labyrinth[r.pos.y][i+1] == 1 )
					break;
				dist++;
			}
			
			if (labyrinth[r.pos.y][i]==2)
				r.end=1;
			
			break;
		case(SUD):
			/*----------------------------------------------------------------------------
				SUD
			 *----------------------------------------------------------------------------*/

			for( i=r.pos.y ; i <= r.pos.y+5 ; i++ ){
				if( i==Y-1 || labyrinth[i+1][r.pos.x] == 1 )
					break;
				dist++;
			}
			
			if (labyrinth[i][r.pos.x]==2)
				r.end=1;
			
			break;
		case(WEST):
			/*----------------------------------------------------------------------------
				WEST
			 *----------------------------------------------------------------------------*/

			for( i=r.pos.x ; i >= r.pos.x-5 ; i-- ){
				if( i==0 || labyrinth[r.pos.y][i-1] == 1 )
					break;
				dist++;
			}
			
			if (labyrinth[r.pos.y][i]==2)
				r.end=1;
			
			break;
		default:
			break;
	}
	
	r.distance = dist;

	return;
}
