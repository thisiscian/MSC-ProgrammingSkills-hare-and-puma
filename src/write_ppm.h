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
#include <sys/stat.h>
#include <sys/types.h>
#include <ctime>

void create_output_directory(std::string directory_name);
void write_ppm(Board<Tile>& tile, double time, std::string output_directory);
void write_adjustable_ppm(Board<Tile>& tile, double time, int tileSize, int borderWidth, std::string title, std::string output_directory);
void output_averages(Board<Tile>& tile, double time);

#endif
