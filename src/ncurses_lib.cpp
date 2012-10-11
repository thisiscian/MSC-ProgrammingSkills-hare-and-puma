#include "ncurses_lib.h"
#include <string>

NcursesField::NcursesField(Board<Tile>& board_in, int x, int y)
{
	board = &board_in;
	initialise_ncurses();
	tileLine = x;
	tileCols = y;
	set_window_size();
	stats.init(*board);
	update(0.0);
}

void NcursesField::initialise_ncurses()
{
	initscr();
	start_color(); 
 	init_pair(1,COLOR_CYAN,COLOR_BLUE); 
 	init_pair(2,COLOR_BLACK,COLOR_GREEN); 
 	init_pair(3,COLOR_WHITE,COLOR_GREEN); 
 	init_pair(4,COLOR_BLACK,COLOR_CYAN); 

	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
}

void NcursesField::update_input()
{
	delwin(input);
	input = newwin(LINES/2+1,COLS/4-1, LINES/2, 3*COLS/4-1);
	set_title(input, "INPUT");
}

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

void NcursesField::set_window_size()
{

	windowWidth = COLS/2-1;
	windowHeight = LINES-2;

	size_t maxNumberOfTilesVisible = min(windowHeight/tileLine, windowWidth/tileCols);

	windowWidth = min(tileCols*maxNumberOfTilesVisible+2, tileCols*(board->get_width()-2)+2);
	windowHeight = min(tileLine*maxNumberOfTilesVisible+2, tileLine*(board->get_height()-2)+2);
	
	widthBuffer = (COLS/2-1-windowWidth)/2;
	heightBuffer = (LINES-2-windowHeight)/2;
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

void NcursesField::update_key()
{
	int l = 1;
	stringstream text;
	double hareSymbolWorth = stats.get_hare_max()/(2*(tileLine-2)*(tileCols-2)-1);
	double pumaSymbolWorth = stats.get_puma_max()/(2*(tileLine-2)*(tileCols-2)-1);
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
	mvwprintw(key, l, 1, " h ");
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
	mvwprintw(key, l, 1, " p ");
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

void NcursesField::update_field()
{
	int x, y;
	int width = board->get_width();
	int height = board->get_height();
	double symbolWorth;
	delwin(field);
	field = newwin(windowHeight,windowWidth, 1+heightBuffer , widthBuffer);
	for(x = 1; x < width-1; ++x)
	{
		for(y = 1; y < height-1; ++y)
		{
			if(!(*board)(x,y).is_land())
			{
				wattron(field, A_BOLD);
				for(int i=1; i<=tileLine; i++)
				{
					for(int j=1; j<=tileCols;j++)
					{
						if(i==1 || i==tileLine || j==1 || j==tileCols)
						{
							wattron(field, COLOR_PAIR(1));
							mvwprintw(field, tileLine*(y-1)+i, tileCols*(x-1)+j, " ");
							wattroff(field, COLOR_PAIR(1));
						}
						else
						{
							wattron(field, COLOR_PAIR(1));
							mvwprintw(field, tileLine*(y-1)+i, tileCols*(x-1)+j, "~");
							wattroff(field, COLOR_PAIR(1));
						}
					}
				}
				wattroff(field,A_BOLD);	
			}
			else
			{
				wattron(field, A_BOLD);
				symbolWorth = stats.get_hare_max()/((tileLine-2)*(tileCols-2)*2+1);
				double val = (*board)(x,y).hare;
				for(int i=1; i<= tileLine/2; i++)
				{
					for(int j=1; j<=tileCols; j++)
					{
						if(i == 1 || j == 1 || j==tileCols)
						{
							wattron(field, COLOR_PAIR(2));
							mvwprintw(field, tileLine*(y-1)+i, tileCols*(x-1)+j, " ");
							wattroff(field, COLOR_PAIR(2));
						}
						else if(val >= 2*symbolWorth)
						{
							wattron(field, COLOR_PAIR(2));
							mvwprintw(field, tileLine*(y-1)+i, tileCols*(x-1)+j, "H");
							val -= 2*symbolWorth;
							wattroff(field, COLOR_PAIR(2));
						}
						else if(val >= symbolWorth)
						{
							wattron(field, COLOR_PAIR(2));
							mvwprintw(field, tileLine*(y-1)+i, tileCols*(x-1)+j, "~");
							val -= symbolWorth;
							wattroff(field, COLOR_PAIR(2));
						}
						else
						{
							wattron(field, COLOR_PAIR(2));
							mvwprintw(field, tileLine*(y-1)+i, tileCols*(x-1)+j, " ");
							wattroff(field, COLOR_PAIR(2));
						}
					}
				}
				symbolWorth = stats.get_puma_max()/(2*(tileLine-2)*(tileCols-2)+1);
				val = (*board)(x,y).puma;
				for(int i=1; i<= tileLine/2; i++)
				{
					for(int j=1; j<=tileCols; j++)
					{
						if(i == tileLine/2 || j == 1 || j==tileCols)
						{
							wattron(field, COLOR_PAIR(3));
							mvwprintw(field, tileLine*(y-1)+i+tileLine/2, tileCols*(x-1)+j, " ");
							wattroff(field, COLOR_PAIR(3));
						}
						else if(val >= 2*symbolWorth)
						{
							wattron(field, COLOR_PAIR(3));
							mvwprintw(field, tileLine*(y-1)+i+tileLine/2, tileCols*(x-1)+j, "P");
							val -= 2*symbolWorth;
							wattroff(field, COLOR_PAIR(3));
						}
						else if(val >= symbolWorth)
						{
							wattron(field, COLOR_PAIR(3));
							mvwprintw(field, tileLine*(y-1)+i+tileLine/2, tileCols*(x-1)+j, "~");
							val -= symbolWorth;
							wattroff(field, COLOR_PAIR(3));
						}
						else
						{
							wattron(field, COLOR_PAIR(3));
							mvwprintw(field, tileLine*(y-1)+i+tileLine/2, tileCols*(x-1)+j, " ");
							wattroff(field, COLOR_PAIR(3));
						}
					}
				}
				wattroff(field, A_BOLD);
			}
		}
	}
	set_title(field, "FIELD");
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


