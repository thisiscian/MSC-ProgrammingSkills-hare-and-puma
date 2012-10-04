#include "board.h"
#include "tile.h"
#include <iostream>

struct two_dee
{
  size_t x;
  size_t y;
};

int main(void)
{
  board<two_dee> b(10,10);

  // ensure that board can be set and gotten
  // as expected
  for(size_t i=0; i<10; ++i)
  for(size_t j=0; j<10; ++j)
  {
    b(i,j).x = i;
    b(i,j).y = j;
  }

  for(size_t i=0; i<10; ++i)
  for(size_t j=0; j<10; ++j)
  {
    if(b(i,j).x != i || b(i,j).y != j)
    {
      // test failed!
      return 1;
    }
  }

  // height and width should be 10
  if(b.get_height() != 10 || b.get_width() != 10)
  {
    // test failed!
    return 1;
  }


  /*
   * Testing board<tile> type
   */

  board<tile> tile_board(5,6);

  // height and width should be 10
  if(tile_board.get_height() != 5 || tile_board.get_width() != 6)
  {
    // test failed!
    std::cout << "get_height and get_width not working" << std::endl;
    return 1;
  }

  // ensure that tile_board can be set and gotten
  // as expected
  for(size_t i=0; i<tile_board.get_height(); ++i)
  for(size_t j=0; j<tile_board.get_width(); ++j)
  {
    tile_board(i,j).hare = i;
    tile_board(i,j).puma = j;
  }

  for(size_t i=0; i<tile_board.get_height(); ++i)
  for(size_t j=0; j<tile_board.get_width(); ++j)
  {
    if(tile_board(i,j).hare != i || tile_board(i,j).puma != j)
    {
      // test failed!
      std::cout << "tile_board not set or read properly" << std::endl;
      return 1;
    }
  }

  //checking water and land declarations
  // land and water should be different
  if(tile::land() == tile::water())
  {
    std::cout << "land and water are the same!!" << std::endl;
    return 1;
  }

  //checking getting and setting of tile types
  tile t;

  // check land setting
  t.make_land();
  if(!t.is_land())
  {
    std::cout << "t was set to land, but doesn't recognize this" << std::endl;
    return 1;
  }

  //check water setting
  t.make_water();
  if(t.is_land())
  {
    std::cout << "t was set to water, but doesn't recognize this" << std::endl;
    return 1;
  }



  // everything passed
  return 0;
}
