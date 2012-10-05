#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdlib.h>
#include <vector>

template<class T>
class board : private std::vector<T>
{
  public:

  board() : height(0), width(0)
  {
  }

  board(size_t width_in, size_t height_in)
  {
    resize(width_in, height_in);
  }


  // return board position (x_pos,y_pos)
  T& operator()(size_t x_pos, size_t y_pos)
  {
    // have rightmost index contiguous in memory
    //   as is standard in C
    return std::vector<T>::operator[](y_pos*width + x_pos);
  }

  // get the height of the board
  size_t get_height()
  {
    return height;
  }

  // get the width of the board
  size_t get_width()
  {
    return width;
  }


  // free old board, set height and width, allocate new board
  void resize(size_t width_in, size_t height_in)
  {
    // set new sizes
    width  = width_in;
    height = height_in;

    std::vector<T>::resize(width*height);
  }


  private:

  size_t height;
  size_t width;

  std::vector<T> board_array;

};


#endif
