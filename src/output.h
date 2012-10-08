#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "board.h"
#include "tile.h"
using namespace std;

class Color
{
	public:
	Color(){};
	Color(int red, int green, int blue)
	{
		set_color(red, green, blue);
	}
	
	void operator()(int red, int green, int blue)
	{
		set_color(red, green, blue);
	}

	string col()
	{
		stringstream color;
		color << r << " " << g << " " << b;
		return color.str();
	}

	private:
	int r, g, b;
	void set_color(int red, int green, int blue)
	{
		r = red;
		g = green;
		b = blue;
	}	
} borderColor(40,40,40);

void output_to_console(Board<Tile> field, double time);
void write_ppm(Board<Tile> field, double time);
void write_adjustable_ppm(Board<Tile> field, double time, int tileSize, int borderWidth);
void output_averages(Board<Tile> field, double time);

