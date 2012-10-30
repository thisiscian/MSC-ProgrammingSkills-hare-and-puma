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
#include "tile.h"
#include "board.h"
#include "output.h"
#include "test_field.h"

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
	int tileLine;
	int tileCols;
	int windowWidth;
	int windowHeight;
	int displayableWidth;
	int displayableHeight;
	int widthBuffer;
	int heightBuffer;	
	
	void initialise_ncurses();
	void set_window_size();
	void set_title(WINDOW* win, std::string title);
	void update_field();
	void update_input();
	void update_statistics(double time);
	void update_key();
};

#endif
