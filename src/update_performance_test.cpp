#include <iostream>
#include <ctime>
#include "tile.h"
#include "board.h"
#include "update.h"


/*a piece of code to test the update routines*/

int main()
{
	double timeStep, a, b, k, l, m, r, newHareSum, oldHareSum, newPumaSum, oldPumaSum;
	Board<Tile> field(1000, 1000), old_field(1000,1000);

	double start, elapsedTime;

	a = b = k = l = m = r = timeStep = 1.0; // chosen so there are values

//
// initialise without pumas to test hare growth also make boundaries 0
//

	for(size_t j=0; j<field.get_height(); ++j)
	for(size_t i=0; i<field.get_width(); ++i)
	{
		if(j == 0 || i == 0 || j == 9 || i == 9)
		{
			field(i,j).make_water();
			field(i,j).hare = old_field(i,j).hare = 0.0;
			field(i,j).puma = old_field(i,j).puma = 0.0;
		}
		else
		{
			field(i,j).make_land();
			field(i,j).hare = old_field(i,j).hare = 1.0;
			field(i,j).puma = old_field(i,j).puma = 0.0;
		}
	}
	
	start = time(NULL);

	for(int i=0; i<100; ++i)
	{
		update_animals(field, timeStep, a, b, k, l, m, r);
	}
	
	elapsedTime = time(NULL) - start;

	cout << "time taken using y outer, x inner was: " << elapsedTime << "\n";


//
// reinitialise so the updates do the exact same operations for most accurate timing
//

	for(size_t j=0; j<field.get_height(); ++j)
	for(size_t i=0; i<field.get_width(); ++i)
	{
		if(j == 0 || i == 0 || j == 9 || i == 9)
		{
			field(i,j).make_water();
			field(i,j).hare = old_field(i,j).hare = 0.0;
			field(i,j).puma = old_field(i,j).puma = 0.0;
		}
		else
		{
			field(i,j).make_land();
			field(i,j).hare = old_field(i,j).hare = 1.0;
			field(i,j).puma = old_field(i,j).puma = 0.0;
		}
	}
	
	start = time(NULL);

	for(int i=0; i<100; ++i)
	{
		update_animals_p(field, timeStep, a, b, k, l, m, r);
	}
	
	elapsedTime = time(NULL) - start;

	cout << "time taken using x outer, y inner was: " << elapsedTime << "\n";

	return 0;

}
