#include <config.h>
#include "board_setter.h"
#include "board.h"
#include "options.h"

int main(int argc, char* argv[])
{
  /*
   * declare some variables
   */

  Board<Tile> board;
  Options options;

  /*
   * Process input
   */
  options.parse_input(argc, argv);


  /*
   * Set Board
   */

  BoardSetter::set_land_from_file(board, options.land_filename);

  // set hares
  if(!options.hare_filename.empty())
  {
    BoardSetter::set_hare_from_file(board, options.hare_filename);
  }
  else
  {
    BoardSetter::set_hare_from_distribution(board, RandomDistribution());
  }
  // set pumas
  if(!options.puma_filename.empty())
  {
    BoardSetter::set_puma_from_file(board, options.puma_filename);
  }
  else
  {
    BoardSetter::set_puma_from_distribution(board, RandomDistribution());
  }


  /*
   * run updates
   */

  /*
   * output data
   */


  return 0;
}
