#include "board.h"
#include "tile.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>



class file_reader : public std::ifstream
{
  public:

  std::vector<double> parse_line()
  {
    std::vector<double> values;
    std::string line;

    // ignore comments
    while(true)
    {
      // check if line is comment
      if(peek() == '#')
      {
        std::string discard;
        std::getline(*this, discard);
        continue;
      }
      break;
    }

    // read the line in from the file
    std::getline(*this, line);

    // if line contains no data, just return;
    if(line.length() == 0)
    {
      return values;
    }

    // initialize start to start of string
    size_t number_start = line.find_first_not_of(' ');
    size_t number_end = 0;

    // loop over all numbers in the string
    do
    {
      double this_value = 0;

      // fine next space
      number_end = line.find(' ', number_start);

      // if space not matched, set to end of line
      if(number_end == std::string::npos)
      {
        number_end = line.length();
      }

      // convert string value to numerical value
      this_value = std::atof(
        line.substr(number_start,number_end-number_start).c_str()
      );

      // set next start position to current end position
      // plus 1 for extra space
      number_start = line.find_first_not_of(' ', number_end);

      // push number to output vector
      values.push_back(this_value);
    }
    while(number_start < line.length());


    return values;
  }

};

class board_setter
{
  public:

  // define board to set
  board_setter& set_board(board<tile>& board_in)
  {
    current_board = &board_in;

    return *this;
  }

  // specific named file readers
  board_setter& read_land_file(std::string const& filename)
  {
    board<double> temp_board = pgm_to_array(filename);

    if(current_board->get_height() == 0 || current_board->get_width() == 0)
    {
      current_board->resize(temp_board.get_width(), temp_board.get_height());
    }

    for(size_t column = 0; column < temp_board.get_width();  ++column)
    for(size_t row    = 0; row    < temp_board.get_height(); ++row   )
    {
      if(temp_board(column, row) == tile::water())
      {
        current_board->operator()(column, row).make_water();
      }
      else
      {
        current_board->operator()(column, row).make_land();
      }
    }

    return *this;
  }
  board_setter& read_hare_file(std::string const& filename)
  {
    board<double> temp_board = pgm_to_array(filename);

    if(current_board->get_height() == 0 || current_board->get_width() == 0)
    {
      current_board->resize(temp_board.get_width(), temp_board.get_height());
    }

    for(size_t column = 0; column < temp_board.get_width();  ++column)
    for(size_t row    = 0; row    < temp_board.get_height(); ++row   )
    {
      current_board->operator()(column, row).hare = temp_board(column, row);
    }

    return *this;
  }
  board_setter& read_puma_file(std::string const& filename)
  {
    board<double> temp_board = pgm_to_array(filename);

    if(current_board->get_height() == 0 || current_board->get_width() == 0)
    {
      current_board->resize(temp_board.get_width(), temp_board.get_height());
    }

    for(size_t column = 0; column < temp_board.get_width();  ++column)
    for(size_t row    = 0; row    < temp_board.get_height(); ++row   )
    {
      (*current_board)(column, row).puma = temp_board(column, row);
    }

    return *this;
  }

  board<double> pgm_to_array(std::string const& filename)
  {
    board<double> return_board;

    file_reader file;

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
          return_board(row, column) = line_values[column];
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


  private:

  board<tile> *current_board;

};
