#include "update.h"

/*function that takes in the arrays of hares and pumas and updates them using the update equations*/

void update_animals(Board<Tile> &board, double timeStep, double a, double b, double k, double l, double m, double r)
{

	int NY = board.get_height();
	int NX = board.get_width();
	int landSum, hareSum, pumaSum;
	Board<Tile> new_board(NX,NY);

#pragma omp parallel for default(none) shared(board, timeStep, a, b, k, l, m, r, NX, NY, new_board) private(landSum, hareSum, pumaSum) schedule(runtime)
	for(int y=1; y<NY-1; ++y)
	for(int x=1; x<NX-1; ++x)
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

			new_board(x,y).hare = board(x,y).hare + timeStep* \
			(r*board(x,y).hare - a*board(x,y).hare * board(x,y).puma + k* \
			(hareSum - landSum*board(x,y).hare));

			new_board(x,y).puma = board(x,y).puma + timeStep* \
      (b*board(x,y).hare*board(x,y).puma - m*board(x,y).puma + l* \
      (pumaSum - landSum*board(x,y).puma));
		}
		else
		{
			new_board(x,y).hare = new_board(x,y).puma = 0;
		}
	}

#pragma omp parallel for default(none) shared(NX, NY, new_board, board) schedule(runtime)
	for(int y=1; y<NY-1; ++y)
	for(int x=1; x<NX-1; ++x)
	{
		if(new_board(x,y).hare < 0)
		{
			board(x,y).hare = 0;
		}	
		else
		{
			board(x,y).hare = new_board(x,y).hare;
		}

		if(new_board(x,y).puma < 0) 
    { 
      board(x,y).puma = 0; 
    }  
    else 
    { 
    board(x,y).puma = new_board(x,y).puma;
    }

	}
	

}
