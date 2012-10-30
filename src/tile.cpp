#include "tile.h"

Tile::Tile(): hare(0), puma(0), land_type(0) {};

// land should be 1
// water should be 0
size_t Tile::water()
{
  return 0;
}
size_t Tile::land()
{
  return 1;
}

// check if tile is land
bool Tile::is_land()
{
  if(land_type == water())
  {
    return false;
  }
  else if(land_type == land())
  {
    return true;
  }

  // default false
  return false;
}

// set land types
void Tile::make_land()
{
  land_type = land();
}
void Tile::make_water()
{
  land_type = water();
}
