#ifndef __TILE_H__
#define __TILE_H__

#include <stdlib.h>

class Tile
{
  public:

  Tile();

  // returns land or water value
  size_t static water();
  size_t static land();

  // test if tile is land
  bool is_land();

  // set land types
  void make_land();
  void make_water();

  // hare and puma densities
  double hare;
  double puma;

  private:

  int land_type;
};

#endif
