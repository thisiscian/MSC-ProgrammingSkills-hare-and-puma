///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// ---------------                                                           //
// ncurses_lib.cpp                                                           //
// ---------------                                                           //
//                                                                           //
// This program contains all of the functions required to start the gui.     //
// The 'board' is taken in, and scaled to fit the terminal window the        //
// program is ran in. Each section of the board relates to a displayed       //
// 'tile', which is coloured according to the type of ground that it is      //
// made of.                                                                  //
//                                                                           //
// Blue: tile is completely water                                            //
// Green: tile contains at least some land                                   //
// Cyan: tile contains at least some water                                   //
//                                                                           //
// If a tile has cyan and green colours in it, then it is known as           //
// 'wetlands', which contain some water and some land elements. The ratio of //
// visible green and cyan is the ratio of land and water in that tile.       //
//                                                                           //
// maintained by Cian Booth                                                  //
// email issues to this.is.cian@gmail.com                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "ncurses_field.h"
using namespace std;

// Constructor for ncursesfield, sets sizes
NcursesField::NcursesField(Board<Tile>& board_in, Options& options_in, int x, int y)
{
	board = &board_in; 						// take in a pointer to the main board
	options = &options_in;				// options contains some useful stuff

	initialise_ncurses();					// intialise all the things to do with ncurses
	tileLines = x; 								// this is the height of each tile
	tileCols = y;									// the width of each tile
	set_field_window_size();		  // sets the field window's size and scaling
	stats.init(*board);						// initialise statistics based on board; 
	delay = options->delay*1000;	// the delay between frames in milliseconds;
	old_time = clock();       		// starts clock, for frame refreshing
}

void NcursesField::initialise_ncurses()
{
	initscr();
	start_color();  											// allows use of colour
 	init_pair(1,COLOR_CYAN,COLOR_BLUE); 	// pure ocean
 	init_pair(2,COLOR_BLACK,COLOR_GREEN); // pure land, with hares
 	init_pair(3,COLOR_WHITE,COLOR_GREEN); // pure land, with pumas
 	init_pair(4,COLOR_BLACK,COLOR_CYAN);  // 'wetlands' with hares
 	init_pair(5,COLOR_WHITE,COLOR_CYAN);  // 'wetlands' with pumas

	noecho();			// stops writing keypresses to screen
	curs_set(0);	// hides the cursor
	halfdelay(1);	// makes getch() nonblocking, after 0.1 seconds
}

void NcursesField::update_input()
{
	int l = 1;
	
	//this section entirely redraws the input window
	delwin(input);
	input = newwin(4,COLS/4-1, LINES-5, 3*COLS/4-1);
	set_title(input, "INPUT");
	
	mvwprintw(input, l, 1, " q/Q - quits the program");
	++l;	
	mvwprintw(input, l, 1, " p/P  - pause and unpause");
	++l;	

	wrefresh(input);

}

// resets statistics window: deletes old window, redraws new window,
// recalculates and displays statistics
void NcursesField::update_statistics(double time)
{
	int l = 1;
	stringstream text;
	stats.trawl_for_statistics(*board, time);

	delwin(statistics);	
	statistics = newwin(LINES/2-1,COLS/4-1, 1, 3*COLS/4-1);

	text.str("");
	text << "Simulation Time: " << time << endl;
	mvwprintw(statistics, l, 1, text.str().c_str());
	l++;

	text.str("");
	text << "Total Density of Hares: " << stats.get_hare_total() << endl;
	mvwprintw(statistics, l, 1, text.str().c_str());
	l++;
	
	text.str("");
	text << "Total Density of Pumas: " << stats.get_puma_total() << endl;
	mvwprintw(statistics, l, 1, text.str().c_str());
	l++;

	text.str("");
	text << "Largest Density of Hares: " << stats.get_hare_max() << endl;
	mvwprintw(statistics, l, 1, text.str().c_str());
	l++;

	text.str("");
	text << "Largest Density of Pumas: " << stats.get_puma_max() << endl;
	mvwprintw(statistics, l, 1, text.str().c_str());
	l++;

	// if the time is very close to zero,
	// the average density should not be displayed
	if(time >= options->time_step)
	{
		text.str("");
		text << "Average Hare Density: " << stats.get_hare_average() << endl;
		mvwprintw(statistics, l, 1, text.str().c_str());
		
		l++;
		text.str("");
		text << "Average Puma Density: " << stats.get_puma_average() << endl;
		mvwprintw(statistics, l, 1, text.str().c_str());
	}

	set_title(statistics, "STATISTICS");
}

