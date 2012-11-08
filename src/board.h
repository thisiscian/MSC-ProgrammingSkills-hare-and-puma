#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>

/*
 * Board class for storing elements as a 2d array to emulate a game board.
 *
 *   Useage:
 *    Board board<MyClass>(x_width, y_width);
 *
 *    // Set element x,y of the board to MyClass(value)
 *    board(x,y) = MyClass(value);
 *
 *    // Retrieve element x,y of the board
 *    MyClass my_class = board(x,y);
 *
 */

#include <stdlib.h>
#include <vector>

template<class T>
class Board
{
  public:

  // Empty initializer sets height and width to zero.
  Board() : _height(0), _width(0)
  {
  }

  // Initialization with height and width allocate height*width elements
  //  on the board.
  Board(size_t width_in, size_t height_in)
  {
    resize(width_in, height_in);
  }


  // get reference to value at board position (x_pos,y_pos)
  T& operator()(size_t x_pos, size_t y_pos)
  {
    // have rightmost index contiguous in memory
    //   as is standard in C
    return _board[x_pos*_height + y_pos];
  }

  // get the height of the board
  size_t get_height()
  {
    return _height;
  }

  // get the width of the board
  size_t get_width()
  {
    return _width;
  }


  // resize the board to size width_in*height_in
  void resize(size_t width_in, size_t height_in)
  {
    // set new sizes
    _width  = width_in;
    _height = height_in;

    size_t new_size = _width*_height;

    _board.resize(new_size);
  }


  private:

  size_t _height;
  size_t _width;
  std::vector<T> _board;

};


#endif
