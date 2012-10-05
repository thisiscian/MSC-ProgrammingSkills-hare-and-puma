#include <iomanip>
#include <stdio.h>
#include <string>
#include "board.h"
#include "tile.h"
using namespace std;

class color
{
	public:
	color(){};
	color(int red, int green, int blue)
	{
		set_color(red, green, blue);
	}
	
	void operator()(int red, int green, int blue)
	{
		set_color(red, green, blue);
	}

	const char* col()
	{
		const char* new_color = get_color().c_str();
		return new_color;
	}

	private:
	int r, g, b;
	void set_color(int red, int green, int blue)
	{
		r = red;
		g = green;
		b = blue;
	}	
	
	string get_color()
	{
		char* buffer = new char[11];
		sprintf(buffer, "%03i %03i %03i", r, g, b);
		string color(buffer);
		return color;
	}

};

void output_to_console(board<tile> field, double time);
void write_simple_ppm(board<tile> field, double time);
void write_simple_adjustable_ppm(board<tile> field, double time, int tileSize, int borderWidth);
void write_fancy_ppm(board<tile> field, double time);
void output_averages(board<tile> field, double time);

