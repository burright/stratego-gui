#include "soldier.h"
#include "board.h"



/*    name: constructor */
/*    desc: sets the rank */
/*    params: rank */
/*    return: n/a    */
soldier::soldier(int team, int rank, image * h, image * r)
  : piece(team, h, r)
{
  _rank = rank;
}

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
int soldier::attack(piece * enemy)
{
  if ( enemy->is_flag() )
    return 1;
  if ( enemy->is_bomb() )
    return -1;

  soldier * s = (soldier*) enemy;

  if ( s->_rank < _rank )
    return -1;
  if ( s->_rank == _rank )
    return 0;
  
  return 1;
}

/*    name: possible moves */
/*    desc: checks left, right, up and down. */
/*      if the move is on on the board and ( empty or an enemy ) */
/*      then it is added to moves object.  */
/*    params: board * b, moves * m,     */
/*    return: void */
void soldier::possible_moves( board *b, moves *m )
{
  if ( b->valid_move( _x + 1, _y, _team ) )
    m->add_move(_x,_y, _x + 1, _y );

  if ( b->valid_move( _x - 1, _y, _team ) )
    m->add_move(_x,_y, _x - 1, _y );
  
  if ( b->valid_move( _x, _y - 1, _team ) )
    m->add_move(_x,_y, _x, _y - 1 );

  if ( b->valid_move( _x, _y + 1, _team ) )
    m->add_move(_x,_y, _x, _y + 1 );
  
}


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
int soldier::valid_move(int checkx, int checky, board * b)
{
  if ( ! b->valid_move(checkx, checky, _team) )
    return 0;

  int dx = abs( checkx - _x );
  int dy = abs( checky - _y );

  if ( dx+dy <= 1 )
    return 1;
  
  return 0;
}

