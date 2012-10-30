#include <tile.h>
#include <iostream>

int main(void)
{
  Tile t;

  /*
   * checking getting and setting of tile types
   */

  /*
   * checking hare and puma settings
   */

  t.hare = 0.06;
  t.puma = 10.2;

  if(t.hare != 0.06)
  {
    std::cerr << "hare not set properly" << std::endl;
    return 1;
  }

  if(t.puma != 10.2)
  {
    std::cerr << "puma not set properly" << std::endl;
    return 1;
  }


  /*
   * checking land types
   */ 

  // land and water should be different
  if(Tile::land() == Tile::water())
  {
    std::cerr << "land and water are the same!!" << std::endl;
    return 1;
  }

  // check land setting
  t.make_land();
  if(!t.is_land())
  {
    std::cerr << "t was set to land, but doesn't recognize this" << std::endl;
    return 1;
  }

  //check water setting
  t.make_water();
  if(t.is_land())
  {
    std::cerr << "t was set to water, but doesn't recognize this" << std::endl;
    return 1;
  }

  return 0;
}
