/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.c
** Last modified Date:  2021-01-07
** Last Version:        V1.00
** Descriptions:        functions to turn leds on/off
** Correlated files:    led.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "GLCD/GLCD.h"
#include "GLCD/AsciiLib.h"

#include "labyrinth.h"

extern Robot r;	/* defined in labyrinth.c							*/

uint16_t index_to_position_x(uint16_t index_x){
	return LAB_OFFSET_X+SQUARE_BORDER_SIZE+(index_x*(SQUARE_INTERNAL_SIZE+SQUARE_BORDER_SIZE));
}

uint16_t index_to_position_y(uint16_t index_y){
	return LAB_OFFSET_Y+SQUARE_BORDER_SIZE+(index_y*(SQUARE_INTERNAL_SIZE+SQUARE_BORDER_SIZE));
}

/* Xpos, Ypos: measures in pixels */
void DrawLabyrinth(uint16_t Xpos, uint16_t Ypos){
	uint16_t x,y;
	
	/* Draw Grid */
	/* x,y represents pixels */
	/* Horizontal Lines */
	for( y=Ypos ; y<=Ypos+LAB_Y ; y+=(SQUARE_INTERNAL_SIZE+SQUARE_BORDER_SIZE) ){
		MyDrawLine(Xpos, y, LAB_X, LINE_COLOR, HORIZONTAL);
		MyDrawLine(Xpos, y+1, LAB_X, LINE_COLOR, HORIZONTAL);
	}
	
	/* Vertical Lines */
	for( x=Xpos ; x<=Xpos+LAB_X ; x+=(SQUARE_INTERNAL_SIZE+SQUARE_BORDER_SIZE) ){
		MyDrawLine(x, Ypos, LAB_Y, LINE_COLOR, VERTICAL);
		MyDrawLine(x+1, Ypos, LAB_Y, LINE_COLOR, VERTICAL);
	}
	
	/* Draw squares */
	/* x,y represents squares */
	for( y=0; y<Y_SQUARES; y++){
		for( x=0; x<X_SQUARES; x++){
			DrawSquare(index_to_position_x(x),index_to_position_y(y),SQUARE_INTERNAL_SIZE, SQUARE_COLOR);
		}
	}
	return;
}

void DrawButton(uint16_t Xpos, uint16_t Ypos, uint8_t *str){
	
	MyDrawLine(Xpos, Ypos, BUTTONS_X, LINE_COLOR, HORIZONTAL);
	MyDrawLine(Xpos, Ypos+(BUTTONS_INTERNAL_SIZE_Y+BUTTONS_BORDER_SIZE), BUTTONS_X, LINE_COLOR, HORIZONTAL);
	
	MyDrawLine(Xpos, Ypos, BUTTONS_Y, LINE_COLOR, VERTICAL);
	MyDrawLine(Xpos+(BUTTONS_INTERNAL_SIZE_X+BUTTONS_BORDER_SIZE), Ypos, BUTTONS_Y, LINE_COLOR, VERTICAL);
	
	DrawRectangle(Xpos+1, Ypos+1, BUTTONS_INTERNAL_SIZE_X, BUTTONS_INTERNAL_SIZE_Y, BUTTONS_BACKGROUND_COLOR);
	
	GUI_Text(Xpos+24, Ypos+BUTTONS_INTERNAL_SIZE_Y/3, str, BUTTONS_TEXT_COLOR, BUTTONS_BACKGROUND_COLOR);
	
	return;
}

void DrawRobot(){
	uint16_t index_x=r.pos.x;
	uint16_t index_y=r.pos.y;
	uint16_t color=(r.mode==MOVE)?MOVE_COLOR:EXPLORE_COLOR;
	
	uint16_t x,xi,y,yi;
	uint8_t count;
	
	switch(r.dir){
		case(NORTH):
			xi=index_to_position_x(index_x)+1;
			yi=index_to_position_y(index_y)+3;
		
			count=4;
			for( y=yi ; y<yi+7 ; y++ ){
				for( x=xi+count; x < xi+(10-count); x++){
					LCD_SetPoint(x, y, color);
				}
				if(count!=0)
					count--;
			}
			break;
		
		case(EAST):
			xi=index_to_position_x(index_x)+3;
			yi=index_to_position_y(index_y)+1;
			
			/* Higher part of triangle */
			count=2;
			for( y=yi; y<yi+5; y++ ){
				for( x=xi; x < xi+count; x++){
					LCD_SetPoint(x, y, color);
				}
				count++;
			}
			/* Lower part of triangle */
			count=6;
			for( ; y<yi+10; y++ ){
				for( x=xi; x < xi+count; x++){
					LCD_SetPoint(x, y, color);
				}
				count--;
			}
			break;
			
		case(SOUTH):
			xi=index_to_position_x(index_x)+1;
			yi=index_to_position_y(index_y)+3;
			
			count=0;
			for( y=yi; y<yi+7; y++ ){
				for( x=xi+count; x < xi+(10-count); x++){
					LCD_SetPoint(x, y, color);
				}
				if(y>yi)
					count++;
			}
			break;
		
		case(WEST):
			xi=index_to_position_x(index_x)+3;
			yi=index_to_position_y(index_y)+1;
			/* Higher part of triangle */
			count=2;
			for( y=yi; y<yi+5; y++ ){
				for( x=xi+(6-count); x < xi+6; x++){
					LCD_SetPoint(x, y, color);
				}
				count++;
			}
			/* Lower part of triangle */
			count=6;
			for( ; y<yi+10 ; y++ ){
				for( x=xi+(6-count); x < xi+6; x++){
					LCD_SetPoint(x, y, color);
				}
				count--;
			}
			break;
		default:
			break;
	}
	return;
}

void DeleteRobot(void){
	
	DrawSquare(index_to_position_x(r.pos.x), index_to_position_y(r.pos.y), SQUARE_INTERNAL_SIZE, SQUARE_COLOR);
	
	return;
}
