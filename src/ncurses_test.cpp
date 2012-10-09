#include "tile.h"
#include "ncurses_test.h"
#include "output.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "board.h"

using namespace std;

int main()
{
	Board<Tile> field(10,10);
	int horizontalPosition, verticalPosition;
	int width = field.get_width();
	int height = field.get_height();
	stringstream value;

	/* define a field with arbitrarily different values for land, hare numbers and puma numbers */
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
		for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
		{
			field(horizontalPosition, verticalPosition).make_land();
			field(horizontalPosition, verticalPosition).hare = 255.0*max(cos(verticalPosition+horizontalPosition), 0.0);
			field(horizontalPosition, verticalPosition).puma = 255.0*max(sin(verticalPosition+horizontalPosition), 0.0);
			if(horizontalPosition % 2 == 0 && verticalPosition % 2 == 0)
			{
				field(horizontalPosition, verticalPosition).make_water();
			}
		}
	}

	initscr();
	WINDOW* draw_field;
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	start_color(); 

 	init_pair(1,COLOR_CYAN,COLOR_BLUE); 
 	init_pair(2,COLOR_BLACK,COLOR_GREEN); 
 	init_pair(3,COLOR_WHITE,COLOR_GREEN); 


	draw_field = newwin(4*width+2, 6*height+2, 1 , 1);
	wattron(draw_field, COLOR_PAIR(1));
	box(draw_field, 0, 0);

	refresh();
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
		for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
		{
			if(!field(horizontalPosition, verticalPosition).is_land())
			{
					wattron(draw_field, COLOR_PAIR(1));
					mvwprintw(draw_field, 4*verticalPosition+1, 6*horizontalPosition+1, " ~~~~ ");
					mvwprintw(draw_field, 4*verticalPosition+2, 6*horizontalPosition+1, " ~~~~ ");
					mvwprintw(draw_field, 4*verticalPosition+3, 6*horizontalPosition+1, " ~~~~ ");
					mvwprintw(draw_field, 4*verticalPosition+4, 6*horizontalPosition+1, " ~~~~ ");
					wattroff(draw_field, COLOR_PAIR(1));
			}
			else
			{
				wattron(draw_field, A_BOLD);
			  value.str("");
				
				value << " H" << setw(3) << floor(field(horizontalPosition,verticalPosition).hare) << " ";
				wattron(draw_field, COLOR_PAIR(2));
				mvwprintw(draw_field, 4*verticalPosition+1, 6*horizontalPosition+1, "      ");
				mvwprintw(draw_field, 4*verticalPosition+4, 6*horizontalPosition+1, "      ");
				mvwprintw(draw_field, 4*verticalPosition+2, 6*horizontalPosition+1, value.str().c_str());
				wattroff(draw_field, COLOR_PAIR(2));
				
			  value.str("");
				value << setw(2) << " P" << setw(3) << floor(field(horizontalPosition,verticalPosition).puma) << " ";
				wattron(draw_field, COLOR_PAIR(3));
				mvwprintw(draw_field, 4*verticalPosition+3, 6*horizontalPosition+1, value.str().c_str());
				wattroff(draw_field, COLOR_PAIR(3));
				wattroff(draw_field, A_BOLD);
			}
			refresh();
			wrefresh(draw_field);
		}
	}
	wattroff(draw_field, COLOR_PAIR(1));
	curs_set(0);
	wrefresh(draw_field);
	getch();
	endwin();
}
