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

	cout << setprecision(3);
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
				cout << "| H" << setw(6) << setfill(' ') <<  field(horizontalPosition, verticalPosition).hare << " " << flush;
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
				cout << "| P" << setw(6) << setfill(' ') <<  field(horizontalPosition, verticalPosition).puma << " " << flush;
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
	write_adjustable_ppm(field, time, 1, 1, "population");
}

void write_adjustable_ppm(Board<Tile> field, double time, int tileSize, int borderWidth, string title)
{
	int verticalPosition, horizontalPosition;
	int width = field.get_width();
	int height = field.get_height();
	int maxValue = 255; // This is the value to be written to PPM, not the actual maximum value. Values could well exceed it

	int drawingWidth = width*(borderWidth+tileSize)+borderWidth;
	int drawingHeight = height*(borderWidth+tileSize)+borderWidth;
	int red, green, blue;
	int i,j,k;
	string grey = " 40  40  40";
	
	ofstream file;
	stringstream fileName;
	fileName << "output/" << title << "_" << time << ".ppm";
	file.open(fileName.str().c_str());
	
	file << "P3 " << drawingWidth << " " <<  drawingHeight << " " <<  maxValue << endl;
	for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
	{
		for(horizontalPosition = 0; horizontalPosition < drawingWidth;  ++horizontalPosition)
		{
			for(i=0; i<borderWidth; ++i)
			{
				file << grey << "\t" << flush;
			}
		}
		file << endl;
		for(i=0; i<tileSize; ++i)
		{
			for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
			{
				if(field(horizontalPosition, verticalPosition).is_land())	
				{
					red = floor(field(horizontalPosition, verticalPosition).puma);
					green = floor(field(horizontalPosition, verticalPosition).hare);
					blue = 0;
				}
				else
				{
					red = 0;
					green = 0;
					blue = 255;
				}
				for(j=0; j<borderWidth; ++j)
				{
					file << grey << "\t" << flush;
				}
				for(k=0; k<tileSize; ++k)
				{
					file << setfill(' ' ) << setw(3) << red << " " <<  setw(3) << green << " " << setw(3) << blue << "\t" << flush;
				}
			}
			for(j=0; j<borderWidth; ++j)
			{
				file << grey << "\t" << flush;
			}
			file << endl;
		}
	}
	for(horizontalPosition = 0; horizontalPosition < drawingWidth;  ++horizontalPosition)
	{
		for(j=0; j<borderWidth; ++j)
		{
			file << grey << "\t" << flush;
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