// gets the maximum number of hares in any tile
double NcursesField::get_hare_max()
{
	int max = 0;
	for(int i=1; i<fieldtile.size(); i++)
	{
		if(fieldtile[max].hare <  fieldtile[i].hare){max = i;}
	}
	return fieldtile[max].hare;
}

// gets the maximum number of pumas in any tile
double NcursesField::get_puma_max()
{
	int max = 0;
	for(int i=1; i<fieldtile.size(); i++)
	{
		if(fieldtile[max].puma <  fieldtile[i].puma){max = i;}
	}
	return fieldtile[max].puma;
}

void NcursesField::get_symbol_worth()
{
	// each animal's symbol is worth a proportion of their current maximum value.
	// The ratio here, is the number of symbols available, e.g. 2 for H and ~
	// multiplied by the drawable area, e.g tileCols*tileLines without the borders
	// and divided by two, because the tile is split two species
	hareSymbolWorth = get_hare_max()/((tileCols-2)*(tileLines-2));
	pumaSymbolWorth = get_puma_max()/((tileCols-2)*(tileLines-2));
}

// draws a decription of what each key means
void NcursesField::update_key()
{
	int l = 1;
	stringstream text;
	get_symbol_worth();
	delwin(key);
	key = newwin(LINES/2-4,COLS/4-1, LINES/2, 3*COLS/4-1);
	
	wattron(key, COLOR_PAIR(2));
	mvwprintw(key, l, 1, "   ");
	wattroff(key, COLOR_PAIR(2));
	mvwprintw(key, l, 5, " - Land");
	++l;	

	wattron(key, COLOR_PAIR(5));
	mvwprintw(key, l, 1, "   ");
	wattroff(key, COLOR_PAIR(5));
	mvwprintw(key, l, 5, " - Wetlands");
	++l;	

	wattron(key, COLOR_PAIR(1));
	mvwprintw(key, l, 1, "   ");
	wattroff(key, COLOR_PAIR(1));
	mvwprintw(key, l, 5, " - Ocean");
	++l;	
	++l;	

	text.str("");
	text << " - 0-" << hareSymbolWorth << " Hares";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(2));
	mvwprintw(key, l, 1, "   ");
	wattroff(key, COLOR_PAIR(2));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	wattron(key, COLOR_PAIR(1));
	text.str("");
	text << " - " << hareSymbolWorth << "-"<< 2*hareSymbolWorth << " Hares";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(2));
	mvwprintw(key, l, 1, " ~ ");
	wattroff(key, COLOR_PAIR(2));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << 2*hareSymbolWorth << " Hares";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(2));
	mvwprintw(key, l, 1, " H ");
	wattroff(key, COLOR_PAIR(2));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;
	++l;	

	text.str("");
	text << " - 0-" << pumaSymbolWorth << " Pumas";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(3));
	mvwprintw(key, l, 1, "   ");
	wattroff(key, COLOR_PAIR(3));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << pumaSymbolWorth << "-"<< 2*pumaSymbolWorth << " Pumas";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(3));
	mvwprintw(key, l, 1, " ~ ");
	wattroff(key, COLOR_PAIR(3));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << 2*pumaSymbolWorth << " Pumas";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(3));
	mvwprintw(key, l, 1, " P ");
	wattroff(key, COLOR_PAIR(3));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;
	++l;

	text.str("");
	text << "Tile Width: " << tileCols << " Columns";	
	mvwprintw(key, l, 1, text.str().c_str());
	++l;	
	
	text.str("");
	text << "Tile Height: " << tileLines << " Lines";	
	mvwprintw(key, l, 1, text.str().c_str());
	++l;
	set_title(key, "KEY");
}

