#ifndef __BOARD_SETTER_H__
#define __BOARD_SETTER_H__

/*
 * namespace BoardSetter
 *  
 *  The BoardSetter class of helper functions act upon a type Board<Tile>
 *  and set various aspects of the board.
 *
 *  The board setter class follows the following conventions when reading
 *  files:
 *
 *    board(x,y)
 *
 *     ---> x
 *    |
 *    |
 *    V
 *    y
 *
 */
#include "board.h"
#include "tile.h"
#include "file_reader.h"
#include "distribution.h"

#include <iostream>
#include <string>
#include <vector>

namespace BoardSetter
{

  /*
   * set_land_from_file
   *
   *  This function sets the tiles of a board to be either land or
   *  water based on data in a named input file.
   *
   *  This function also adds a halo of water to the input data.
   *
   *  Input files look much like PGM files with binary values.
   *
   *  The first row should contain the width and height of the
   *  data in the file, in that order.
   *
   *  The data should consist of 1s and 0s, where 1 indicates a tile
   *  is made of land and 0 indicates a tile is made of water.
   *
   *  If a tile contains a value for a hare or puma distribution and is
   *  set to water, the value will be unaffected.
   *
   *  If the dimensions of a board have not yet been set, this function will
   *  set them to the dimensions of the input data.
   *
   *  Example Useage:
   *    #File.dat
   *    5 4
   *    1 0 0 1 1
   *    0 1 1 0 1
   *    0 1 1 1 1
   *    1 1 0 0 0
   *
   *    Board<Tile> board;
   *    set_land_from_file(board, "File.dat");
   *
   *    #board(0,0) -> 0
   *    #board(6,5) -> 0
   *    #board(1,1) -> 1
   *    #board(3,4) -> 0
   *
   */
  void set_land_from_file(
      Board<Tile>& board, std::string const& filename);

  /*
   * set_hare_from_file
   * set_puma_from_file
   *
   *  These functions set the hare population or puma population of
   *  the tiles of a board based on named input files.
   *
   *  This function also adds a halo of 0 values around the outside
   *  of the data.
   *
   *  Input files look much like PGM files with decimal values.
   *
   *  The files should begin with the width and height of the data in
   *  the file.
   *
   *  The data should consist of nonzero values of the density of the
   *  hare or puma population at of a given tile.
   *
   *  If the dimensions of a board have not yet been set, this function will
   *  set them to the dimensions of the input data.
   *
   *  Example Useage:
   *    #File.dat
   *    5 4
   *    1.21 0 0 2.5 2
   *    0 3.033 2.4 0 1.4
   *    0 2.7 1.5 0.8 1.3
   *    2.004 2.1 0 0 0
   *
   *    Board<Tile> board;
   *    set_hare_from_file(board, "File.dat");
   *    
   *    #board(0,0) -> 0
   *    #board(6,5) -> 0
   *    #board(1,1) -> 1.21
   *    #board(1,4) -> 2.004
   *
   */
  void set_hare_from_file(
      Board<Tile>& board, std::string const& filename);
  void set_puma_from_file(
      Board<Tile>& board, std::string const& filename);


  /*
   * Given an instance of a class inheriting from DistributionBase,
   * these functions use those distributions to set certain values
   * of the tiles of a board.
   *
   * These functions call the operator()(x,y) method of the input class.
   *
   * The reasoning for this was to allow for easily configured parameters
   * of a distribution without having to resort to using global variables
   * and passing function pointers.
   *
   * Halo data will be set to zero (or land) regardless of distribution.
   *
   * Example Useage:
   *  Board<Tile> board(5,4);
   *  set_land_from_distribution(board, MyLandDistribution(a,d,c,d));
   *
   */
  void set_land_from_distribution(
      Board<Tile>& board,
      DistributionBase<bool> const&
  );
  void set_hare_from_distribution(
      Board<Tile>& board,
      DistributionBase<double> const&
  );
  void set_puma_from_distribution(
      Board<Tile>& board,
      DistributionBase<double> const&
  );


  /*
   * pgm_to_array
   *
   *  Given a named input file, this function will parse
   *  the file and output a Board<double> type initialized
   *  to the dimensions of the data and each element set to
   *  the corresponding piece of data in the file.
   *
   *  Example:
   *    #File.dat
   *    5 4
   *    1 0 1 1 0
   *    1 0 1 0 1
   *    1 1 1 0 1
   *    0 0 1 1 1
   *
   *    Board<double> board = pgm_to_array("File.dat");
   *
   *    double zero_zero = board(0,0);
   *    #one_one -> 1
   *
   *    double zero_one = board(0,1);
   *    #zero_one -> 1
   *
   */

  Board<double> pgm_to_array(std::string const& filename);

};

#endif
