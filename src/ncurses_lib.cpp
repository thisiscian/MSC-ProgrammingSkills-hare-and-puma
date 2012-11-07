#include "ncurses_lib.h"

using namespace std;
// Constructor for ncursesfield, sets sizes
NcursesField::NcursesField(Board<Tile>& board_in, int delay_in, int x, int y)
{
	board = &board_in;
	initialise_ncurses();
	tileLine = x;
	tileCols = y;
	set_field_window_size();
	stats.init(*board);
	delay = delay_in*1000;
	old_time = clock();
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
 	init_pair(4,COLOR_BLACK,COLOR_CYAN); 
 	init_pair(5,COLOR_WHITE,COLOR_CYAN); 

	// removes the cursor and any keypresses the user makes
	noecho();
	curs_set(0);
	halfdelay(1);

	keypad(stdscr, TRUE);
}

// resets input window: deletes old window, and redraws the entire window
void NcursesField::update_input()
{
	int l = 1;
	delwin(input);
	input = newwin(4,COLS/4-1, LINES-5, 3*COLS/4-1);
	set_title(input, "INPUT");
	
	mvwprintw(input, l, 1, " q/Q  ");
	mvwprintw(input, l, 7, " - quits the program");
	++l;	
	mvwprintw(input, l, 1, " p/P  ");
	mvwprintw(input, l, 7, " - pause and unpause");
	++l;	

	wrefresh(input);

}

// resets statistics window: deletes old window, redraws new window, recalculates and displays statistics
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

	// if the time is very close to zero, the average density should not be displayed
	text.str("");
	text << "Average Hare Density: " << stats.get_hare_average() << endl;
	if(time < pow(10,-10))
	{	
		for(int i=1; i<=text.str().length(); i++)
		{	
			mvwprintw(statistics, l, i, " ");
		}
	}
	else
	{
		mvwprintw(statistics, l, 1, text.str().c_str());
	}
	l++;

	// as above	
	text.str("");
	text << "Average Puma Density: " << stats.get_puma_average() << endl;
	if(time < pow(10,-10))
	{	
		for(int i=1; i<=text.str().length(); i++)
		{	
			mvwprintw(statistics, l, i, " ");
		}
	}
	else
	{
		mvwprintw(statistics, l, 1, text.str().c_str());
	}

	set_title(statistics, "STATISTICS");
}

double NcursesField::get_hare_max()
{
	int max = 0;
	for(int i=1; i<block.size(); i++)
	{
		if(block[max].hare <  block[i].hare){max = i;}
	}
	return block[max].hare;
}

double NcursesField::get_puma_max()
{
	int max = 0;
	for(int i=1; i<block.size(); i++)
	{
		if(block[max].puma <  block[i].puma){max = i;}
	}
	return block[max].puma;
}

