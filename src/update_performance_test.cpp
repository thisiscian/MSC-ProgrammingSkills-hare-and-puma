#include <iostream>
#include <ctime>
#include "tile.h"
#include "board.h"
#include "update_p.h"

using namespace std;

/*a piece of code to test the speed of the update routines standard is a 1000x1000 board and 50 iterations*/

int main()
{
	double timeStep, a, b, k, l, m, r;
	Board<Tile> board(1002, 1002);

	double start, elapsedTime;

	a = b = k = l = m = r = timeStep = 1.0; // chosen so there are values

//
// initialise without pumas to test hare growth also make boundaries 0
//

	cout << "initialising board before testing" << endl;

	for(size_t j=0; j<board.get_height(); ++j)
	for(size_t i=0; i<board.get_width(); ++i)
	{
		if(j == 0 || i == 0 || j == board.get_height()-1 || i == board.get_height()-1)
		{
			board(i,j).make_water();
			board(i,j).hare = 0.0;
			board(i,j).puma = 0.0;
		}
		else
		{
			board(i,j).make_land();
			board(i,j).hare = 1.0;
			board(i,j).puma = 0.5;
		}
	}
	
	cout << "board initialised. Now starting timing test" << endl;

	start = time(NULL);

	for(int i=0; i<50; ++i)
	{
    update_animals_p(board, timeStep, a, b, k, l, m, r);
  }
	
  elapsedTime = time(NULL) - start;

  cout << "seconds for 50 updates of 1000x1000 board and current incarnation of update_animals: " << elapsedTime << "\n";
  cout << "Flops: " << (1000*1000*50*35)/elapsedTime << "\n";


	return 0;

}
