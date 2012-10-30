#include "board.h"
#include "tile.h"
#include <iostream>

class DestructorTester
{
  public:
    DestructorTester(): destructor_tester(NULL)
    {
      destructor_tester = NULL;
    }

    ~DestructorTester()
    {
      if(destructor_tester != NULL)
      {
        *destructor_tester = true;
      }
    }

    bool *destructor_tester;
};


int test_getting_and_setting(Board<int> b)
{

  // ensure that board can be set and gotten
  // as expected
  for(size_t i=0; i<10; ++i)
  for(size_t j=0; j<20; ++j)
  {
    b(i,j) = i*20 + j;
  }

  for(size_t i=0; i<10; ++i)
  for(size_t j=0; j<20; ++j)
  {
    if(b(i,j) != (i*20 + j))
    {
      std::cerr << "Board not set or read correctly" << std::endl;
      return 1;
    }
  }

  return 0;
}

int main(void)
{
  // test empty initialization
  {
    Board<int> b;

    // test height and width
    if(b.get_width() != 0 || b.get_height() != 0)
    {
      std::cerr << "Empty initialization has non-zero height or width"
                << std::endl;
      return 1;
    }

    b.resize(10,20);

    // test height and width after resize
    if(b.get_width() != 10 || b.get_height() != 20)
    {
      std::cerr << "Empty initialization has non-zero height or width"
                << std::endl;
      return 1;
    }

    if( test_getting_and_setting(b) == 1)
    {
      return 1;
    }
    
  }

  // test nonzero initialization
  {
    Board<int> b(10,20);

    // height and width should be 10
    if(b.get_width() != 10 || b.get_height() != 20)
    {
      std::cerr << "Height or Width not set correctly" << std::endl;
      return 1;
    }

    if( test_getting_and_setting(b) == 1)
    {
      return 1;
    }
  }


  // destructor test
  {
    //quickly test DestructorTester
    {
      bool check = false;
      DestructorTester *d = new DestructorTester;

      d->destructor_tester = &check;

      delete d;

      if(check != true)
      {
        std::cerr << "DestructorTester class not working" << std::endl;
      }
    }

    // declare destructor testers and initialize them to false
    bool destructors[5][5];

    for(size_t i=0; i<5; ++i)
    for(size_t j=0; j<5; ++j)
    {
      destructors[i][j] = false;
    } 

    // simulate Board being called and then going out of scope
    {
      Board<DestructorTester> b(5,5);

      // assign destructor testers to each DestructorTester class
      for(size_t i=0; i<5; ++i)
      for(size_t j=0; j<5; ++j)
      {
        b(i,j).destructor_tester = &destructors[i][j];
      }
    }

    // test all destructors have been called
    for(size_t i=0; i<5; ++i)
    for(size_t j=0; j<5; ++j)
    {
      if( destructors[i][j] != true )
      {
        std::cerr << "Destructors not being called!" << std::endl;
        return 1;
      }
    } 

  }


  // everything passed
  return 0;
}
