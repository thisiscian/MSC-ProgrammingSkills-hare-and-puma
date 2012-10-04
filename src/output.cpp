//
//	This file is made by, and should be kept update by Cian Booth
//	this.is.cian@gmail.com
//

#include "output.h"

/*A function that recieves the populations of the hares and pumas, and outputs their values to the console*/
void output_to_console(board<tile> field, double time)
{
	int horizontalPosition, verticalPosition;
	int width = field.get_width();
	int height = field.get_height();

	cout << "Time: " << time << endl;
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
		if(field(horizontalPosition, 0).is_land())
		{
			cout << field(horizontalPosition, 0).hare <<	";" << field(horizontalPosition, 0).puma << flush;
		}
		else
		{
			cout << "~~~~~" << flush;
		}
		for(verticalPosition = 1; verticalPosition < height; ++verticalPosition)
		{
			if(field(horizontalPosition, verticalPosition).is_land())
			{
				cout << " | " << field(horizontalPosition, verticalPosition).hare <<	"; " << field(horizontalPosition, verticalPosition).puma << flush;
			}
			else
			{
				cout << " | ~~~~~ " << flush;
			}
		}
		cout << endl;
	}
	cout << endl;
}

/*A function that recieves the two populations and outputs a simple plain PPM file, named according to the current iteration to 'output/'*/
void write_simple_ppm(board<tile> field, double time)
{
	int horizontalPosition, verticalPosition;
	int width = field.get_width();
	int height = field.get_height();
	int maxValue = 255; // This is not a good choice, as values could well exceed it
	stringstream fileName;
	ofstream population;
	
	fileName << "output/population_" << time << ".ppm";
	population.open(fileName.str().c_str());
	
	population << "P3 " << width << " " << height << " " << maxValue << endl;
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
		for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
		{
			int red = 0, green = 0, blue = 0;
			red = (int) (field(horizontalPosition, verticalPosition).puma);
			green = (int) (field(horizontalPosition, verticalPosition).hare);
			if(!field(horizontalPosition, verticalPosition).is_land())
			{
				red = 0;
				green = 0;
				blue = 255;
			}
			population << red << " " << green << " " << blue << " " << flush;
		}
		population << endl;
	}
	
	population.close();
}

/* A function that writes a fancy looking PPM file */
void write_fancy_ppm(board<tile> field, double time)
{
	int horizontalPosition, verticalPosition;
	int width = field.get_width();
	int height = field.get_height();
	int maxValue = 255; // This is not a good choice, as values could well exceed it
	stringstream fileName;
	ofstream population;
	
	fileName << "output/population_" << time << ".ppm";
	population.open(fileName.str().c_str());
	
	population << "P3 " << width << " " << height << " " << maxValue << endl;
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
		for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
		{
			int red = 0, green = 0, blue = 0;
			red = (int) (field(horizontalPosition, verticalPosition).puma);
			green = (int) (field(horizontalPosition, verticalPosition).hare);
			if(!field(horizontalPosition, verticalPosition).is_land())
			{
				red = 0;
				green = 0;
				blue = 255;
			}
			population << red << " " << green << " " << blue << " " << flush;
		}
		population << endl;
	}
	
	population.close();
}
/*A function that outputs the mean values of the populations of the hares and pumas*/
/*void output_averages(board<tile> field, double time, double timeStep)
{

	cout << "Mean Number of Hares (at time " << time << "): " << field.mean.hare << endl;
	cout << "Mean Number of Pumas (at time " << time << "): " << field.mean.puma << endl;
	cout << endl;
}
*/
