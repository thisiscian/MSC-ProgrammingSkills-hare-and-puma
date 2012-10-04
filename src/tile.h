class tile
{
  public:

  tile(): hare(0), puma(0), land_type(0) {};

  // land should be 1
  // water should be 0
  size_t static water()
  {
    return 1;
  }
  size_t static land()
  {
    return 0;
  }

  // check if tile is land
  bool is_land()
  {
    if(land_type == water())
    {
      return false;
    }
    else if(land_type == land())
    {
      return true;
    }
  }

  // set land types
  void make_land()
  {
    land_type = land();
  }
  void make_water()
  {
    land_type = water();
  }


  // hare and puma densities
  double hare;
  double puma;


  private:

  int land_type;
};
