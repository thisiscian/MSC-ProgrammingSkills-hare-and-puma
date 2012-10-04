#include <iostream>
#include "tile.h"
#include "board.h"
#include "update.h"

/*a piece of code to test the update routines*/

int main()
{
	double timeStep, a, b, k, l, m, r, newHareSum, oldHareSum, newPumaSum, oldPumaSum;
	board<tile> field(10, 10), old_field(10,10);

	a = b = k = l = m = r = timeStep = 1.0; // chosen so there are values

//
// initialise without pumas to test hare growth
//

	for(size_t j=0; j<10; ++j)
	for(size_t i=0; i<10; ++i)
	{
		field(i,j).hare = old_field(i,j).hare = 1.0;
		field(i,j).puma = old_field(i,j).puma = 0.0;
	}

	

	update_hares(field, timeStep, a, k, r);
	update_pumas(field, timeStep, b, l, m, r);	

	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	

//
// first test if the hares numbers are increasing and pumas staying at 0
//

	for(size_t j=0; j<10; ++j)
	for(size_t i=0; i<10; ++i)
	{
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
	
	for(size_t j=0; j<10; ++j)
	for(size_t i=0; i<10; ++i)
	{
		field(i,j).hare = old_field(i,j).hare = 0.0;
		field(i,j).puma = old_field(i,j).puma = 1.0;
	}

	for(int i=0;i<5;++i)
	{
		update_hares(field, timeStep, a, k, r);
		update_pumas(field, timeStep, b, l, m, r);	
	}


//
// next test if the pumas die if there are no hares and the hares don't spawn
//

	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	

	for(size_t j=0; j<10; ++j)
	for(size_t i=0; i<10; ++i)
	{
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


	return 0;
}