void NcursesField::update_field(double time)
{
	int x, y, draw_land;
	int width = board->get_width();
	int height = board->get_height();
	double hares_unrepresented_in_tile;
	double pumas_unrepresented_in_tile;

	// delete and redraw the field window
	delwin(field);
	field = newwin(fieldNumVerticalTiles*tileLines+2,fieldNumHorizontalTiles*tileCols+2, 1+heightBuffer , widthBuffer);

	// the following loops are a bit complicated, due to ncurses
	// here is a breakdown of what they do;
	//
	// for every tile, determine the number of hares and pumas not yet
	// represented on the tile, check if it is_only_water (i.e. Ocean)
	// and the amount of land that needs to be drawn
	//
	// the tile is then drawn systematically;
	//
	// if the tile is_only_water, then set the color to blue
	// and only whitespace is drawn
	//
	// if the tile contains land, then each segment of the tile is drawn
	// green, until the ratio of land in the tile is achieved, and the 
	// rest are drawn as wetlands
	//
	// similarly, the symbols 'H' (hares), 'P' (pumas) and '~' (half a hare or puma)
	// are used to represent the number of each animal on the tile, until
	// the full number is represented, and then the rest is printed as 
	// whitespace
	//
	// the borders of each tile are also drawn as whitespaces, to distinguish
	// one tile from another
	

	for(y = 0; y < fieldNumVerticalTiles; y++)
	{
		for(x = 0; x < fieldNumHorizontalTiles; x++)
		{
			hares_unrepresented_in_tile= fieldtile[x+fieldNumVerticalTiles*y].hare;
			pumas_unrepresented_in_tile= fieldtile[x+fieldNumVerticalTiles*y].puma;

			bool is_only_water = fieldtile[x+fieldNumVerticalTiles*y].is_only_water;
			draw_land = fieldtile[x+fieldNumVerticalTiles*y].land_count*(tileLines*tileCols/(double)fieldtile[x+fieldNumVerticalTiles*y].area);
			for(int j=1; j<=tileLines/2; j++)
			{
				for(int i=1; i<=tileCols; i++)
				{
					if(is_only_water)
					{
						wattron(field, COLOR_PAIR(1)); // turn on ocean colors
					}
					else if(draw_land > 0)
					{
						wattron(field, COLOR_PAIR(2));	// turn on land/hare colors
					}
					else
					{
						wattron(field, COLOR_PAIR(4));	// turn on wetland/hare colors
					}
					wattron(field, A_BOLD);
					if(j==1 || i==1 || i==tileCols)
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, " ");
					}
					else if(hareSymbolWorth == 0)
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, "#");
					}
					else if(hares_unrepresented_in_tile>= 2*hareSymbolWorth)
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, "H");
						hares_unrepresented_in_tile-= 2*hareSymbolWorth;
					}
					else if(hares_unrepresented_in_tile>= hareSymbolWorth)
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, "~");
						hares_unrepresented_in_tile-= hareSymbolWorth;
					}
					else
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, " ");
					}
					--draw_land;
				}
			}
			for(int j=tileLines/2+1; j<=tileLines; j++)
			{
				for(int i=1; i<=tileCols; i++)
				{
					if(is_only_water)
					{
						wattron(field, COLOR_PAIR(1));	// turn on ocean colors
					}
					else if(draw_land > 0)
					{
						wattroff(field,COLOR_PAIR(2));	// turn off land/hare colors
						wattron(field, COLOR_PAIR(3));	// turn on land/puma colors
					}
					else
					{
						wattroff(field, COLOR_PAIR(4)); // turn off wetlands/hare colors
						wattron(field, COLOR_PAIR(5));	// turn on wetlands/puma colors
					}
					if(j==tileLines || i==1 || i==tileCols)
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, " ");
					}
					else if(pumaSymbolWorth == 0)
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, "#");
					}
					else if(pumas_unrepresented_in_tile>= 2*pumaSymbolWorth)
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, "P");
						pumas_unrepresented_in_tile-= 2*pumaSymbolWorth;
					}
					else if(pumas_unrepresented_in_tile>= pumaSymbolWorth)
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, "~");
						pumas_unrepresented_in_tile-= pumaSymbolWorth;
					}
					else
					{
						mvwprintw(field, tileLines*y+j, tileCols*x+i, " ");
					}
				}
			}
			if(is_only_water)
			{
				wattroff(field, COLOR_PAIR(1)); // turn off ocean colors
			}
			else if(draw_land > 0)
			{
				wattroff(field,COLOR_PAIR(3));	// turn off land/puma colors
			}
			else
			{
				wattroff(field, COLOR_PAIR(5));	// turn off wetlands/hare colors
			}
			wattroff(field, A_BOLD);	
		}
	}
	set_title(field, "FIELD");
}

