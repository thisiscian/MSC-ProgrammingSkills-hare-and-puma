#include <iostream>
#include <fstream>
#include <sstream>
#include "board.h"
#include "tile.h"
using namespace std;

void output_to_console(board<tile> field, double time);
void write_simple_ppm(board<tile> field, double time);
void write_fancy_ppm(board<tile> field, double time);
void output_averages(board<tile> field, double time);
