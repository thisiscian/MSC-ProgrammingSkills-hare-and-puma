#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include "board.h"
#include "tile.h"
#include "statistics.h"

void output_to_console(Board<Tile> field, double time);
void write_ppm(Board<Tile> field, int iteration);
void write_adjustable_ppm(Board<Tile> field, int iteration, int tileSize, int borderWidth, std::string title);
void output_averages(Board<Tile> field, double time);

#endif
