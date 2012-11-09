///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// ----------                                                                //
// output.cpp 			                                                         //
// ----------                                                                //
//                                                                           //
// this file contains the functions neccessary to create .ppm files          //
//                                                                           //
//                                                                           //
// maintained by Cian Booth                                                  //
// email issues to this.is.cian@gmail.com                                    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "write_ppm.h"

using namespace std;

void create_output_directory(string directory_name)
{
	// the mode S_IRWXU allows the user read, write and execute permissions
	int err = mkdir(directory_name.c_str(), S_IRWXU);
}

/*A function that recieves the two populations and outputs a simple plain PPM file, named according to the current iteration to 'output/'*/
void write_ppm(Board<Tile>& board, double time, string output_directory)
{
	write_adjustable_ppm(board, time, 1, 0, "population", output_directory);
}

void write_adjustable_ppm(Board<Tile>& board, double time, int tileSize, int borderWidth, string title, string output_directory)
{
	int verticalPosition, horizontalPosition;
	int width = board.get_width();
	int height = board.get_height();
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
				if(board(horizontalPosition, verticalPosition).is_land())	
				{
					red = min(floor(board(horizontalPosition, verticalPosition).puma),255.0);
					green = min(floor(board(horizontalPosition, verticalPosition).hare),255.0);
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
void output_averages(Board<Tile>& board, double time)
{
	BoardStatistics stats(board);
	cout << "Total Number of Hares: " << stats.get_hare_total() << endl;
	cout << "Total Number of Pumas: " << stats.get_puma_total() << endl;
	cout << "Mean Number of Hares: " << stats.get_hare_mean() << endl;
	cout << "Mean Number of Pumas: " << stats.get_puma_mean() << endl;
	cout << "Time Average Number of Hares" << stats.get_hare_average() << endl;
	cout << "Time Average Number of Pumas" << stats.get_puma_average() << endl;
	cout << endl;
}

