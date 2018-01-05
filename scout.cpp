
#include "scout.h"
#include "board.h"

/*      name: constructor */
/*      desc: calls the parent's constructor and passes a 9 */
/*      params: none */
/*      return: n/a */
scout::scout(int team, image * h, image * r)
  : soldier(team, 9, h, r)
{
}

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
void scout::possible_moves(board *b, moves *m)
{
  int dx, dy, testx, testy;

  // up
  dx = 0;
  dy = -1;

  for ( testx = _x + dx, testy = _y + dy;
	valid_move(testx, testy, b);
	testx += dx, testy += dy)
    m->add_move(_x,_y, testx, testy);

  // down
  dx = 0;
  dy = 1;

  for ( testx = _x + dx, testy = _y + dy;
	valid_move(testx, testy, b);
	testx += dx, testy += dy)
    m->add_move(_x,_y, testx, testy);

  // left
  dx = -1;
  dy = 0;

  for ( testx = _x + dx, testy = _y + dy;
	valid_move(testx, testy, b);
	testx += dx, testy += dy)
    m->add_move(_x,_y, testx, testy);

  // right
  dx = 1;
  dy = 0;

  for ( testx = _x + dx, testy = _y + dy;
	valid_move(testx, testy, b);
	testx += dx, testy += dy)
    m->add_move(_x,_y, testx, testy);
  
}

/*      name: valid moves */
/*      desc: checks to see if the checkx, checky */
/*        is on the same col or row as the piece. */
/*        checks to see if the dest is empty or an enemy */
/*        checks to see if all the squares between */
/*        checkx, checky and the current position are empty.    */
int scout::valid_move(int checkx, int checky, board * b)
{
  int dx, dy;

  if ( _x == checkx && _y == checky )
    return 0;

    if ( _x != checkx && _y != checky )
    return 0;

  if ( ! b->valid_move(checkx, checky, _team) )
    return 0;

  int testx, testy;

  dx = checkx - _x;
  dy = checky - _y;

  if ( dx )
    dx /= abs( dx );

  if ( dy )
    dy /= abs( dy );

  for ( testx = _x + dx, testy = _y + dy;
	testx != checkx || testy != checky; 
	testx += dx, testy += dy)
    if ( ! b->is_empty( testx, testy ) )
    {
      return 0;
    }


  return 1;
}
