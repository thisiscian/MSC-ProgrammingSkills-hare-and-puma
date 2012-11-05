#include "ncurses_lib.h"

using namespace std;
// Constructor for ncursesfield, sets sizes
NcursesField::NcursesField(Board<Tile>& board_in, int x, int y)
{
	board = &board_in;
	initialise_ncurses();
	tileLine = x;
	tileCols = y;
	set_field_window_size();
	stats.init(*board);
	update(0.0);
}

void NcursesField::initialise_ncurses()
{
	initscr();
	// allows use of color, and sets the values of some initial colors
	start_color(); 
 	init_pair(1,COLOR_CYAN,COLOR_BLUE); 
 	init_pair(2,COLOR_BLACK,COLOR_GREEN); 
 	init_pair(3,COLOR_WHITE,COLOR_GREEN); 
 	init_pair(4,COLOR_BLACK,COLOR_BLUE); 
 	init_pair(5,COLOR_WHITE,COLOR_BLUE); 

	// removes the cursor and any keypresses the user makes
	noecho();
	curs_set(0);

	cbreak();
	keypad(stdscr, TRUE);
}

// resets input window: deletes old window, and redraws the entire window
void NcursesField::update_input()
{
	delwin(input);
	input = newwin(LINES/2+1,COLS/4-1, LINES/2, 3*COLS/4-1);
	set_title(input, "INPUT");
}

// resets statistics window: deletes old window, redraws new window, recalculates and displays statistics
void NcursesField::update_statistics(double time)
{
	stringstream text;
	stats.trawl_for_statistics(*board, time);

	delwin(statistics);	
	statistics = newwin(LINES/2-1,COLS/2-1, 1, COLS/2-1);
	text.str("");
	text << "Total Density of Hares: " << stats.get_hare_total() << endl;
	mvwprintw(statistics, 1, 1, text.str().c_str());
	
	text.str("");
	text << "Total Density of Pumas: " << stats.get_puma_total() << endl;
	mvwprintw(statistics, 2, 1, text.str().c_str());

	text.str("");
	text << "Largest Density of Hares: " << stats.get_hare_max() << endl;
	mvwprintw(statistics, 3, 1, text.str().c_str());

	text.str("");
	text << "Largest Density of Pumas: " << stats.get_puma_max() << endl;
	mvwprintw(statistics, 4, 1, text.str().c_str());

	// if the time is very close to zero, the average density should not be displayed
	text.str("");
	text << "Average Hare Density: " << stats.get_hare_average() << endl;
	if(time < pow(10,-10))
	{	
		for(int i=1; i<=text.str().length(); i++)
		{	
			mvwprintw(statistics, 5, i, " ");
		}
	}
	else
	{
		mvwprintw(statistics, 5, 1, text.str().c_str());
	}

	// as above	
	text.str("");
	text << "Average Puma Density: " << stats.get_puma_average() << endl;
	if(time < pow(10,-10))
	{	
		for(int i=1; i<=text.str().length(); i++)
		{	
			mvwprintw(statistics, 5, i, " ");
		}
	}
	else
	{
		mvwprintw(statistics, 6, 1, text.str().c_str());
	}

	set_title(statistics, "STATISTICS");
}

void NcursesField::get_symbol_worth()
{
	//each symbol is equal to the total amount of hares and pumas divided by the number of options there are
	symbolWorth = (stats.get_hare_total()+stats.get_puma_total())/((tileCols-2)*(tileLine-2)*4);
}

// draws a decription of what each key means
void NcursesField::update_key()
{
	int l = 1;
	stringstream text;
	get_symbol_worth();
	delwin(key);
	key = newwin(LINES/2+1,COLS/4-1, LINES/2, COLS/2-1);
	
	wattron(key, COLOR_PAIR(2));
	mvwprintw(key, l, 1, "   ");
	wattroff(key, COLOR_PAIR(2));
	mvwprintw(key, l, 5, " - Land");
	++l;	

	wattron(key, COLOR_PAIR(1));
	mvwprintw(key, l, 1, " ~ ");
	wattroff(key, COLOR_PAIR(1));
	mvwprintw(key, l, 5, " - Water");
	++l;	
	++l;	

	text.str("");
	text << " - 0-" << symbolWorth << " Hares";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(2));
	mvwprintw(key, l, 1, "   ");
	wattroff(key, COLOR_PAIR(2));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	wattron(key, COLOR_PAIR(1));
	text.str("");
	text << " - " << symbolWorth << "-"<< 2*symbolWorth << " Hares";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(2));
	mvwprintw(key, l, 1, " h ");
	wattroff(key, COLOR_PAIR(2));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << symbolWorth << " Hares";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(2));
	mvwprintw(key, l, 1, " H ");
	wattroff(key, COLOR_PAIR(2));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - 0-" << symbolWorth << " Pumas";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(3));
	mvwprintw(key, l, 1, "   ");
	wattroff(key, COLOR_PAIR(3));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << symbolWorth << "-"<< 2*symbolWorth << " Pumas";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(3));
	mvwprintw(key, l, 1, " p ");
	wattroff(key, COLOR_PAIR(3));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << 2*symbolWorth << " Pumas";
	wattron(key, A_BOLD);
	wattron(key, COLOR_PAIR(3));
	mvwprintw(key, l, 1, " P ");
	wattroff(key, COLOR_PAIR(3));
	wattroff(key, A_BOLD);
	mvwprintw(key, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << "Tile Width: " << tileCols << " Columns";	
	mvwprintw(key, l, 1, text.str().c_str());
	++l;	
	
	text.str("");
	text << "Tile Height: " << tileLine << " Lines";	
	mvwprintw(key, l, 1, text.str().c_str());
	++l;
	set_title(key, "KEY");
}

