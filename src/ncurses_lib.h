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
#include "output.h"
#include "test_field.h"
#include "options.h"
#include "update.h"

class FieldBlock
{
	public:
	FieldBlock(Board<Tile>* board_in, size_t x, size_t y, size_t x_max, size_t y_max);
	void find_land_state();
	double hare_count();
	double puma_count();
	int land_count;
	size_t x_min;
	size_t y_min;
	size_t x_max;
	size_t y_max;
	double hare;
	double puma;
	Board<Tile>* board;
	void set_range(size_t x, size_t y, size_t x_max, size_t y_max);
	int total;
	private:
};

class NcursesField
{
	public:
	NcursesField(Board<Tile>& board, int tileLine, int tileCols);
	void update(double time);
	int delay;

	private:
	WINDOW* field;
	WINDOW* statistics;
	WINDOW* key;
	WINDOW* input;
	WINDOW* quit;

	BoardStatistics stats;
	Board<Tile>* board;
	std::vector<FieldBlock> block;
	clock_t old_time;
	double hareSymbolWorth;
	double pumaSymbolWorth;
	int tileLine;
	int tileCols;
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
	void set_field_block_sizes();
	double get_hare_max();
	double get_puma_max();
	double count_animals_in_blocks();
	void quit_program();
};
#endif
