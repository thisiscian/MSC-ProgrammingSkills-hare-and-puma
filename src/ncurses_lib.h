#include <ncurses.h>
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
#include "tile.h"
#include "board.h"
#include "output.h"

void initialise_ncurses();
void print_field(WINDOW* win, Board<Tile>& field, BoardStatistics& stats, int tileCols, int tileLine);
void set_title(WINDOW* win, string title);
void set_key(WINDOW* win, BoardStatistics& stats, int tileCols, int tileLine);
void set_statistics(WINDOW* win, Board<Tile>& field, BoardStatistics& stats, double time);
