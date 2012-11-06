#include "board_setter.h"

/*
 * BoardSetter::set_land_from_file
 *  set the tiles in a Board<Tile> type to land or water based
 *  on data in a given input file
 *
 */
void BoardSetter::set_land_from_file(
  Board<Tile>& board, std::string const& filename)
{
  // read file into Board<double> type
  Board<double> temp_board = pgm_to_array(filename);

  /*
   * if the dimensions of the board haven't already been set,
   * set them.
   *
   * Add 2 to the dimensions to allow for halo data
   */
  if(board.get_height() == 0 || board.get_width() == 0)
  {
    board.resize(temp_board.get_width()+2, temp_board.get_height()+2);
  }

  // loop over the input board dimensions
  for(size_t column = 0; column < temp_board.get_width()+2;  ++column)
  for(size_t row    = 0; row    < temp_board.get_height()+2; ++row   )
  {
    // add halo of water on boundaries
    if(column == 0 || column == temp_board.get_width()+1
        || row == 0 || row == temp_board.get_width()+1)
    {
      board(column, row).make_water();
    }
    // set internal tiles to value from input file
    else if(temp_board(column-1, row-1) == Tile::water())
    {
      board(column, row).make_water();
    }
    else
    {
      board(column, row).make_land();
    }
  }

}


/*
 * BoardSetter::set_hare_from_file
 *  set the hare value of tiles in a Board<Tile> type to values
 *  based on data in a given input file
 *
 */
void BoardSetter::set_hare_from_file(
  Board<Tile>& board, std::string const& filename)
{
  // read input file to array
  Board<double> temp_board = pgm_to_array(filename);

  /* if board not already initialized, initialize to
   * dimensions of input data plus 2 for halos
   */
  if(board.get_height() == 0 || board.get_width() == 0)
  {
    board.resize(temp_board.get_width()+2, temp_board.get_height()+2);
  }

  // loop over input board
  for(size_t column = 0; column < temp_board.get_width()+2;  ++column)
  for(size_t row    = 0; row    < temp_board.get_height()+2; ++row   )
  {
    // set boundary to zero
    if(column == 0 || column == temp_board.get_width()+1
        || row == 0 || row == temp_board.get_width()+1)
    {
      board(column, row).hare = 0;
    }
    // set inner board to values of input data
    else
    {
      board(column, row).hare = temp_board(column-1, row-1);
    }
  }

}


/*
 * BoardSetter::set_puma_from_file
 *  set the puma value of tiles in a Board<Tile> type to values
 *  based on data in a given input file
 *
 */
void BoardSetter::set_puma_from_file(
  Board<Tile>& board, std::string const& filename)
{
  // set array from data in file
  Board<double> temp_board = pgm_to_array(filename);

  /*
   * If board not already initialized, set dimensions
   * to those of the input data.
   *
   * Add 2 to each dimensions for zero halos.
   */
  if(board.get_height() == 0 || board.get_width() == 0)
  {
    board.resize(temp_board.get_width()+2, temp_board.get_height()+2);
  }

  for(size_t column = 0; column < temp_board.get_width()+2;  ++column)
  for(size_t row    = 0; row    < temp_board.get_height()+2; ++row   )
  {
    // set boundary to zero
    if(column == 0 || column == temp_board.get_width()+1
        || row == 0 || row == temp_board.get_width()+1)
    {
      board(column, row).puma = 0;
    }
    // set internal board to values from input file
    else
    {
      board(column, row).puma = temp_board(column-1, row-1);
    }
  }

}



/*
 * BoardSetter::set_land_from_distribution
 *  Set tile to land or water on board according to
 *  input distribution.
 *
 *  true -> land
 *  false -> water
 *
 */
void BoardSetter::set_land_from_distribution(
    Board<Tile>& board,
    DistributionBase<bool> const& distribution
)
{
  for(size_t x=0; x<board.get_width(); ++x)
  for(size_t y=0; y<board.get_height(); ++y)
  {
    // set halo to water
    if(  x==0 || x==board.get_width()-1
      || y==0 || y==board.get_height()-1)
    {
      board(x,y).make_land();
    }
    // set inner board according to distribution
    else if(distribution(x,y))
    {
      board(x,y).make_land();
    }
    else
    {
      board(x,y).make_water();
    }
  }
}

/*
 * BoardSetter::set_hare_from_distribution
 *  Set hare data for Board<Tile> based on input distribution.
 *
 */
void BoardSetter::set_hare_from_distribution(
    Board<Tile>& board,
    DistributionBase<double> const& distribution
)
{
  for(size_t x=0; x<board.get_width(); ++x)
  for(size_t y=0; y<board.get_height(); ++y)
  {
    //std::cerr << "HARE: (" << x << "," << y << ")" << std::endl;
    // set boundaries to zero
    if(  x==0 || x==board.get_width()-1
      || y==0 || y==board.get_height()-1)
    {
      board(x,y).hare = 0;
    }
    // set internal board according to distribution
    else if(board(x,y).is_land())
    {
      board(x,y).hare = distribution(x,y);
    }
    else
    {
      board(x,y).hare = 0;
    }
  }
}


/*
 * BoardSetter::set_hare_from_distribution
 *  Set hare data for Board<Tile> based on input distribution.
 *
 */
void BoardSetter::set_puma_from_distribution(
    Board<Tile>& board,
    DistributionBase<double> const& distribution
)
{
  for(size_t x=0; x<board.get_width(); ++x)
  for(size_t y=0; y<board.get_height(); ++y)
  {
    // set boundaries to zero
    if(  x==0 || x==board.get_width()-1
      || y==0 || y==board.get_height()-1)
    {
      board(x,y).puma = 0;
    }
    // set internal board according to distribution
    else if(board(x,y).is_land())
    {
      board(x,y).puma = distribution(x,y);
    }
    else
    {
      board(x,y).puma = 0;
    }
  }
}

Board<double> BoardSetter::pgm_to_array(std::string const& filename)
{
  Board<double> return_board;

  FileReader file;

  std::vector<double> line_values;

  file.open(filename.c_str());

  if(file.is_open())
  {

    // get file size from header
    // format: width height
    while(true)
    {
      line_values = file.parse_line();

      return_board.resize(line_values[0], line_values[1]);

      break;
    }

    // loop over all lines of the file
    size_t row = 0;
    while(file.good())
    {
      // copy line of values to vector
      line_values = file.parse_line();

      // copy vector to current row of board
      for(size_t column=0; column<line_values.size(); ++column)
      {
        return_board(column, row) = line_values[column];
      }

      ++row;

    }

    file.close();
  }
  else
  {
    std::cerr << "Failed to open file: " << filename <<  std::endl;
  }

  return return_board;
}
