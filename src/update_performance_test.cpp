#include <iostream>
#include <ctime>
#include "tile.h"
#include "board.h"
#include "update_p.h"

using namespace std;

/*a piece of code to test the update routines*/

int main()
{
  double timeStep, a, b, k, l, m, r;
  Board<Tile> board(1000, 1000);

  double start, elapsedTime;

  a = b = k = l = m = r = timeStep = 1.0; // chosen so there are values

//
// initialise without pumas to test hare growth also make boundaries 0
//

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
  
  start = time(NULL);

  for(int i=0; i<50; ++i)
  {
    update_animals_p(board, timeStep, a, b, k, l, m, r);
  }
  
  elapsedTime = time(NULL) - start;

  cout << "time on multiple threads was: " << elapsedTime << "\n";


//
// reinitialise so the updates do the exact same operations for most accurate timing
//

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
  
  start = time(NULL);

  for(int i=0; i<50; ++i)
  {
    update_animals(board, timeStep, a, b, k, l, m, r);
  }
  
  elapsedTime = time(NULL) - start;

  cout << "time on one thread was: " << elapsedTime << "\n";

  return 0;

}
