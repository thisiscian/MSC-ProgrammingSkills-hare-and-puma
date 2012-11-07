#include "output.h"
#include <cstdio>
#include <math.h>

using namespace std;

int main()
{
	Board<Tile> field(10,10);
	int horizontalPosition, verticalPosition;
	int width = field.get_width();
	int height = field.get_height();

	/* convert stdout output to writing to "output.log" so console output can be checked */
	freopen("output.log", "w", stdout);
	
	/* define a field with arbitrarily different values for land, hare numbers and puma numbers */
	for(horizontalPosition = 0; horizontalPosition < width; ++horizontalPosition)
	{
		for(verticalPosition = 0; verticalPosition < height; ++verticalPosition)
		{
			field(horizontalPosition, verticalPosition).make_land();
			field(horizontalPosition, verticalPosition).hare = 255.0*max(cos(verticalPosition+horizontalPosition), 0.0);
			field(horizontalPosition, verticalPosition).puma = 255.0*max(sin(verticalPosition+horizontalPosition), 0.0);
			if(horizontalPosition % 2 == 0 && verticalPosition % 2 == 0)
			{
				field(horizontalPosition, verticalPosition).make_water();
			}
		}
	}

	output_to_console(field, 0.0);
	fclose(stdout);	

	ifstream check;
	string line;
	check.open("output.log");
	getline(check, line);
	if(line.find("Time") == string::npos)
	{
		cerr << "\tError: \"Time\" not printed" << endl;
		return 1;
	}
	getline(check,line);
	getline(check,line);
	if(line.find("~") == string::npos)
	{
		fprintf(stderr, "\tError: did not print small values\n");
		return 1;
	}
	else if(line.find("H") == string::npos)
	{
		fprintf(stderr, "Error: did not find Hare content\n");
		return 1;
	}
	getline(check,line);
	if(line.find("P") == string::npos)
	{
		fprintf(stderr, "\tError: did not find Puma content\n");
		return 1;
	}

	write_ppm(field, 0.0);
	write_adjustable_ppm(field, 0.0, 35, 3, "adjustable");
	return 0;
}
