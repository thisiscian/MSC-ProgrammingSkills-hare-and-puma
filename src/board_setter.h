#include "board.h"
#include "tile.h"
#include "file_reader.h"
#include "distribution.h"

#include <iostream>
#include <string>
#include <vector>

class BoardSetter
{
  public:

  // specific named file readers and setters
  static void set_land_from_file(
      Board<Tile>& board, std::string const& filename);
  static void set_hare_from_file(
      Board<Tile>& board, std::string const& filename);
  static void set_puma_from_file(
      Board<Tile>& board, std::string const& filename);

  // random setters
  static void set_land_randomly(
      Board<Tile>& board,
      DistributionBase<bool> const&
  );
  static void set_hare_randomly(
      Board<Tile>& board,
      DistributionBase<double> const&
  );
  static void set_puma_randomly(
      Board<Tile>& board,
      DistributionBase<double> const&
  );


  static Board<double> pgm_to_array(std::string const& filename);

};

