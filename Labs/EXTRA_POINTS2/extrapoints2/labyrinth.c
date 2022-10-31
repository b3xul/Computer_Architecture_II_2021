/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           labyrinth.c
** Last modified Date:  17/01/2021
** Last Version:        V1.00
** Descriptions:        functions that checks position in the labyrinth
** Correlated files:    labyrinth.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "labyrinth.h"
#include "GLCD/GLCD.h"

/*----------------------------------------------------------------------------
  LABYRINTH GLOBAL DATA STRUCTURE
 *----------------------------------------------------------------------------*/
volatile uint8_t labyrinth[Y_SQUARES][X_SQUARES]=	{ {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
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
											5,			/* uint_8t distance */
											MOVE	};/* MODES mode */		
/*----------------------------------------------------------------------------
  Function that computes distance from the next obstacle/wall and draws obstacles found
 *----------------------------------------------------------------------------*/
void compute_distance(){
	int8_t i;
	int8_t dist=0;
	
	r.end=0;
	switch(r.dir){
		case(NORTH):
			/*----------------------------------------------------------------------------
				NORTH
			 *----------------------------------------------------------------------------*/
			
			for( i=r.pos.y ; i >= r.pos.y-(RANGE-1) ; i-- ){
				if( i==0 || labyrinth[i-1][r.pos.x] == 3 )
					break;
				else if( labyrinth[i-1][r.pos.x] == 1 ){
					labyrinth[i-1][r.pos.x] = 3;
					DrawSquare( index_to_position_x(r.pos.x), index_to_position_y(i-1), SQUARE_INTERNAL_SIZE, OBSTACLE_COLOR);
					break;
				}
				dist++;
			}

			if (labyrinth[i][r.pos.x]==2)
				r.end=1;
			
			break;
		case(EAST):
			/*----------------------------------------------------------------------------
				EAST
			 *----------------------------------------------------------------------------*/
			
			for( i=r.pos.x ; i <= r.pos.x+(RANGE-1) ; i++ ){
				if( i==X_SQUARES-1 || labyrinth[r.pos.y][i+1] == 3 )
					break;
				else if( labyrinth[r.pos.y][i+1] == 1 ){
					labyrinth[r.pos.y][i+1] = 3;
					DrawSquare( index_to_position_x(i+1), index_to_position_y(r.pos.y), SQUARE_INTERNAL_SIZE, OBSTACLE_COLOR);
					break;
				}
				dist++;
			}
			
			if (labyrinth[r.pos.y][i]==2)
				r.end=1;
			
			break;
		case(SOUTH):
			/*----------------------------------------------------------------------------
				SOUTH
			 *----------------------------------------------------------------------------*/

			for( i=r.pos.y ; i <= r.pos.y+(RANGE-1) ; i++ ){
				if( i==Y_SQUARES-1 || labyrinth[i+1][r.pos.x] == 3 )
					break;
				else if( labyrinth[i+1][r.pos.x] == 1 ){
					labyrinth[i+1][r.pos.x] = 3;
					DrawSquare( index_to_position_x(r.pos.x), index_to_position_y(i+1), SQUARE_INTERNAL_SIZE, OBSTACLE_COLOR);
					break;
				}
					
				dist++;
			}
			
			if (labyrinth[i][r.pos.x]==2)
				r.end=1;
			
			break;
		case(WEST):
			/*----------------------------------------------------------------------------
				WEST
			 *----------------------------------------------------------------------------*/

			for( i=r.pos.x ; i >= r.pos.x-(RANGE-1) ; i-- ){
				if( i==0 || labyrinth[r.pos.y][i-1] == 3 )
					break;
				else if( labyrinth[r.pos.y][i-1] == 1 ){
					labyrinth[r.pos.y][i-1] = 3;
					DrawSquare( index_to_position_x(i-1), index_to_position_y(r.pos.y), SQUARE_INTERNAL_SIZE, OBSTACLE_COLOR);
					break;
				}
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
