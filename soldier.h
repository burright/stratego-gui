#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "piece.h"

class soldier : public piece
{
 public:

  /*    name: constructor */
  /*    desc: sets the rank */
  /*    params: rank */
  /*    return: n/a    */
  soldier(int team, int rank, image * h, image * r);

  /*    name: attack */
  /*    desc: handles an attack */
  /*    params: piece * enemy */
  /*    return: int -  return 1 if this object wins */
  /*                   return 0 if tie */
  /* 		  return -1 if this object loses */
  /*    0) if enemy is a flag, return 1 */
  /*    1) if enemy is a bomb, return -1 */
  /*    2) if enemy's rank is less than this object's, return -1 */
  /*    3) if enemy's rank is equal to this object's, return 0 */
  /*    4) return 1 */
  int attack(piece * enemy);

  /*    name: possible moves */
  /*    desc: checks left, right, up and down. */
  /*      if the move is on on the board and ( empty or an enemy ) */
  /*      then it is added to moves object.  */
  /*    params: board * b, moves * m,     */
  /*    return: void */
  void possible_moves( board *b, moves *m );


  /*    name: valid_move */
  /*    desc: checks to see if the given x,y work */
  /*     on the board, and then if it make sense for the peice */
  /*    params: int checkx, int checky */
  /*    return: int - true if it makes sense */
  /*    1)  call the board's check method for checkx, and checky, */
  /*      if it returns false, return false */
  /*    2)  if the cehckx, and checky are to the left, right, up */
  /*    or down of the current position, return true */
  /*    3)  return false  */
  int valid_move(int checkx, int checky, board * b);


  /*    name: move */
  /*    desc: changes the object's x,y to the newx, newy */
  /*    params: int newx, int newy */
  /*    return: void */
  void move(int newx, int newy)
  {
    _x = newx;
    _y = newy;
  }


  /*    name: is_soldier */
  /*    return true */
  int is_soldier() { return 1; }
  
  int get_rank() { return _rank; }

 protected:

  int _rank;



};


#endif
