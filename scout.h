#ifndef __SCOUT_H__
#define __SCOUT_H__

#include "soldier.h"

class scout : public soldier
{
 public:
  /*      name: constructor */
  /*      desc: calls the parent's constructor and passes a 9 */
  /*      params: none */
  /*      return: n/a */
  scout(int team, image * h, image * r);

  /*      name: possible moves */
  /*      desc: checks all moves in the same row and col */
  /*        as the piece */
  /*      params: board * b, moves * m */
  /*      1) check to see if all moves to the left are valid. */
  /*        stop at the first invalid move, and add valid moves */
  /*        to the moves object.  */
  /*      2) check to see if all moves to the right are valid. */
  /*        stop at the first invalid move, and add valid moves */
  /*        to the moves object.  */
  /*      3) check to see if all moves to the top are valid. */
  /*        stop at the first invalid move, and add valid moves */
  /*        to the moves object.  */
  /*      4) check to see if all moves to the bottom are valid. */
  /*        stop at the first invalid move, and add valid moves */
  /*        to the moves object.  */
  void possible_moves(board *b, moves *m);

  /*      name: valid moves */
  /*      desc: checks to see if the checkx, checky */
  /*        is on the same col or row as the piece. */
  /*        checks to see if the dest is empty or an enemy */
  /*        checks to see if all the squares between */
  /*        checkx, checky and the current position are empty.    */
  int valid_move(int checkx, int checky, board * b);


};

#endif
