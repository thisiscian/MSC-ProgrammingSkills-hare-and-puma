///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// ----------                                                                //
// output.cpp 			                                                         //
// ----------                                                                //
//                                                                           //
// maintained by Cian Booth                                                  //
// email issues to this.is.cian@gmail.com                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


#include "output.h"

using namespace std;

void create_output_directory(string directory_name)
{
	// the mode S_IRWXU allows the user read, write and execute permissions
	int err = mkdir(directory_name.c_str(), S_IRWXU);
}

/*A function that recieves the populations of the hares and pumas, and outputs their values to the console*/
void output_to_console(Board<Tile> field, double time)
{
	int verticalPosition, horizontalPosition;
	int width = field.get_width();
	int height = field.get_height();

	cout << setprecision(3);
	cout << "Time: " << time << "\n";
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
			cout << "----------";
	}
	cout << "-" << "\n";
	for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
	{
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			if(field(horizontalPosition, verticalPosition).is_land())
			{
				cout << "| H" << setw(6) << setfill(' ') <<  field(horizontalPosition, verticalPosition).hare << " ";
			}
			else
			{
				cout << "| ~~~~~~~ ";
			}
		}
		cout << "|" << "\n";
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			if(field(horizontalPosition, verticalPosition).is_land())
			{
				cout << "| P" << setw(6) << setfill(' ') <<  field(horizontalPosition, verticalPosition).puma << " ";
			}
			else
			{
				cout << "| ~~~~~~~ ";
			}
		}
		cout << "|" << "\n";
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			cout << "----------";
		}
		cout << "-" << "\n";
	}
	cout << "\n";
}

/*A function that recieves the two populations and outputs a simple plain PPM file, named according to the current iteration to 'output/'*/
void write_ppm(Board<Tile> field, double time, string output_directory)
{
	write_adjustable_ppm(field, time, 1, 0, "population", output_directory);
}

void write_adjustable_ppm(Board<Tile> field, double time, int tileSize, int borderWidth, string title, string output_directory)
{
	int verticalPosition, horizontalPosition;
	int width = field.get_width();
	int height = field.get_height();
	int maxValue = 255;

	int drawingWidth = (width-2)*(borderWidth+tileSize)+borderWidth;
	int drawingHeight = (height-2)*(borderWidth+tileSize)+borderWidth;
	int red, green, blue;
	int i,j,k;
	string grey = " 40  40  40";
	
	ofstream file;
	stringstream fileName;
	fileName << output_directory << "/" << title << "_" << setprecision(3) << setw(4) << setfill('0') << left << fixed << time << ".ppm";
	file.open(fileName.str().c_str());
	
	file << "P3 " << drawingWidth << " " <<  drawingHeight << " " <<  maxValue << "\n";
	for(verticalPosition = 1; verticalPosition < height-1; ++verticalPosition)
	{
		for(horizontalPosition = 1; horizontalPosition <= drawingWidth;  ++horizontalPosition)
		{
			for(i=0; i<borderWidth; ++i)
			{
				file << grey << "\t";
			}
		}
		file << "\n";
		for(i=0; i<tileSize; ++i)
		{
			for(horizontalPosition = 1; horizontalPosition < width-1; ++horizontalPosition)
			{
				if(field(horizontalPosition, verticalPosition).is_land())	
				{
					red = min(floor(field(horizontalPosition, verticalPosition).puma),255.0);
					green = min(floor(field(horizontalPosition, verticalPosition).hare),255.0);
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
					file << grey << "\t";
				}
				for(k=0; k<tileSize; ++k)
				{
					file << setfill(' ') << setw(3) << red << " " <<  setw(3) << green << " " << setw(3) << blue << "\t";
				}
			}
			for(j=0; j<borderWidth; ++j)
			{
				file << grey << "\t";
			}
			file << "\n";
		}
	}
	for(horizontalPosition = 1; horizontalPosition <= drawingWidth;  ++horizontalPosition)
	{
		for(j=0; j<borderWidth; ++j)
		{
			file << grey << "\t";
		}
	}
	file << "\n";
	file.close();	
}

/*A function that outputs the mean values of the populations of the hares and pumas*/
void output_averages(Board<Tile> field, double time, double timeStep)
{
	BoardStatistics stats(field);
	cout << "Total Number of Hares: " << stats.get_hare_total() << endl;
	cout << "Total Number of Pumass: " << stats.get_puma_total() << endl;
	cout << "Mean Number of Hares (at time " << time << "): " << stats.get_hare_average() << endl;
	cout << "Mean Number of Pumas (at time " << time << "): " << stats.get_puma_average() << endl;
	cout << endl;
}