// draw the title (in bold) of a given window in the center top position
void NcursesField::set_title(WINDOW* win, string title)
{
	int x,y;
	getmaxyx(win, y, x);		// gets size of the window
	box(win, 0, 0);
	wattron(win, A_BOLD); 	// turn on writing in bold
	mvwprintw(win, 0, (x-title.length())/2, title.c_str());
	wattroff(win, A_BOLD); 	// turn off writing in bold
}

// sets the number of vertical/horizontal tiles to the largest amount that will fit on the screen,
// which, at the same time, isn't larger than the actual size of the board
void NcursesField::set_field_window_size()
{
	fieldNumHorizontalTiles = (3*COLS/4-1)/tileCols;	
	fieldNumVerticalTiles = (LINES-2)/tileLines;			
	size_t maxNumberOfTilesVisible = min(fieldNumVerticalTiles, fieldNumHorizontalTiles);

	fieldNumHorizontalTiles = min(maxNumberOfTilesVisible, (board->get_width()-2));
	fieldNumVerticalTiles = min(maxNumberOfTilesVisible, (board->get_height()-2));
	
	widthBuffer = (3*COLS/4-1-fieldNumHorizontalTiles*tileCols)/2;
	heightBuffer = (LINES-2-fieldNumVerticalTiles*tileLines)/2;

	set_field_tile_sizes();
}

// tells each tile the range over which it spans
void NcursesField::set_field_tile_sizes()
{	
	endwin();
	size_t x=1, y=1;
	size_t x_range = max((size_t) 1,board->get_width()/fieldNumHorizontalTiles);
	size_t y_range = max((size_t) 1,board->get_height()/fieldNumVerticalTiles);
	for(int j=0; j<fieldNumVerticalTiles;j++)
	{
		for(int i=0; i<fieldNumHorizontalTiles;i++)
		{	
			int x_max =  min(board->get_width()-1, x+x_range);
			int y_max =  min(board->get_height()-1, y+y_range);
			fieldtile.push_back(FieldTile(board, x, y, x_max, y_max));
			x += x_range;
		}
		y += y_range;
		x = 1;
	}
}

// opens a prompt to see if the use actually wants to quit
// remains until users enter y/Y/n/N
void NcursesField::quit_program()
{
	string quit_message = "Are you sure you want to quit? y/n";	
	quit = newwin(3, quit_message.length()+4, (LINES-3)/2 , (COLS-quit_message.length()-4)/2);
	mvwprintw(quit, 1, 2, quit_message.c_str());
	box(quit, 0,0);
	wrefresh(quit);
	int c = getch();
	while(true)
	{
		if(c == 110 || c == 78)
		{
			quit = newwin(3, quit_message.length()+4, (LINES-3)/2, (COLS-quit_message.length()-4)/2);
			wrefresh(quit);
			wrefresh(field);
			wrefresh(statistics);
			wrefresh(input);
			wrefresh(key);
			refresh();
			break;
		}
		else if(c == 121 || c == 89)
		{
			endwin();
			exit(0);
		}
		c = getch();
	}
}

// counts the number of animals in each tile 
double NcursesField::count_animals_in_tiles()
{
	for(int k = 0; k<fieldtile.size(); k++)
	{
		double hare_count = 0;
		double puma_count = 0;
		for(int j=fieldtile[k].y_min; j<fieldtile[k].y_max; j++)
		{
			for(int i=fieldtile[k].x_min; i<fieldtile[k].x_max; i++)
			{
				hare_count += (*fieldtile[k].board)(i,j).hare;
				puma_count += (*fieldtile[k].board)(i,j).puma;
			}
		}
		fieldtile[k].hare = hare_count;
		fieldtile[k].puma = puma_count;
	}
}
// updates the entire board
// if user presses q/Q opens quitting prompt
// if user presses p/P, pauses program until they repress
void NcursesField::update(double simulation_time)
{
	update_statistics(simulation_time);
	count_animals_in_tiles();
	update_field(simulation_time);
	update_key();
	update_input();
	wrefresh(field);
	wrefresh(statistics);
	wrefresh(key);
	wrefresh(input);
	refresh();
	if(simulation_time < options->time_step){return;}	
	int c = getch();

	if(c == 113 || c == 81)
	{
		quit_program();
	}
	if(c == 112 || c == 80)
	{
		c = 0;
		while(!(c == 112 || c == 80) )
		{
			set_title(field, "PAUSED");
			wrefresh(field);
			c = getch();
			if(c == 113)
			{
				quit_program();
			}
		};
	}
	while(clock() <= old_time + delay){}
	old_time = clock();
}


