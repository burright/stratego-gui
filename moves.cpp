#include "moves.h"


/*   name: add_move */
/*   desc: adds an oldx,y and a newx,y to the array */
/*     and at index _max_moves.then adds one to max_moves */
/*   params: int oldx, int oldy, int newx, int newy */
/*   return: void */
void moves::add_move(int oldx, int oldy, int newx, int newy)
{
  assert( _max_moves < 1000 );
  _oldx[_max_moves] = oldx;
  _oldy[_max_moves] = oldy;
  _newx[_max_moves] = newx;
  _newy[_max_moves] = newy;

  _max_moves++;
}

