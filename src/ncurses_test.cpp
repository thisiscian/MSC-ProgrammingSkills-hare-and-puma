#include "ncurses_lib.h"
using namespace std;

int main()
{
	Board<Tile> field(12,12);
	int horizontalPosition, verticalPosition;
	int width = field.get_width();
	int height = field.get_height();

	WINDOW* draw_field;
	int fieldWindowWidth;
	int fieldWindowHeight;
	int maxNumberOfTilesVisible;
	int fieldDisplayableWidth;
	int fieldDisplayableHeight;
	
	int tileLine = 4;
	int tileCols = 6;

	WINDOW* draw_statistics;
	WINDOW* draw_key;
	WINDOW* draw_input;

	/* define a field with arbitrarily different values for land, hare numbers and puma numbers */
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
		for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
		{
			if(horizontalPosition == 0 || horizontalPosition == width-1 || verticalPosition == 0 || verticalPosition == height-1)
			{
				field(horizontalPosition,verticalPosition).make_water();
				field(horizontalPosition, verticalPosition).hare = 0.0;
				field(horizontalPosition, verticalPosition).puma = 0.0;
			}
			else
			{
				field(horizontalPosition, verticalPosition).make_land();
				field(horizontalPosition, verticalPosition).hare = horizontalPosition-1;
				field(horizontalPosition, verticalPosition).puma = verticalPosition-1;
				//field(horizontalPosition, verticalPosition).hare = 255.0*max(cos(verticalPosition+horizontalPosition), 0.0);
				//field(horizontalPosition, verticalPosition).puma = 255.0*max(sin(verticalPosition+horizontalPosition), 0.0);
				if(horizontalPosition % 2 == 0 && verticalPosition % 2 == 0)
				{
					field(horizontalPosition, verticalPosition).make_water();
				}
			}
		}
	}

	BoardStatistics stats(field);
	initialise_ncurses();
	
	fieldWindowWidth = COLS/2-1;
	fieldWindowHeight = LINES-2;
	maxNumberOfTilesVisible = min(fieldWindowHeight/tileLine, fieldWindowWidth/tileCols);
	
	fieldWindowWidth = min(tileCols*maxNumberOfTilesVisible+2, tileCols*(width-2)+2);
	fieldWindowHeight = min(tileLine*maxNumberOfTilesVisible+2, tileLine*(height-2)+2);
	int widthBuffer = (COLS/2-1-fieldWindowWidth)/2;
	int heightBuffer = (LINES-2-fieldWindowHeight)/2;
	draw_field = newwin(fieldWindowHeight, fieldWindowWidth, 1+heightBuffer , widthBuffer);
	draw_statistics = newwin(LINES/2-1,COLS/2-1, 1, COLS/2-1);
	draw_key = newwin(LINES/2+1,COLS/4-1, LINES/2, COLS/2-1);
	draw_input = newwin(LINES/2+1,COLS/4-1, LINES/2, 3*COLS/4-1);
	refresh();
	set_title(draw_field, "FIELD");
	set_title(draw_input, "INPUT");
	set_key(draw_key, stats, tileCols, tileLine);
	set_statistics(draw_statistics, field, stats, 0.0);
	
	print_field(draw_field, field, stats, tileCols, tileLine);
	wrefresh(draw_field);
	refresh();
	getch();
	endwin();
}
