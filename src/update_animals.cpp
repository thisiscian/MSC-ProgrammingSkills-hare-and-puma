#include "update.h"

/*function that takes in the arrays of hares and pumas and updates them using the update equations*/

using namespace std;

void update_animals(Board<Tile> &board, double timeStep, double a, double b, double k, double l, double m, double r)
{

	int NY = board.get_height();
	int NX = board.get_width();
	int landSum;
  double hareSum, pumaSum;
	static Board<Tile> work_board(NX,NY);

#pragma omp parallel default(none) shared(board, timeStep, a, b, k, l, m, r, NX, NY, work_board) private(landSum, hareSum, pumaSum)
  {
    #pragma omp for
    for(int x=1; x<NX-1; ++x)
    for(int y=1; y<NY-1; ++y)
    {
      if(board(x,y).is_land())
      {
        landSum = hareSum = pumaSum = 0;

        hareSum += board(x-1,y).hare;
        pumaSum += board(x-1,y).puma;
        if(board(x-1,y).is_land())
        {
          landSum++;
        }

        hareSum += board(x+1,y).hare;
        pumaSum += board(x+1,y).puma;
        if(board(x+1,y).is_land())
        {
          landSum++;
        }

        hareSum += board(x,y-1).hare;
        pumaSum += board(x,y-1).puma;
        if(board(x,y-1).is_land())
        {
          landSum++;
        }

        hareSum += board(x,y+1).hare;
        pumaSum += board(x,y+1).puma;
        if(board(x,y+1).is_land())
        {
          landSum++;
        }

        work_board(x,y).hare = board(x,y).hare + timeStep* \
        (r*board(x,y).hare - a*board(x,y).hare * board(x,y).puma + k* \
        (hareSum - landSum*board(x,y).hare));

        if(work_board(x,y).hare < 0)
        {
          work_board(x,y).hare = 0;
        }	

        work_board(x,y).puma = board(x,y).puma + timeStep* \
        (b*board(x,y).hare*board(x,y).puma - m*board(x,y).puma + l* \
        (pumaSum - landSum*board(x,y).puma));

        if(work_board(x,y).puma < 0) 
        { 
          work_board(x,y).puma = 0; 
        }  
      }
      else
      {
        work_board(x,y).hare = work_board(x,y).puma = 0;
      }
    }

    #pragma omp for
    for(int x=1; x<NX-1; ++x)
    for(int y=1; y<NY-1; ++y)
    {
      board(x,y).hare = work_board(x,y).hare;
      board(x,y).puma = work_board(x,y).puma;
    }

  }

}
