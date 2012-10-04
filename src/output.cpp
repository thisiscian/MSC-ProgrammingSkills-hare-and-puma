//
//	This file is made by, and should be kept update by Cian Booth
//	this.is.cian@gmail.com
//

#include "output.h"

/*A function that recieves the populations of the hares and pumas, and outputs their values to the console*/
void output_to_console(board<tile> field, double time)
{
	int verticalPosition, horizontalPosition;
	int width = field.get_width();
	int height = field.get_height();

	printf("Time: %2.1f\n", time);
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
			printf("----------");
	}
	printf("-\n");
	for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
	{
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			if(field(horizontalPosition, verticalPosition).is_land())
			{
				printf("| H%6.1f ", field(horizontalPosition, verticalPosition).hare);
			}
			else
			{
				printf("| ~~~~~~~ ");
			}
		}
		printf("|\n");
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			if(field(horizontalPosition, verticalPosition).is_land())
			{
				printf("| P%6.1f ", field(horizontalPosition, verticalPosition).puma);
			}
			else
			{
				printf("| ~~~~~~~ ");
			}
		}
		printf("|\n");
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
		{
			printf("----------");
		}
		printf("-\n");
	}
	printf("\n");
}

/*A function that recieves the two populations and outputs a simple plain PPM file, named according to the current iteration to 'output/'*/
void write_simple_ppm(board<tile> field, double time)
{
	int verticalPosition, horizontalPosition;
	int width = field.get_width();
	int height = field.get_height();
	int maxValue = 255; // This is not a good choice, as values could well exceed it

	FILE *file;
	char buffer[100];
	sprintf(buffer, "output/population_%f.ppm", time);
	file = fopen(buffer, "w");
	
	fprintf(file, "P3 %i %i %i\n", width, height, maxValue);
	for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
	{
		for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
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
			fprintf(file, "%i %i %i ", red, green, blue);
		}
		fprintf(file, "\n");
	}
	fclose(file);	
}

/* A function that writes a fancy looking PPM file */
void write_fancy_ppm(board<tile> field, double time)
{
	int verticalPosition, horizontalPosition;
	int width = field.get_width();
	int height = field.get_height();
	int tileSize = 10;
	int borderWidth = 3;
	int maxValue = 255; // This is not a good choice, as values could well exceed it

	int drawingWidth = width*(borderWidth+tileSize)+borderWidth;
	int drawingHeight = height*(borderWidth+tileSize)+borderWidth;

	FILE *file;
	char buffer[100];
	char grey[12] = "040 040 040";
	sprintf(buffer, "output/fancy_%f.ppm", time);
	file = fopen(buffer, "w");
	
	fprintf(file, "P3 %i %i %i\n", drawingWidth, drawingHeight, maxValue);
	for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
	{
		for(horizontalPosition = 0; horizontalPosition < drawingWidth ; ++horizontalPosition)
		{
			for(int j=0; j<borderWidth; j++)
			{
				fprintf(file, "%s ", grey);
			}
		}
		for(int i=0; i<tileSize; i++)
		{
			for(horizontalPosition = 0; horizontalPosition < width ; ++horizontalPosition)
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
					fprintf(file, "%s ", grey);
				}
				for(int i=0; i<tileSize; i++)
				{
					fprintf(file, "%i %i %i ", red, green, blue);
				}
			}
			for(int j=0; j<borderWidth; j++)
			{
				fprintf(file, "%s ", grey);
			}
		}
	}
	for(horizontalPosition = 0; horizontalPosition < drawingWidth; ++horizontalPosition)
	{
		for(int j=0; j<borderWidth; j++)
		{
			fprintf(file, "%s \n", grey);
		}
	}
	fprintf(file, "\n");
		fclose(file);	
}

/*A function that outputs the mean values of the populations of the hares and pumas*/
/*void output_averages(board<tile> field, double time, double timeStep)
{

	cout << "Mean Number of Hares (at time " << time << "): " << field.mean.hare << endl;
	cout << "Mean Number of Pumas (at time " << time << "): " << field.mean.puma << endl;
	cout << endl;
}
*/
