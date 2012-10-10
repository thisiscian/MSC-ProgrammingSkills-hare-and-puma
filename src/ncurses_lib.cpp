#include "ncurses_lib.h"
#include <string>

void initialise_ncurses()
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

void set_title(WINDOW* win, string title)
{
	int x,y;
	getmaxyx(win, y, x);
	box(win, 0, 0);
	wattron(win, A_BOLD);
	mvwprintw(win, 0, (x-title.length())/2, title.c_str());
	wattroff(win, A_BOLD);
	wrefresh(win);
}

void set_statistics(WINDOW* win, Board<Tile>& field, BoardStatistics& stats, double time)
{
	stringstream text;
	set_title(win, "STATISTICS");
	stats.trawl_for_statistics(field, time);
	
	text.str("");
	text << "Total Density of Hares: " << stats.get_hare_total() << endl;
	mvwprintw(win, 1, 1, text.str().c_str());
	
	text.str("");
	text << "Total Density of Pumas: " << stats.get_puma_total() << endl;
	mvwprintw(win, 2, 1, text.str().c_str());

	text.str("");
	text << "Largest Density of Hares: " << stats.get_hare_max() << endl;
	mvwprintw(win, 3, 1, text.str().c_str());

	text.str("");
	text << "Largest Density of Pumas: " << stats.get_puma_max() << endl;
	mvwprintw(win, 4, 1, text.str().c_str());

	text.str("");
	text << "Average Hare Density: " << stats.get_hare_average() << endl;
	if(time < pow(10,-10))
	{	
		for(int i=1; i<=text.str().length(); i++)
		{	
			mvwprintw(win, 5, i, " ");
		}
	}
	else
	{
		mvwprintw(win, 5, 1, text.str().c_str());
	}
	
	text.str("");
	text << "Average Puma Density: " << stats.get_puma_average() << endl;
	if(time < pow(10,-10))
	{	
		for(int i=1; i<=text.str().length(); i++)
		{	
			mvwprintw(win, 5, i, " ");
		}
	}
	else
	{
		mvwprintw(win, 6, 1, text.str().c_str());
	}
	wrefresh(win);
}

void set_key(WINDOW* win, BoardStatistics& stats, int tileCols, int tileLine)
{
	int l = 1;
	stringstream text;
	double hareSymbolWorth = stats.get_hare_max()/(2*(tileLine-2)*(tileCols-2)-1);
	double pumaSymbolWorth = stats.get_puma_max()/(2*(tileLine-2)*(tileCols-2)-1);
	set_title(win, "KEY");

	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, l, 1, "   ");
	wattroff(win, COLOR_PAIR(2));
	mvwprintw(win, l, 5, " - Land");
	++l;	

	wattron(win, COLOR_PAIR(1));
	mvwprintw(win, l, 1, " ~ ");
	wattroff(win, COLOR_PAIR(1));
	mvwprintw(win, l, 5, " - Water");
	++l;	
	++l;	

	text.str("");
	text << " - 0-" << hareSymbolWorth << " Hares";
	wattron(win, A_BOLD);
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, l, 1, "   ");
	wattroff(win, COLOR_PAIR(2));
	wattroff(win, A_BOLD);
	mvwprintw(win, l, 5, text.str().c_str());
	++l;	

	wattron(win, COLOR_PAIR(1));
	text.str("");
	text << " - " << hareSymbolWorth << "-"<< 2*hareSymbolWorth << " Hares";
	wattron(win, A_BOLD);
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, l, 1, " h ");
	wattroff(win, COLOR_PAIR(2));
	wattroff(win, A_BOLD);
	mvwprintw(win, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << 2*hareSymbolWorth << " Hares";
	wattron(win, A_BOLD);
	wattron(win, COLOR_PAIR(2));
	mvwprintw(win, l, 1, " H ");
	wattroff(win, COLOR_PAIR(2));
	wattroff(win, A_BOLD);
	mvwprintw(win, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - 0-" << pumaSymbolWorth << " Pumas";
	wattron(win, A_BOLD);
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, l, 1, " P ");
	wattroff(win, COLOR_PAIR(3));
	wattroff(win, A_BOLD);
	mvwprintw(win, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << pumaSymbolWorth << "-"<< 2*pumaSymbolWorth << " Pumas";
	wattron(win, A_BOLD);
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, l, 1, " p ");
	wattroff(win, COLOR_PAIR(3));
	wattroff(win, A_BOLD);
	mvwprintw(win, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << " - " << 2*pumaSymbolWorth << " Pumas";
	wattron(win, A_BOLD);
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, l, 1, " P ");
	wattroff(win, COLOR_PAIR(3));
	wattroff(win, A_BOLD);
	mvwprintw(win, l, 5, text.str().c_str());
	++l;	

	text.str("");
	text << "Tile Width: " << tileCols << " Columns";	
	mvwprintw(win, l, 1, text.str().c_str());
	++l;	
	
	text.str("");
	text << "Tile Height: " << tileLine << " Lines";	
	mvwprintw(win, l, 1, text.str().c_str());
	++l;	
	
	wrefresh(win);
}

