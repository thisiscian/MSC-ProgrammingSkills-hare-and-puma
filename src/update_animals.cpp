#include "update.h"
#include <omp.h>

/*function that takes in the arrays of hares and pumas and updates them using the update equations*/

void update_animals(Board<Tile> &board, double timeStep, double a, double b, double k, double l, double m, double r)
{

	int NY = board.get_height();
	int NX = board.get_width();
	int landSum;
	Board<Tile> new_board(NX,NY);

#pragma omp parallel for default(none) shared(board, timeStep, a, b, k, l, m, r, NX, NY, new_board) private(landSum)
	for(int y=1; y<NY-1; ++y)
	for(int x=1; x<NX-1; ++x)
	{
		if(board(x,y).is_land())
		{
		landSum = 0;
			for(int i=x-1; i<=x+1; i+=2)
			{
				if(board(i,y).is_land())
				{
					landSum++;
				}
			}
			for(int i=y-1; i<=y+1; i+=2)
			{
				if(board(x,i).is_land())
				{
					landSum++;
				}	
			}

			new_board(x,y).hare = board(x,y).hare + timeStep* \
			(r*board(x,y).hare - a*board(x,y).hare * board(x,y).puma + k* \
			(board(x-1,y).hare + board(x+1,y).hare + board(x,y-1).hare + board(x,y+1).hare - \
			(landSum)*board(x,y).hare));

			new_board(x,y).puma = board(x,y).puma + timeStep* \
      (b*board(x,y).hare*board(x,y).puma - m*board(x,y).puma + l* \
      ((board(x-1,y).puma + board(x+1,y).puma + board(x,y-1).puma + board(x,y+1).puma) - \
      (landSum)*board(x,y).puma));
		}
		else
		{
			new_board(x,y).hare = new_board(x,y).puma = 0;
		}
	}

#pragma omp parallel for default(none) shared(NX, NY, new_board, board)
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
