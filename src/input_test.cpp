#include "board_setter.h"
#include <iostream>
#include <fstream>
#include "board.h"
#include "tile.h"

/*
 * Define some test data
 */

std::string test_land_data(
  "5 5\n"
  "0 0 0 0 1\n"
  "1 1 1 0 1\n"
  "0 1 0 1 1\n"
  "1 0 1 0 1\n"
  "1 0 0 0 0\n"
);

double test_land_array[5][5] = {
  {0, 0, 0, 0, 1},
  {1, 1, 1, 0, 1},
  {0, 1, 0, 1, 1},
  {1, 0, 1, 0, 1},
  {1, 0, 0, 0, 0}
};

const char* test_land_filename = "../test_data/test_land_input.dat";


std::string test_hare_data(
  "5 5\n"
  "0  0 0 0 0.1\n"
  "3.8  8.4 2.5 0 1.2\n"
  "0 9.9 0 6.3 9.9\n"
  "0.92 0 7.5 0 4\n"
  "6.4 0 0 0 0\n"
);

double test_hare_array[5][5] = {
  {0, 0, 0, 0, 0.1},
  {3.8, 8.4, 2.5, 0, 1.2},
  {0, 9.9, 0, 6.3, 9.9},
  {0.92, 0, 7.5, 0, 4},
  {6.4, 0, 0, 0, 0}
};

const char* test_hare_filename = "../test_data/test_hare_input.dat";


std::string test_puma_data(
  "5 5\n"
  "  0 0 0 0 0.04  \n"
  "1.28 4.44 10.667 0 9.04\n"
  "0 8.01 0 4.55 0.9\n"
  "5.6 0 1.23 0 3.56\n"
  "7.77 0 0 0 0\n"
);

double test_puma_array[5][5] = {
  {0, 0, 0, 0, 0.04},
  {1.28, 4.44, 10.667, 0, 9.04},
  {0, 8.01, 0, 4.55, 0.9},
  {5.6, 0, 1.23, 0, 3.56},
  {7.77, 0, 0, 0, 0}
};

const char* test_puma_filename = "../test_data/test_puma_input.dat";


int main()
{
  Board<Tile> b;

  std::ofstream file;

  // set files
  file.open(test_land_filename);
  file << test_land_data;
  file.close();

  file.open(test_hare_filename);
  file << test_hare_data;
  file.close();

  file.open(test_puma_filename);
  file << test_puma_data;
  file.close();


  BoardSetter::set_land_from_file(b,test_land_filename);
  BoardSetter::set_hare_from_file(b,test_hare_filename);
  BoardSetter::set_puma_from_file(b,test_puma_filename);


  for(size_t x=0; x<b.get_width();  ++x)
  for(size_t y=0; y<b.get_height(); ++y)
  {
    if(b(x,y).is_land() != (test_land_array[y][x] == 1))
    {
      std::cout << "land array not properly set" << std::endl;
      std::cout << b(x,y).is_land() << ", " << test_land_array[y][x] << std::endl;
      return 1;
    }

    if(b(x,y).hare != test_hare_array[y][x])
    {
      std::cout << "hare array not properly set" << std::endl;
      std::cout << b(x,y).hare << ", " << test_hare_array[y][x] << std::endl;
      return 1;
    }

    if(b(x,y).puma != test_puma_array[y][x])
    {
      std::cout << "puma array not properly set" << std::endl;
      return 1;
    }
  }


  // all tests passed!
  return 0;
}