void print_field(WINDOW * win, Board<Tile>&field, BoardStatistics& stats, int tileCols, int tileLine)
{
	int horizontalPosition, verticalPosition;
	int width = field.get_width();
	int height = field.get_height();
	double symbolWorth;
	for(horizontalPosition = 1; horizontalPosition < width-1; ++horizontalPosition)
	{
		for(verticalPosition = 1; verticalPosition < height-1; ++verticalPosition)
		{
			if(!field(horizontalPosition, verticalPosition).is_land())
			{
				wattron(win, A_BOLD);
				for(int i=1; i<=tileLine; i++)
				{
					for(int j=1; j<=tileCols;j++)
					{
						if(i==1 || i==tileLine || j==1 || j==tileCols)
						{
							wattron(win, COLOR_PAIR(1));
							mvwprintw(win, tileLine*(verticalPosition-1)+i, tileCols*(horizontalPosition-1)+j, " ");
							wattroff(win, COLOR_PAIR(1));
						}
						else
						{
							wattron(win, COLOR_PAIR(1));
							mvwprintw(win, tileLine*(verticalPosition-1)+i, tileCols*(horizontalPosition-1)+j, "~");
							wattroff(win, COLOR_PAIR(1));
						}
					}
				}
				wattroff(win,A_BOLD);	
			}
			else
			{
				wattron(win, A_BOLD);
				symbolWorth = stats.get_hare_max()/((tileLine-2)*(tileCols-2)*2+1);
				double val = field(horizontalPosition,verticalPosition).hare;
				for(int i=1; i<= tileLine/2; i++)
				{
					for(int j=1; j<=tileCols; j++)
					{
						if(i == 1 || j == 1 || j==tileCols)
						{
							wattron(win, COLOR_PAIR(2));
							mvwprintw(win, tileLine*(verticalPosition-1)+i, tileCols*(horizontalPosition-1)+j, " ");
							wattroff(win, COLOR_PAIR(2));
						}
						else if(val >= 2*symbolWorth)
						{
							wattron(win, COLOR_PAIR(2));
							mvwprintw(win, tileLine*(verticalPosition-1)+i, tileCols*(horizontalPosition-1)+j, "H");
							val -= 2*symbolWorth;
							wattroff(win, COLOR_PAIR(2));
						}
						else if(val >= symbolWorth)
						{
							wattron(win, COLOR_PAIR(2));
							mvwprintw(win, tileLine*(verticalPosition-1)+i, tileCols*(horizontalPosition-1)+j, "h");
							val -= symbolWorth;
							wattroff(win, COLOR_PAIR(2));
						}
						else
						{
							wattron(win, COLOR_PAIR(2));
							mvwprintw(win, tileLine*(verticalPosition-1)+i, tileCols*(horizontalPosition-1)+j, " ");
							wattroff(win, COLOR_PAIR(2));
						}
					}
				}
				symbolWorth = stats.get_puma_max()/(2*(tileLine-2)*(tileCols-2)+1);
				val = field(horizontalPosition,verticalPosition).puma;
				for(int i=1; i<= tileLine/2; i++)
				{
					for(int j=1; j<=tileCols; j++)
					{
						if(i == tileLine/2 || j == 1 || j==tileCols)
						{
							wattron(win, COLOR_PAIR(3));
							mvwprintw(win, tileLine*(verticalPosition-1)+i+tileLine/2, tileCols*(horizontalPosition-1)+j, " ");
							wattroff(win, COLOR_PAIR(3));
						}
						else if(val >= 2*symbolWorth)
						{
							wattron(win, COLOR_PAIR(3));
							mvwprintw(win, tileLine*(verticalPosition-1)+i+tileLine/2, tileCols*(horizontalPosition-1)+j, "P");
							val -= 2*symbolWorth;
							wattroff(win, COLOR_PAIR(3));
						}
						else if(val >= symbolWorth)
						{
							wattron(win, COLOR_PAIR(3));
							mvwprintw(win, tileLine*(verticalPosition-1)+i+tileLine/2, tileCols*(horizontalPosition-1)+j, "p");
							val -= symbolWorth;
							wattroff(win, COLOR_PAIR(3));
						}
						else
						{
							wattron(win, COLOR_PAIR(3));
							mvwprintw(win, tileLine*(verticalPosition-1)+i+tileLine/2, tileCols*(horizontalPosition-1)+j, " ");
							wattroff(win, COLOR_PAIR(3));
						}
					}
				}
				wattroff(win, A_BOLD);
					/*
				mvwprintw(win, 4*(verticalPosition-1)+1, 6*(horizontalPosition-1)+1, "      ");
				mvwprintw(win, 4*(verticalPosition-1)+4, 6*(horizontalPosition-1)+1, "      ");
				mvwprintw(win, 4*(verticalPosition-1)+2, 6*(horizontalPosition-1)+1, value.str().c_str());
				
			  value.str("");
				value << setw(2) << " P" << setw(3) << floor(field(horizontalPosition,verticalPosition).puma) << " ";
				wattron(win, COLOR_PAIR(3));
				mvwprintw(win, 4*(verticalPosition-1)+3, 6*(horizontalPosition-1)+1, value.str().c_str());
				mvwprintw(win, 4*(verticalPosition-1)+4, 6*(horizontalPosition-1)+1, value.str().c_str());
				wattroff(win, COLOR_PAIR(3));
				wattroff(win, A_BOLD);*/
			}
		}
	}
}
