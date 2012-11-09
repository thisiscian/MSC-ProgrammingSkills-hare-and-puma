#include <iostream>
#include "tile.h"
#include "board.h"
#include "update.h"

using namespace std;


void reset_board(Board<Tile> &board, Board<Tile> &old_board);
void initialise_board(Board<Tile> &board, Board<Tile> &old_board, double hares, double pumas, int mod);
int test_negative(Board<Tile> &board, int testNumber);
/*a piece of code to test the update routines*/

int main()
{
  int test;
	double timeStep, a, b, k, l, m, r, newHareSum, oldHareSum, newPumaSum, oldPumaSum;
	Board<Tile> board(12, 10), old_board(12, 10);

	a = b = k = l = m = r = 1.0; // chosen so there are values
  timeStep = 0.1; //to maintain stability in the equation timeStep*k and timeStep*l must be < 0.25


//
// initialise without pumas to test hare growth also make boundaries 0
//
  reset_board(board, old_board);
  initialise_board(board, old_board, 1.6, 0.0, 1);

	update_animals(board, timeStep, a, b, k, l, m, r);

	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	

//
// first test if the hares numbers are increasing and pumas staying at 0
// and test for negative pumas or hares
//

  test = test_negative(board, 1);
  if(1 == test)
  {
    return 1;
  }

	for(size_t i=0; i<board.get_width(); ++i)
	for(size_t j=0; j<board.get_height(); ++j)
	{
	/*	if(board(i,j).hare < 0)
		{
			cout << "error: test 1: negative hares appearing" << endl;
			return 1;
		}
		if(board(i,j).puma < 0)
		{
			cout << "error: test 1: negative pumas appearing" << endl;
			return 1;
		}*/
		newHareSum += board(i,j).hare;
		oldHareSum += old_board(i,j).hare;
		newPumaSum += board(i,j).puma;
		oldPumaSum += old_board(i,j).puma;
	}
	
	if(newHareSum <= oldHareSum)
	{
		cout << "error: hares decreasing" << endl;
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
	
  initialise_board(board, old_board, 0.0, 1.6, 1);

	for(int i=0;i<1000;++i)
	{
		update_animals(board, timeStep, a, b, k, l, m, r);
	}


//
// next test if the pumas die if there are no hares and the hares don't spawn
// and test for negative pumas and hares
//

	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	

  test = test_negative(board, 2);
  if(1 == test)
  {
    return 1;
  }
	for(size_t i=0; i<board.get_width(); ++i)
	for(size_t j=0; j<board.get_height(); ++j)
	{
	/*	if(board(i,j).hare < 0)
		{
			cout << "error: test 2:negative hares appearing" << endl;
			return 1;
		}
		if(board(i,j).puma < 0)
		{
			cout << "error: test 2: negative pumas appearing" << endl;
			return 1;
		}*/
		newHareSum += board(i,j).hare;
		oldHareSum += old_board(i,j).hare;
		newPumaSum += board(i,j).puma;
		oldPumaSum += old_board(i,j).puma;
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
//flip board and old_board to test rectangular arrays properly
//

  board.resize(10,12);
  old_board.resize(10,12);

  reset_board(board, old_board);
  initialise_board(board, old_board, 0.0, 0.0, 1);

//
// initialise one square with pumas and hares to test migration
//

	board(5,5).hare = 10.8;
	board(5,5).puma = 10.8;
	
	update_animals(board, timeStep, a, b, k, l, m, r);


//
// test that pumas and hares are appearing in the squares adjacent to their
// starting point
//

	
	if(board(4,5).hare == 0 && board(6,5).hare == 0 && board(5,4).hare == 0 && board(5,6).hare == 0)
	{
		cout << "error: no hares have moved" << endl;
		return 1;
	}
	else if(board(4,5).puma == 0 && board(6,5).puma == 0 && board(5,4).puma == 0 && board(5,6).puma == 0)
	{
		cout << "error: no pumas have moved" << endl;
		return 1;
	}

//
//	test for negative hares and pumas
//

  test = test_negative(board, 3);
  if(1 == test)
  {
    return 1;
  }

//
// reinitialise to now test that the parameters (all=0) have the correct effect
//

  initialise_board(board, old_board, 1.5, 1.5, 1);
 
//
//  will test that if all parameters are zero that the number of animals stay the same
//   

	a = b = k = l = m = r = 0.0;
	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	
  	
	update_animals(board, timeStep, a, b, k, l, m, r);

	for(size_t j=1; j<board.get_height()-1; ++j)
	for(size_t i=1; i<board.get_width()-1; ++i)
	{
    newHareSum += board(i,j).hare;
    oldHareSum += old_board(i,j).hare;
    newPumaSum += board(i,j).puma;
    oldPumaSum += old_board(i,j).puma;
  }
	
	if(newHareSum != oldHareSum)
	{
		cout << "error: 0 parameter test: Hare numbers changing" << endl;
		return 1;
	}
	else if(newPumaSum != oldPumaSum)
	{
		cout << "error: 0 parameter test: Puma numbers changing" << endl;
		return 1;
	}

//
// reinitialise to now test that the parameters (a,b!=0) have the correct effect
//

  initialise_board(board, old_board, 1.5, 1.5, 1);
 
//
//  test for agreement with analytical solution to a,b!=0 everything else 0
//   

	a = b = 1;
  k = l = m = r = 0.0;
	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	

  for(int k=0; k<10; ++k)
  {
    for(size_t j=1; j<board.get_height()-1; ++j)
    for(size_t i=1; i<board.get_width()-1; ++i)
    {
      old_board(i,j).hare = board(i,j).hare;
      old_board(i,j).puma = board(i,j).puma;
    }
    update_animals(board, timeStep, a, b, k, l, m, r);

    for(size_t j=1; j<board.get_height()-1; ++j)
    for(size_t i=1; i<board.get_width()-1; ++i)
    {
      //upon solving the update equations with all parameters 0 except a and b, one finds that the following must hold true
      //not checked against 0 due to floating point errors
      if(board(i,j).hare - old_board(i,j).hare + (a/b)*(board(i,j).puma - board(i,j).puma) > 0.0000001)
      {
        cout << "error: a,b parameter test: derived equation does not hold" << endl;
        return 1;
      }
    }
  }
	
//
// reinitialise to now test that the parameters(k,l=0) have the correct effect
//

  initialise_board(board, old_board, 1.5, 1.5, 2);
 
//
//  will test that if k,l=0 that there is no diffusion occuring
//  

	k = l = 0.0;
  a = b = m = r = 1.0;
	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	
  	
	update_animals(board, timeStep, a, b, k, l, m, r);

	for(size_t j=1; j<board.get_height()-1; ++j)
	for(size_t i=1; i<board.get_width()-1; ++i)
	{
    if(1 == (i+j)%2)
    {
      if(board(i,j).hare != 0.0)
      {
        cout << "error: k,l parameter test: hares diffusing" << endl;
        return 1;
      }
      if(board(i,j).puma != 0.0)
      {
        cout << "error: k,l parameter test: pumas diffusing" << endl;
        return 1;
      }
    }
  }


//
// reinitialise to now test that the parameters(k,l=0) have the correct effect
//

  initialise_board(board, old_board, 1.5, 1.5, 2);
 
//
//  will test that if k,l=0 that the hares an pumas increase in populated squares according to H_1=H_0e^(rt) and similarly
//  for pumas
//  

	a = b = k = l = 0.0;
  m = r = 1.0;
	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	
  	
	update_animals(board, timeStep, a, b, k, l, m, r);

	for(size_t j=1; j<board.get_height()-1; ++j)
	for(size_t i=1; i<board.get_width()-1; ++i)
	{
    if(0 == (i+j)%2)
    {
      if(board(i,j).hare - old_board(i,j).hare*exp(r*timeStep) > 0.0000001)
      {
        cout << "error: k,l=0 parameter test: hares not evolving in time properly" << endl;
        return 1;
      }
      if(board(i,j).puma - old_board(i,j).puma*exp(-m*timeStep) > 0.0000001)
      {
        cout << "error: k,l=0 parameter test: pumas not evolving in time properly" << endl;
        return 1;
      }
    }
    else
    {
      if(board(i,j).hare != 0.0)
      {
        cout << "error: k,l=0 parameter test: hares diffusing" << endl;
        return 1;
      }
      if(board(i,j).puma != 0.0)
      {
        cout << "error: k,l=0 parameter test: pumas diffusing" << endl;
        return 1;
      }
    }
  }

//
// reinitialise to now test that the parameters (k,l=1, allelse=0) have the correct effect
//

  initialise_board(board, old_board, 1.5, 1.5, 1);
 
//
//  will test that if the board is uniform it stays uniform with only diffusion
//   

	a = b = m = r = 0.0;
  k = l = 1.0;
	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	
  	
	update_animals(board, timeStep, a, b, k, l, m, r);

	for(size_t j=1; j<board.get_height()-1; ++j)
	for(size_t i=1; i<board.get_width()-1; ++i)
	{
    if(old_board(i,j).hare != board(i,j).hare)
    {
      cout << " error: k,l=1 parameter test: hare numbers changed" << endl;
      return 1;
    }
    if(old_board(i,j).puma != board(i,j).puma)
    {
      cout << "error: k,l=1 parameter test: puma numbers changed" << endl;
      return 1;
    }
    newHareSum += board(i,j).hare;
    oldHareSum += old_board(i,j).hare;
    newPumaSum += board(i,j).puma;
    oldPumaSum += old_board(i,j).puma;
  }
	
	if(newHareSum != oldHareSum)
	{
		cout << "error: k,l=1 parameter test: Hare numbers changing" << endl;
		return 1;
	}
	else if(newPumaSum != oldPumaSum)
	{
		cout << "error: k,l=1 parameter test: Puma numbers changing" << endl;
		return 1;
	}

//
// reinitialise to now test that the parameters(k,l=1) and everything else 0 has the correct effect
//

  initialise_board(board, old_board, 1.5, 1.5, 2);
 
//
//  will test that if k,l=1 on a checkerboard 0 squares become populated
//  

	k = l = 1.0;
  a = b = m = r = 0.0;
	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	
  	
	update_animals(board, timeStep, a, b, k, l, m, r);

	for(size_t j=1; j<board.get_height()-1; ++j)
	for(size_t i=1; i<board.get_width()-1; ++i)
	{
    if(1 == (i+j)%2)
    {
      if(board(i,j).hare == 0.0)
      {
        cout << "error: k,l parameter test: hares not diffusing" << endl;
        return 1;
      }
      if(board(i,j).puma == 0.0)
      {
        cout << "error: k,l parameter test: pumas not diffusing" << endl;
        return 1;
      }
    }
  }

//
// test for animals appearing on water in the map
//

  a = b = k = l = m = r = 1.0;

  initialise_board(board, old_board, 0.9, 1.1, 1); //these puma and hare values persist for a while
	
	board(5,5).make_water();
	board(2,2).make_water();

	for(int i=0; i<1; ++i)
	{
		update_animals(board, timeStep, a, b, k, l, m, r);

		if(board(5,5).hare != 0 || board(2,2).hare != 0 || board(5,5).puma != 0 || board(2,2).puma !=0)
		{
			cout << "error: animals appearing in water" << endl;
			return 1;
		} 
	}

	return 0;
}

//
//function to initialise the board, takes arguments of the hare and puma numbers
//the mod argument determines whether it will be in a checkerboard style or not
//
void initialise_board(Board<Tile> &board, Board<Tile> &old_board, double hares, double pumas, int mod)
{
	for(size_t i=1; i<board.get_width()-1; ++i)
	for(size_t j=1; j<board.get_height()-1; ++j)
	{
    if(0 == (i+j)%mod)
    {
      board(i,j).hare = old_board(i,j).hare = hares;
      board(i,j).puma = old_board(i,j).puma = pumas;
    }
    else
    {
      board(i,j).hare = old_board(i,j).hare = 0.0;
      board(i,j).puma = old_board(i,j).puma = 0.0;
    }
	}
}

//
//function to reset the boundaries of the board
//
void reset_board(Board<Tile> &board, Board<Tile> &old_board)
{
	for(size_t i=0; i<board.get_width(); ++i)
	for(size_t j=0; j<board.get_height(); ++j)
	{
		if(j == 0 || i == 0 || j == board.get_height()-1 || i == board.get_width()-1)
		{
			board(i,j).make_water();
      old_board(i,j).make_water();
			board(i,j).hare = old_board(i,j).hare = 0.0;
			board(i,j).puma = old_board(i,j).puma = 0.0;
		}
    else
    {
    board(i,j).make_land();
    old_board(i,j).make_land();
    }
	}
}

//
//function to test for negative animals appearing. Takes testNumber so location can be found
//
int test_negative(Board<Tile> &board, int testNumber)
{
	for(size_t i=0; i<board.get_width(); ++i)
	for(size_t j=0; j<board.get_height(); ++j)
	{
		if(board(i,j).hare < 0)
		{
			cout << "error: test " << testNumber << ": negative hares appearing" << endl;
			return 1;
		}
		if(board(i,j).puma < 0)
		{
			cout << "error: test " << testNumber << ": negative pumas appearing" << endl;
			return 1;
		}
	}
}
