#ifndef __NCURSES_LIB_H__
#define __NCURSES_LIB_H__

#include <ncurses.h>
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

class FieldBlock
{
	public:
	bool is_land();
	FieldBlock(Board<Tile>* board_in, size_t x, size_t y, size_t x_max, size_t y_max);
	void find_land_state();
	double hare_count();
	double puma_count();
	private:
	Board<Tile>* board;
	size_t x_min;
	size_t y_min;
	size_t x_max;
	size_t y_max;
	bool is_this_land;
	void set_range(size_t x, size_t y, size_t x_max, size_t y_max);
};

class NcursesField
{
	public:
	NcursesField(Board<Tile>& board, int tileLine, int tileCols);
	void update(double time);

	private:
	WINDOW* field;
	WINDOW* statistics;
	WINDOW* key;
	WINDOW* input;

	BoardStatistics stats;
	Board<Tile>* board;
	std::vector<FieldBlock> block;
	int symbolWorth;
	int tileLine;
	int tileCols;
	int fieldWindowWidth;
	int fieldWindowHeight;
	int displayableWidth;
	int displayableHeight;
	int widthBuffer;
	int heightBuffer;
	
	void set_field_block_sizes();
	void initialise_ncurses();
	void set_field_window_size();
	void set_title(WINDOW* win, std::string title);
	void get_symbol_worth();
	void update_field();
	void update_input();
	void update_statistics(double time);
	void update_key();
};
#endif
