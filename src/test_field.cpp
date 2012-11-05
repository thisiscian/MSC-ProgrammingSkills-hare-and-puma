#include "test_field.h"

using namespace std;

/* define a field with constant values for land, hare numbers and puma numbers */
void defineAllWater(Board<Tile>& field)
{
	int width = field.get_width();
	int height = field.get_height();
	int x, y;	
	for(x = 0; x < width; ++x)
	{
		for(y = 0; y < height; ++y)
		{
			field(x,y).make_water();
		}
	}
}

void defineConstantField(Board<Tile>& field)
{
	int width = field.get_width();
	int height = field.get_height();
	int x, y;	
	for(x = 0; x < width; ++x)
	{
		for(y = 0; y < height; ++y)
		{
			if(x == 0 || x == width-1 || y == 0 || y == height-1)
			{
				field(x,y).make_water();
				field(x, y).hare = 0.0;
				field(x, y).puma = 0.0;
			}
			else
			{
				field(x, y).make_land();
				field(x, y).hare = 1;
				field(x, y).puma = 1;
				if(x % 2 == 0 && y % 2 == 0)
				{
					field(x, y).make_water();
				}
			}
		}
	}
}

/* define a field with linear values for land, hare numbers and puma numbers */
void defineLinearField(Board<Tile>& field)
{
	int width = field.get_width();
	int height = field.get_height();
	int x, y;	
	for(x = 0; x < width; ++x)
	{
		for(y = 0; y < height; ++y)
		{
			if(x == 0 || x == width-1 || y == 0 || y == height-1)
			{
				field(x,y).make_water();
				field(x, y).hare = 0.0;
				field(x, y).puma = 0.0;
			}
			else
			{
				field(x, y).make_land();
				field(x, y).hare = x-1;
				field(x, y).puma = y-1;
				if(x % 2 == 0 && y % 2 == 0)
				{
					field(x, y).make_water();
				}
			}
		}
	}
}
/* define a field with non linear values for land, hare numbers and puma numbers */
void defineGaussian(Board<Tile>& field)
{
	int width = field.get_width();
	int height = field.get_height();
	int x, y;	
	for(x = 0; x < width; ++x)
	{
		for(y = 0; y < height; ++y)
		{
			field(x,y).make_land();
			field(x,y).hare = 255*exp(-pow(x-0.5*width,2)/(2*pow(0.25*width,2))-pow(y-0.5*height,2)/(2*pow(0.25*height,2)));
			field(x,y).puma = 2*exp(-pow(x-0.75*width,2)/(2*pow(0.25*width,2))-pow(y-height/2,2)/(2*pow(0.25*height,2)))+2*exp(-pow(x-0.25*width,2)/(2*pow(0.25*width,2))-pow(y-height/2,2)/(2*pow(0.25*height,2)));
		}
	}
}

void defineNonLinearField(Board<Tile>& field)
{
	int width = field.get_width();
	int height = field.get_height();
	int x, y;	
	for(x = 0; x < width; ++x)
	{
		for(y = 0; y < height; ++y)
		{
			if(x == 0 || x == width-1 || y == 0 || y == height-1)
			{
				field(x,y).make_water();
				field(x, y).hare = 0.0;
				field(x, y).puma = 0.0;
			}
			else
			{
				field(x, y).make_land();
				field(x, y).hare = max(cos(y+x), 0.0);
				field(x, y).puma = max(sin(y+x), 0.0);
				if(x % 2 == 0 && y % 2 == 0)
				{
					field(x, y).make_water();
				}
			}
		}
	}
}
