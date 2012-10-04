#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdlib.h>

template<class T>
class board
{
  public:

  board(size_t height_in, size_t width_in)
  {
    board_array = NULL;
    resize_board(height_in, width_in);
  }


  // return board position (x_pos,y_pos)
  T& operator()(size_t x_pos, size_t y_pos)
  {
    // have rightmost index contiguous in memory
    //   as is standard in C
    return board_array[x_pos*width + y_pos];
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


  private:

  // free old board, set height and width, allocate new board
  void resize_board(size_t height_in, size_t width_in)
  {
    // free old board
    delete[] board_array;

    // set new sizes
    height = height_in;
    width  = width_in;

    // make space for new board
    board_array = new T[height*width];
  }



  size_t height;
  size_t width;

  T* board_array;

};


#endif
