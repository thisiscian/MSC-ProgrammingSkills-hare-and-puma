#include "board_setter.h"

// specific named file readers
void BoardSetter::set_land_from_file(
  Board<Tile>& board, std::string const& filename)
{
  Board<double> temp_board = pgm_to_array(filename);

  if(board.get_height() == 0 || board.get_width() == 0)
  {
    board.resize(temp_board.get_width(), temp_board.get_height());
  }

  for(size_t column = 0; column < temp_board.get_width();  ++column)
  for(size_t row    = 0; row    < temp_board.get_height(); ++row   )
  {
    if(temp_board(column, row) == Tile::water())
    {
      board(column, row).make_water();
    }
    else
    {
      board(column, row).make_land();
    }
  }

}
void BoardSetter::set_hare_from_file(
  Board<Tile>& board, std::string const& filename)
{
  Board<double> temp_board = pgm_to_array(filename);

  if(board.get_height() == 0 || board.get_width() == 0)
  {
    board.resize(temp_board.get_width(), temp_board.get_height());
  }

  for(size_t column = 0; column < temp_board.get_width();  ++column)
  for(size_t row    = 0; row    < temp_board.get_height(); ++row   )
  {
    board(column, row).hare = temp_board(column, row);
  }

}
void BoardSetter::set_puma_from_file(
  Board<Tile>& board, std::string const& filename)
{
  Board<double> temp_board = pgm_to_array(filename);

  if(board.get_height() == 0 || board.get_width() == 0)
  {
    board.resize(temp_board.get_width(), temp_board.get_height());
  }

  for(size_t column = 0; column < temp_board.get_width();  ++column)
  for(size_t row    = 0; row    < temp_board.get_height(); ++row   )
  {
    board(column, row).puma = temp_board(column, row);
  }

}




void BoardSetter::set_land_randomly(
    Board<Tile>& board,
    DistributionBase<bool> const& distribution
)
{
  for(size_t x=0; x<board.get_width(); ++x)
  for(size_t y=0; y<board.get_width(); ++y)
  {
    if(distribution(x,y))
    {
      board(x,y).make_land();
    }
    else
    {
      board(x,y).make_water();
    }
  }
}
void BoardSetter::set_hare_randomly(
    Board<Tile>& board,
    DistributionBase<double> const& distribution
)
{
  for(size_t x=0; x<board.get_width(); ++x)
  for(size_t y=0; y<board.get_width(); ++y)
  {
    if(board(x,y).is_land())
    {
      board(x,y).hare = distribution(x,y);
    }
  }
}


void BoardSetter::set_puma_randomly(
    Board<Tile>& board,
    DistributionBase<double> const& distribution
)
{
  for(size_t x=0; x<board.get_width(); ++x)
  for(size_t y=0; y<board.get_width(); ++y)
  {
    if(board(x,y).is_land())
    {
      board(x,y).hare = distribution(x,y);
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
