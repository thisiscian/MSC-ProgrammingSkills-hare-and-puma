#include "board.h"
#include "tile.h"

class input_acceptor
{
  input_acceptor(board<tile>& board_in)
  {
    &current_board = &board_in;
  }



  private:

  board<tile> &current_board;

};
