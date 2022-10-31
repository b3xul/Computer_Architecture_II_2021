/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  17/01/2021
** Last Version:        V1.00
** Descriptions:        functions to manage joystick and touch screen actions
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "GLCD/GLCD.h"
#include "TouchPanel/TouchPanel.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"

#include "labyrinth.h"

extern uint8_t labyrinth[Y_SQUARES][X_SQUARES];	/* defined in labyrinth.c							*/
extern Robot r;																	/* defined in labyrinth.c							*/

void rotate(DIRECTIONS newDir);
void run(void);

static _Bool win=0;

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler:
**									Manages debouncing and action for INT0 (START), KEY1 (ROTATE), KEY2 (RUN)
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
/* RIT : JOYSTICK AND TOUCH SCREEN POLLING */
void RIT_IRQHandler (void)
{			
	static _Bool started=0;
	
	static _Bool select=0;
	static uint8_t down=0;
	static uint8_t left=0;
	static uint8_t right=0;
	static uint8_t up=0;
	
	uint16_t x;
	uint16_t y;
	
	/* TOUCH SCREEN ACTIONS*/
	getDisplayPoint(&display, Read_Ads7846(), &matrix ) ;
	if( started==0 && win==0 &&
			display.x > LAB_OFFSET_X && display.x < LAB_OFFSET_X+LAB_X &&
			display.y > LAB_OFFSET_Y && display.y < LAB_OFFSET_Y+LAB_Y ){
		/* Clicked inside the labyrinth: start game */
		started=1;
		DeleteText(0, 224, 30, BACKGROUND_COLOR); /* strlen(" Touch the labyrinth to start ")=30 */
		joystick_init();
		DrawRobot();
	}
	else if( started==1 &&
					 display.x > RESET_BUTTON_OFFSET_X && display.x < RESET_BUTTON_OFFSET_X+BUTTONS_X &&
					 display.y > BUTTONS_OFFSET_Y && display.y < BUTTONS_OFFSET_Y+BUTTONS_Y ){
		/* Clicked RESET BUTTON: restart program */
		__NVIC_SystemReset();
	}
	else if( started==1 && win==0 &&
					 display.x > CLEAR_BUTTON_OFFSET_X && display.x < CLEAR_BUTTON_OFFSET_X+BUTTONS_X &&
					 display.y > BUTTONS_OFFSET_Y && display.y < BUTTONS_OFFSET_Y+BUTTONS_Y ){
		/* Clicked CLEAR BUTTON: clear screen */
		for( y=0; y<Y_SQUARES; y++){
			for( x=0; x<X_SQUARES; x++){
				if( labyrinth[y][x] == 3 ){
					labyrinth[y][x] = 1;
					DrawSquare(index_to_position_x(x),index_to_position_y(y),SQUARE_INTERNAL_SIZE, SQUARE_COLOR);
				}
			}
		}
		compute_distance();	/* Draw again obstacle if it's in view */
	}
		
	/* JOYSTICK ACTIONS */
	if( started==1 && win == 0){
		/* SELECT */
		if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
			/* Pressed */
			select=1;
		}
		else{
			/* Released */
			if( select == 1){
				r.mode=(MODES) ((r.mode+1)%2);	/* MOVE->EXPLORE->MOVE... */
				DrawRobot();
			}
			select=0;
		}
		
		/* DOWN */
		if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){
			/* Pressed */
			down++;
			if( down == 1 && r.dir!=SOUTH ){
				rotate(SOUTH);
			}
			else if ( r.distance != 0 && r.mode==MOVE && down == 20 ){
				down=0;
				run();
			}
		}
		else{
			/* Released */
			down=0;
		}
		
		/* LEFT*/
		if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
			/* Pressed */
			left++;
			if( left == 1 && r.dir!=WEST ){
				rotate(WEST);
			}
			else if ( r.distance != 0 && r.mode==MOVE && left == 20 ){
				left=0;
				run();
			}
		}
		else{
			/* Released */
			left=0;
		}
		
		/* RIGHT */
		if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
			/* Pressed */
			right++;
			if( right == 1 && r.dir!=EAST ){
				rotate(EAST);
			}
			else if ( r.distance != 0 && r.mode==MOVE && right == 20 ){
				right=0;
				run();
			}
		}
		else{
			/* Released */
			right=0;
		}
		
		/* UP */
		if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){
			up++;
			if( up == 1 && r.dir!=NORTH ){
				rotate(NORTH);
			}
			else if ( r.distance != 0 && r.mode==MOVE && up == 20 ){
				up=0;
				run();
			}
		}
		else{
			/* Released */
			up=0;
		}
	}
	
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */

}

/******************************************************************************
** Function name:		rotate
**
** Descriptions:		change direction, distance, end flag of the robot and move it
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void rotate(DIRECTIONS newDir){
	
	/* Delete old robot */
	DeleteRobot();
	
	/* change robot direction */
	r.dir=newDir;
	
	/* Draw new robot */
	DrawRobot();
	
	/* compute new distance */
	compute_distance();
	
	return;
}

/******************************************************************************
** Function name:		run
**
** Descriptions:		change distance and position of the robot and move it
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void run(void){
	
	/* Delete old robot */
	DeleteRobot();
	
	/* update position */
	switch(r.dir){
		case(NORTH):
			r.pos.y--;
			break;
		case(EAST):
			r.pos.x++;
			break;
		case(SOUTH):
			r.pos.y++;
			break;
		case(WEST):
			r.pos.x--;
			break;
		default:
			break;
	}
	
	/* Draw new robot */
	DrawRobot();
	
	/* update distance */
	if ( r.distance == RANGE )
		compute_distance();
	else
		r.distance--;
	
	/* check final position */
	if(r.end == 1 && r.distance == 0){
		GUI_Text(80, 224, (uint8_t *) "YOU WON!!!", TEXT_COLOR, BACKGROUND_COLOR);
		win=1;
		DrawRectangle(CLEAR_BUTTON_OFFSET_X, BUTTONS_OFFSET_Y, BUTTONS_X, BUTTONS_Y, BACKGROUND_COLOR);
		GUI_Text(15, 295, (uint8_t *) "Reset button to start again", TEXT_COLOR, BACKGROUND_COLOR);
	}
	
}
/******************************************************************************
**                            End Of File
******************************************************************************/
