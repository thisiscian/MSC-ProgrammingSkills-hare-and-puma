#include <iostream>
#include "tile.h"
#include "board.h"
#include "update.h"


/*a piece of code to test the update routines*/

int main()
{
	double timeStep, a, b, k, l, m, r, newHareSum, oldHareSum, newPumaSum, oldPumaSum;
	Board<Tile> field(10, 10), old_field(10,10);

	a = b = k = l = m = r = timeStep = 1.0; // chosen so there are values

//
// initialise without pumas to test hare growth also make boundaries 0
//

	for(size_t j=0; j<10; ++j)
	for(size_t i=0; i<10; ++i)
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

	update_hares(field, timeStep, a, k, r);
	update_pumas(field, timeStep, b, l, m, r);	

	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	

//
// first test if the hares numbers are increasing and pumas staying at 0
// and test for negative pumas or hares
//

	for(size_t j=0; j<10; ++j)
	for(size_t i=0; i<10; ++i)
	{
		if(field(i,j).hare < 0)
		{
			cout << "error: negative hares appearing" << endl;
			return 1;
		}
		if(field(i,j).puma < 0)
		{
			cout << "error: negative pumas appearing" << endl;
			return 1;
		}
		newHareSum += field(i,j).hare;
		oldHareSum += old_field(i,j).hare;
		newPumaSum += field(i,j).puma;
		oldPumaSum += old_field(i,j).puma;
	}
	
	if(newHareSum <= oldHareSum)
	{
		cout << "error: hare sums not changing" << endl;
		return 1;
	}
	else if(newPumaSum != 0)
	{
		cout << "error: pumas have spawned" << endl;
		return 1;
	}

//
// reinitialise for re-testing, this time of puma death occuring
// this requires a short loop over updates
//
	
	for(size_t j=1; j<9; ++j)
	for(size_t i=1; i<9; ++i)
	{
		field(i,j).hare = old_field(i,j).hare = 0.0;
		field(i,j).puma = old_field(i,j).puma = 1.0;
	}

	for(int i=0;i<10;++i)
	{
		update_hares(field, timeStep, a, k, r);
		update_pumas(field, timeStep, b, l, m, r);	
	}


//
// next test if the pumas die if there are no hares and the hares don't spawn
// and test for negative pumas and hares
//

	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	

	for(size_t i=0; i<10; ++i)
	for(size_t j=0; j<10; ++j)
	{
		if(field(i,j).hare < 0)
		{
			cout << "error: negative hares appearing" << endl;
			return 1;
		}
		if(field(i,j).puma < 0)
		{
			cout << "error: negative pumas appearing" << endl;
			return 1;
		}
		newHareSum += field(i,j).hare;
		oldHareSum += old_field(i,j).hare;
		newPumaSum += field(i,j).puma;
		oldPumaSum += old_field(i,j).puma;
	}
	
	if(newHareSum != 0)
	{
		cout << "error: hares spawning" << endl;
		return 1;
	}
	else if(newPumaSum >= oldPumaSum)
	{
		cout << "error: pumas not dying" << endl;
		return 1;
	}


//
// initialise one square with pumas and hares to test migration
//

	for(size_t j=1; j<9; ++j)
	for(size_t i=1; i<9; ++i)
	{
		field(i,j).make_land();
		field(i,j).hare = old_field(i,j).hare = 0.0;
		field(i,j).puma = old_field(i,j).puma = 0.0;
	}

	field(5,5).hare = 10.0;
	field(5,5).puma = 10.0;
	
	update_hares(field, timeStep, a, k, r);
	update_pumas(field, timeStep, b, l, m, r);	


//
// test that pumas and hares are appearing in the squares adjacent to their
// starting point
//

	
	if(field(4,5).hare == 0 && field(6,5).hare == 0 && field(5,4).hare == 0 && field(5,6).hare == 0)
	{
		cout << "error: no hares have moved" << endl;
		return 1;
	}
	else if(field(4,5).puma == 0 && field(6,5).puma == 0 && field(5,4).puma == 0 && field(5,6).puma == 0)
	{
		cout << "error: no pumas have moved" << endl;
		return 1;
	}

//
//	test for negative hares and pumas
//

	for(size_t j=0; j<10; ++j)
	for(size_t i=0; i<10; ++i)
	{
		if(field(i,j).hare < 0)
		{
			cout << "error: negative hares appearing" << endl;
			return 1;
		}
		if(field(i,j).puma < 0)
		{
			cout << "error: negative pumas appearing" << endl;
			return 1;
		}
	}


	return 0;
}
