#include "board.h"
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

  // everything passed
  return 0;
}