void NcursesField::get_symbol_worth()
{
	//each symbol is a proportion of the maximum number of animals	
	hareSymbolWorth = get_hare_max()/((tileCols-2)*(tileLine-2));
	pumaSymbolWorth = get_puma_max()/((tileCols-2)*(tileLine-2));
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

void NcursesField::update_field(double time)
{
	int x, y, draw_land;
	int width = board->get_width();
	int height = board->get_height();
	double val;

	delwin(field);
	field = newwin(fieldNumVerticalTiles*tileLine+2,fieldNumHorizontalTiles*tileCols+2, 1+heightBuffer , widthBuffer);
	for(y = 0; y < fieldNumVerticalTiles; y++)
	{
		for(x = 0; x < fieldNumHorizontalTiles; x++)
		{
			val = block[x+fieldNumVerticalTiles*y].hare;
			bool is_fully_water = block[x+fieldNumVerticalTiles*y].is_fully_water;
			draw_land = block[x+fieldNumVerticalTiles*y].land_count*(tileLine*tileCols/(double)block[x+fieldNumVerticalTiles*y].total);
			for(int j=1; j<=tileLine/2; j++)
			{
				for(int i=1; i<=tileCols; i++)
				{
					if(is_fully_water)
					{
						wattron(field, COLOR_PAIR(1));	
					}
					else if(draw_land > 0)
					{
						wattron(field, COLOR_PAIR(2));	
					}
					else
					{
						wattron(field, COLOR_PAIR(4));	
					}
					wattron(field, A_BOLD);
					if(j==1 || i==1 || i==tileCols)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, " ");
					}
					else if(hareSymbolWorth == 0)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "#");
					}
					else if(val >= 2*hareSymbolWorth)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "H");
						val -= 2*hareSymbolWorth;
					}
					else if(val >= hareSymbolWorth)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "~");
						val -= hareSymbolWorth;
					}
					else
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, " ");
					}
					--draw_land;
				}
			}
			val = block[x+fieldNumVerticalTiles*y].puma;
			for(int j=tileLine/2+1; j<=tileLine; j++)
			{
				for(int i=1; i<=tileCols; i++)
				{
					if(is_fully_water)
					{
						wattron(field, COLOR_PAIR(1));	
					}
					else if(draw_land > 0)
					{
						wattroff(field,COLOR_PAIR(2));
						wattron(field, COLOR_PAIR(3));	
					}
					else
					{
						wattroff(field, COLOR_PAIR(4));
						wattron(field, COLOR_PAIR(5));	
					}
					if(j==tileLine || i==1 || i==tileCols)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, " ");
					}
					else if(pumaSymbolWorth == 0)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "#");
					}
					else if(val >= 2*pumaSymbolWorth)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "P");
						val -= 2*pumaSymbolWorth;
					}
					else if(val >= pumaSymbolWorth)
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, "~");
						val -= pumaSymbolWorth;
					}
					else
					{
						mvwprintw(field, tileLine*y+j, tileCols*x+i, " ");
					}
				}
			}
			if(is_fully_water)
			{
				wattroff(field, COLOR_PAIR(1));
			}
			else if(draw_land > 0)
			{
				wattroff(field,COLOR_PAIR(3));
			}
			else
			{
				wattroff(field, COLOR_PAIR(5));
			}
			wattroff(field, A_BOLD);	
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
	fieldNumHorizontalTiles = (3*COLS/4-1)/tileCols;
	fieldNumVerticalTiles = (LINES-2)/tileLine;

	size_t maxNumberOfTilesVisible = min(fieldNumVerticalTiles, fieldNumHorizontalTiles);

	fieldNumHorizontalTiles = min(maxNumberOfTilesVisible, (board->get_width()-2));
	fieldNumVerticalTiles = min(maxNumberOfTilesVisible, (board->get_height()-2));
	
	widthBuffer = (3*COLS/4-1-fieldNumHorizontalTiles*tileCols)/2;
	heightBuffer = (LINES-2-fieldNumVerticalTiles*tileLine)/2;

	set_field_block_sizes();
	
}

void NcursesField::set_field_block_sizes()
{	
	size_t x=1, y=1;
	size_t x_range = max((size_t) 1,board->get_width()/fieldNumHorizontalTiles);
	size_t y_range = max((size_t) 1,board->get_height()/fieldNumVerticalTiles);
	for(int j=0; j<fieldNumVerticalTiles;j++)
	{
		for(int i=0; i<fieldNumHorizontalTiles;i++)
		{	
			int x_max =  min(board->get_width()-1, x+x_range);
			int y_max =  min(board->get_height()-1, y+y_range);
			block.push_back(FieldBlock(board, x, y, x_max, y_max));
			x += x_range;
		}
		y += y_range;
		x = 1;
	}
}

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

void NcursesField::update(double simulation_time)
{
	update_statistics(simulation_time);
	count_animals_in_blocks();
	update_field(simulation_time);
	update_key();
	update_input();
	wrefresh(field);
	wrefresh(statistics);
	wrefresh(key);
	wrefresh(input);
	refresh();
	if(simulation_time < pow(10,-10)){return;}	
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

FieldBlock::FieldBlock(Board<Tile>* board_in, size_t i, size_t j, size_t i_max, size_t j_max)
{
	is_fully_water = false;
	board = board_in;
	set_range(i,j,i_max,j_max);
	find_land_state();
	total = (i_max-i)*(j_max-j);
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
	land_count = 0;
	for(int j=y_min; j<y_max; j++)
	{
		for(int i=x_min; i<x_max; i++)
		{
			if((*board)(i,j).is_land()){land_count += 1.0;}
		}
	}
	if(land_count == 0){is_fully_water = true;}
}

double NcursesField::count_animals_in_blocks()
{
	for(int k = 0; k<block.size(); k++)
	{
		double hare_count = 0;
		double puma_count = 0;
		for(int j=block[k].y_min; j<block[k].y_max; j++)
		{
			for(int i=block[k].x_min; i<block[k].x_max; i++)
			{
				hare_count += (*block[k].board)(i,j).hare;
				puma_count += (*block[k].board)(i,j).puma;
			}
		}
		block[k].hare = hare_count;
		block[k].puma = puma_count;
	}
}
