#ifndef __NCURSES_LIB_H__
#define __NCURSES_LIB_H__

#include <ncurses.h>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <string>

#include "tile.h"
#include "board.h"
#include "options.h"
#include "statistics.h"
#include "update.h"
#include "field_tile.h"

class NcursesField
{
	public:
	NcursesField(Board<Tile>& board, Options& options, int tileLines, int tileCols);
	void update(double time);
	#ifdef GUI_TEST
		std::vector<FieldTile> fieldtile;
		double count_animals_in_tiles();
		double get_hare_max();
		double get_puma_max();
	#endif
	int delay;

	private:
	WINDOW* field;
	WINDOW* statistics;
	WINDOW* key;
	WINDOW* input;
	WINDOW* quit;

	BoardStatistics stats;
	Board<Tile>* board;
	Options* options;
	#ifndef GUI_TEST
		std::vector<FieldTile> fieldtile;
		double count_animals_in_tiles();
		double get_hare_max();
		double get_puma_max();
	#endif
	
	clock_t old_time;	// for refreshing the gui

	double hareSymbolWorth;	// how much each symbol representing
	double pumaSymbolWorth;	// each species is worth

	int tileLines;	// height and width
	int tileCols;		// of tile respectively

	int fieldNumHorizontalTiles;
	int fieldNumVerticalTiles;
	int displayableWidth;
	int displayableHeight;
	int widthBuffer;
	int heightBuffer;
	
	void initialise_ncurses();
	void set_field_window_size();
	void set_title(WINDOW* win, std::string title);
	void get_symbol_worth();
	void update_field(double time);
	void update_input();
	void update_statistics(double time);
	void update_key();
	void set_field_tile_sizes();
	void quit_program();
};

#endif
