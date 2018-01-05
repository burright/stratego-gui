#ifndef __MOVES_H__
#define __MOVES_H__

#include "common.h"


class moves
{
 public:
  
  /*   name: constructor */
  /*   desc: set _max_moves to zero */
  /*   params: none */
  /*   return: n/a */
  moves() { _max_moves = 0; }


  /*   name: get_max_moves */
  int get_max_moves() { return _max_moves; }

  /*   name: add_move */
  /*   desc: adds an oldx,y and a newx,y to the array */
  /*     and at index _max_moves.then adds one to max_moves */
  /*   params: int oldx, int oldy, int newx, int newy */
  /*   return: void */
  void add_move(int oldx, int oldy, int newx, int newy);
  

  /*   name: get_oldx */
  /*   desc: gets the oldx at position i */
  /*   params: int i */
  /*   return: int - oldx[i] */
  int get_oldx(int i) { return _oldx[i]; }

  /*   name: get_oldy */
  /*   desc: gets the oldy at position i */
  /*   params: int i */
  /*   return: int - oldy[i] */
  int get_oldy(int i) { return _oldy[i]; }

  /*   name: get_newx */
  /*   desc: gets the newx at position i */
  /*   params: int i */
  /*   return: int - newx[i] */
  int get_newx(int i) { return _newx[i]; }

  /*   name: get_newy */
  /*   desc: gets the newy at position i */
  /*   params: int i */
  /*   return: int - newy[i] */
  int get_newy(int i) { return _newy[i]; }

 protected:

      int _oldx[1000];
      int _oldy[1000];
      int _newx[1000];
      int _newy[1000];
      int _max_moves;
};


#endif
