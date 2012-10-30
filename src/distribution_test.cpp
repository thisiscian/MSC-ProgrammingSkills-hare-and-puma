#include "distribution.h"
#include <iostream>

int main()
{
  // insert distribution tests here!

  // test DirectDistribution
  for(size_t i=0; i<10; ++i)
  for(size_t j=0; j<10; ++j)
  {
    // check pattern matches expected pattern
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
    // check pattern matches expected pattern
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
    // repeat random tests multiple times
    for(size_t r=0; r<100; ++r)
    {
      // check values remain within the default bounds
      double randval = RandomDistribution()(i,j);
      if(randval < 0 || randval > 1)
      {
        std::cerr << "RandomDistribution broken for empty init" << std::endl;
        return 1;
      }

      // check values remain within defined bounds
      double min=-2;
      double max=8;
      randval = RandomDistribution(min,max)(i,j);
      if(randval < min || randval > max)
      {
        std::cerr << "CheckerDistribution broken for max and min init" << std::endl;
        return 1;
      }
    }
  }

  return 0;
}