void NcursesField::update_field()
{
	int x, y;
	int width = board->get_width();
	int height = board->get_height();
	double val;

	delwin(field);
	field = newwin(fieldWindowHeight,fieldWindowWidth, 1+heightBuffer , widthBuffer);

	// for each element of the field, check if it's 'block' is mostly water or mostly land
	for(y = 0; y < fieldWindowHeight; y++)
	{
		for(x = 0; x < fieldWindowWidth; x++)
		{
			wattron(field, A_BOLD);
			if(block[x+fieldWindowHeight*y].is_land())
			{
				wattron(field, COLOR_PAIR(2));	
			}
			else
			{
				wattron(field, COLOR_PAIR(4));	
			}
			val = block[x+fieldWindowHeight*y].hare_count();
			for(int j=1; j<=tileLine/2; j++)
			{
				for(int i=1; i<=tileCols; i++)
				{
					if(j==1 || i==1 || i==tileCols)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, " ");
					}
					else if(val >= 2*symbolWorth)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "H");
						val -= 2*symbolWorth;
					}
					else if(val >= symbolWorth)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "~");
						val -= symbolWorth;
					}
					else
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, " ");
					}
				}
			}
			if(block[x+fieldWindowHeight*y].is_land())
			{
				wattroff(field,COLOR_PAIR(2));
				wattron(field, COLOR_PAIR(3));	
			}
			else
			{
				wattroff(field, COLOR_PAIR(4));
				wattron(field, COLOR_PAIR(5));	
			}
			val = block[x+fieldWindowHeight*y].hare_count();
			for(int j=tileLine/2+1; j<=tileLine; j++)
			{
				for(int i=1; i<=tileCols; i++)
				{
					if(j==tileLine || i==1 || i==tileCols)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, " ");
					}
					else if(val >= 2*symbolWorth)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "P");
						val -= 2*symbolWorth;
					}
					else if(val >= symbolWorth)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "~");
						val -= symbolWorth;
					}
					else
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, " ");
					}
				}
			}
		}
	}
	set_title(field, "FIELD");
}

void NcursesField::set_title(WINDOW* win, string title)
{
	int x,y;
	getmaxyx(win, y, x);
	box(win, 0, 0);
	wattron(win, A_BOLD);
	mvwprintw(win, 0, (x-title.length())/2, title.c_str());
	wattroff(win, A_BOLD);
}

void NcursesField::set_field_window_size()
{
	fieldWindowWidth = COLS/2-1;
	fieldWindowHeight = LINES-2;

	size_t maxNumberOfTilesVisible = min(fieldWindowHeight/tileLine, fieldWindowWidth/tileCols);

	fieldWindowWidth = min(tileCols*maxNumberOfTilesVisible+2, tileCols*(board->get_width()-2)+2);
	fieldWindowHeight = min(tileLine*maxNumberOfTilesVisible+2, tileLine*(board->get_height()-2)+2);
	
	widthBuffer = (COLS/2-1-fieldWindowWidth)/2;
	heightBuffer = (LINES-2-fieldWindowHeight)/2;
	
	size_t x=0, y=0;
	size_t x_range = max((size_t) 1,board->get_width()/fieldWindowWidth);
	size_t y_range = max((size_t) 1,board->get_height()/fieldWindowHeight);
	for(int j=0; j<fieldWindowWidth;j++)
	{
		for(int i=0; i<fieldWindowHeight;i++)
		{	
			int x_max =  min(board->get_width(), x+x_range);
			int y_max =  min(board->get_height(), y+y_range);
			block.push_back(FieldBlock(board, x, y, x_max, y_max));
			x += x_range;
		}
		y += y_range;
		x = 0;
	}
}

void NcursesField::update(double time)
{
	update_statistics(time);
	update_field();
	update_key();
	update_input();
	wrefresh(field);
	wrefresh(statistics);
	wrefresh(key);
	wrefresh(input);
	refresh();
}

FieldBlock::FieldBlock(Board<Tile>* board_in, size_t i, size_t j, size_t i_max, size_t j_max)
{
	board = board_in;
	set_range(i,j,i_max,j_max);
	find_land_state();
}

void FieldBlock::set_range(size_t i, size_t j, size_t i_max, size_t j_max)
{
	x_min = i;
	y_min = j;
	x_max = i_max;
	y_max = j_max;
}

void FieldBlock::find_land_state()
{
	int land_count = 0;
	for(int j=y_min; j<y_max; j++)
	{
		for(int i=x_min; i<x_max; i++)
		{
			if((*board)(i,j).is_land()){land_count++;}
		}
	}
	if(land_count >= (y_max-y_min)*(x_max-x_min)/2)
	{
		is_this_land = true;
	}
	else
	{
		is_this_land = false;
	}
}

double FieldBlock::hare_count()
{
	double count = 0;
	for(int j=y_min; j<y_max; j++)
	{
		for(int i=x_min; i<x_max; i++)
		{
			count += (*board)(i,j).hare;
		}
	}
	return count;
}

double FieldBlock::puma_count()
{
	double count = 0;
	for(int j=y_min; j<y_max; j++)
	{
		for(int i=x_min; i<x_max; i++)
		{
			count += (*board)(i,j).puma;
		}
	}
	return count;
}

bool FieldBlock::is_land()
{
	return is_this_land;
}
