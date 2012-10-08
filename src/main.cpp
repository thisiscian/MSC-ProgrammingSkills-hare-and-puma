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

  BoardSetter::set_land_from_file(board, options.land_filename);
  BoardSetter::set_hare_from_file(board, options.hare_filename);
  BoardSetter::set_puma_from_file(board, options.puma_filename);


  /*
   * run updates
   */

  /*
   * output data
   */


  return 0;
}
