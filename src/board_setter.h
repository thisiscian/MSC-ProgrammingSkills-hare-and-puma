#include "board.h"
#include "tile.h"
#include "file_reader.h"
#include "distribution.h"

#include <iostream>
#include <string>
#include <vector>

namespace BoardSetter
{
  // specific named file readers and setters
  void set_land_from_file(
      Board<Tile>& board, std::string const& filename);
  void set_hare_from_file(
      Board<Tile>& board, std::string const& filename);
  void set_puma_from_file(
      Board<Tile>& board, std::string const& filename);

  // random setters
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


  Board<double> pgm_to_array(std::string const& filename);

};

