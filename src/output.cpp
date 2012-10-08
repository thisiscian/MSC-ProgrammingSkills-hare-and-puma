//
//	This file is made by, and should be kept update by Cian Booth
//	this.is.cian@gmail.com
//

#include "output.h"

/*A function that recieves the populations of the hares and pumas, and outputs their values to the console*/
void output_to_console(Board<Tile> field, double time)
{
	int verticalPosition, horizontalPosition;
	int width = field.get_width();
	int height = field.get_height();

	cout << "Time: " << time << endl;
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
			cout << "----------" << flush;
	}
	cout << "-" << endl;
	for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
	{
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			if(field(horizontalPosition, verticalPosition).is_land())
			{
				cout << "| H" << field(horizontalPosition, verticalPosition).hare << " " << flush;
			}
			else
			{
				cout << "| ~~~~~~~ " << flush;
			}
		}
		cout << "|" << endl;
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			if(field(horizontalPosition, verticalPosition).is_land())
			{
				cout << "| P" << field(horizontalPosition, verticalPosition).puma << " " << flush;
			}
			else
			{
				cout << "| ~~~~~~~ " << flush;
			}
		}
		cout << "|" << endl;
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			cout << "----------" << flush;
		}
		cout << "-" << endl;
	}
	cout << endl;
}

/*A function that recieves the two populations and outputs a simple plain PPM file, named according to the current iteration to 'output/'*/
void write_ppm(Board<Tile> field, double time)
{
	write_adjustable_ppm(field, time, 1, 0);
}

void write_adjustable_ppm(Board<Tile> field, double time, int tileSize, int borderWidth)
{
	int verticalPosition, horizontalPosition;
	int width = field.get_width();
	int height = field.get_height();
	int maxValue = 255; // This is not a good choice, as values could well exceed it

	int drawingWidth = width*(borderWidth+tileSize)+borderWidth;
	int drawingHeight = height*(borderWidth+tileSize)+borderWidth;

	ofstream file;
	stringstream fileName;
	fileName << "output/population_" << time << ".ppm";
	file.open(fileName.str().c_str());
	
	file << "P3 " << drawingWidth << " " <<  drawingHeight << " " <<  maxValue << endl;
	for(verticalPosition = 0; verticalPosition < drawingHeight; ++verticalPosition)
	{
		for(horizontalPosition = 0; horizontalPosition < drawingWidth;  ++horizontalPosition)
		{
				for(int j=0; j<borderWidth; j++)
				{
					file << borderColor.col() << " " << flush;
				}
		}
		for(int i=0; i<tileSize; i++)
		{
			for(horizontalPosition = 0; horizontalPosition < drawingWidth;  ++horizontalPosition)
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
				for(int j=0; j<borderWidth; j++)
				{
					file << borderColor.col() << " " << flush;
				}
				
				for(int k=0; i<tileSize; k++)
				{
					file << red << " " <<  green << " " << blue << " " << flush;
				}
			}
			for(int j=0; j<borderWidth; j++)
			{
				file << borderColor.col() << " " << flush;
			}
		}
	}
	for(horizontalPosition = 0; horizontalPosition < drawingWidth;  ++horizontalPosition)
	{
		for(int j=0; j<borderWidth; j++)
		{
			file << borderColor.col() << " " << flush;
		}
	}
	file << endl;
	file.close();	
}

/*A function that outputs the mean values of the populations of the hares and pumas*/
/*void output_averages(Board<Tile> field, double time, double timeStep)
{

	cout << "Mean Number of Hares (at time " << time << "): " << field.mean.hare << endl;
	cout << "Mean Number of Pumas (at time " << time << "): " << field.mean.puma << endl;
	cout << endl;
}
*/
