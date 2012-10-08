#include "distribution.h"
#include <iostream>

int main()
{
  // insert distribution tests here!

  // test DirectDistribution
  for(size_t i=0; i<10; ++i)
  for(size_t j=0; j<10; ++j)
  {
    if(DirectDistribution<size_t>(20, 40)(i,j) != 20*i + 40*j)
    {
      std::cerr << "DirectDistribution broken" << std::endl;
      return 1;
    }
  }

  // test CheckerDistribution
  for(size_t i=0; i<10; ++i)
  for(size_t j=0; j<10; ++j)
  {
    if(CheckerDistribution()(i,j) != ((i+j)%2 == 0))
    {
      std::cerr << "CheckerDistribution broken" << std::endl;
      return 1;
    }
  }

  // test RandomDistribution
  for(size_t i=0; i<10; ++i)
  for(size_t j=0; j<10; ++j)
  {
    double randval = RandomDistribution()(i,j);
    if(randval < 0 || randval > 1)
    {
      std::cerr << "RandomDistribution broken for empty init" << std::endl;
      return 1;
    }

    double min=-2;
    double max=8;
    randval = RandomDistribution(min,max)(i,j);
    if(randval < min || randval > max)
    {
      std::cerr << "CheckerDistribution broken for max and min init" << std::endl;
      return 1;
    }
  }

  return 0;
}
