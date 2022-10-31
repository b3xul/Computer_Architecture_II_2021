/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           labyrinth.h
** Last modified Date:  17/01/2021
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the labyrinth.c file
** Correlated files:    labyrinth.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#ifndef __LABYRINTH_H
#define __LABYRINTH_H

#include <inttypes.h>

/* Measures in squares */
#define X_SQUARES 15	/* number of horizontal squares */
#define Y_SQUARES 13	/* number of vertical squares */
#define RANGE 5	/* distance==5 squares from nearest obstacle means infinite distance */

/* Measures in pixels */
/* Labyrinth */
#define SQUARE_INTERNAL_SIZE 12
#define SQUARE_BORDER_SIZE 2
#define LAB_OFFSET_X 14
#define LAB_OFFSET_Y 34
#define LAB_X (SQUARE_INTERNAL_SIZE+SQUARE_BORDER_SIZE)*X_SQUARES+SQUARE_BORDER_SIZE
#define LAB_Y (SQUARE_INTERNAL_SIZE+SQUARE_BORDER_SIZE)*Y_SQUARES+SQUARE_BORDER_SIZE

/* Buttons */
#define BUTTONS_OFFSET_Y 246
#define RESET_BUTTON_OFFSET_X LAB_OFFSET_X
#define CLEAR_BUTTON_OFFSET_X 130
#define BUTTONS_INTERNAL_SIZE_X	94
#define BUTTONS_INTERNAL_SIZE_Y 44
#define BUTTONS_BORDER_SIZE 1
#define BUTTONS_X BUTTONS_INTERNAL_SIZE_X+2*BUTTONS_BORDER_SIZE
#define BUTTONS_Y BUTTONS_INTERNAL_SIZE_Y+2*BUTTONS_BORDER_SIZE

/* Colors used */
/* Interface */
#define BACKGROUND_COLOR Cyan
#define TEXT_COLOR NicePink

/* Labyrinth */
#define LINE_COLOR NiceGreen
#define SQUARE_COLOR White
#define OBSTACLE_COLOR Violet

/* Buttons */
#define BUTTONS_TEXT_COLOR Blue
#define BUTTONS_BACKGROUND_COLOR White

/* Robot */
#define MOVE_COLOR Blue
#define EXPLORE_COLOR	Red

typedef struct position { uint8_t y; uint8_t x; } Position;
typedef enum Directions {NORTH, EAST, SOUTH, WEST} DIRECTIONS; /* NORTH=0, EAST=1, SOUTH=2, WEST=3 */
typedef enum Modes {MOVE, EXPLORE} MODES;

typedef struct robot { Position pos;			/* current robot position */
											 DIRECTIONS dir;		/* current robot direction*/
											 _Bool end;					/* ==1 if going forward robot reaches exit */
											 uint8_t distance;	/* distance squares from nearest obstacle/wall (==RANGE  means infinite distance) */
											 MODES mode; } Robot;	/* current robot mode */
			
												
void compute_distance( void );

#endif /* end __LABYRINTH_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/

