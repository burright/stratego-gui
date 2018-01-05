#include "spy_miner.h"
#include "board.h"
 
// board.h in scout?

/*  name: constructor */
/*   desc: calls the parent's contructor and passes it an */
/*    8. */
/*   params: none */
/*   return: n/a */
miner::miner(int team, image * h, image * r)
  : soldier(team, 8, h, r)
{
}

  /*   name: attack */
  /*   desc: if attacking a mine, return 1, */
  /*   else call the parent's method */
  /*   params: piece * enemy */
int miner::attack(piece * enemy)
{
  if ( enemy->is_bomb() )
    return 1;

  return soldier::attack(enemy);
}


  /*  name: constructor */
  /*   desc: calls the parent's contructor and passes it an */
  /*    10. */
  /*   params: none */
  /*   return: n/a */
spy::spy( int team, image * h, image * r )
  : soldier(team, 10, h, r)
{
}

  /*   name: attack */
  /*   desc: if attacking a 1, return 1, */
  /*   else call the parent's method */
  /*   params: piece * enemy */
int spy::attack(piece * enemy)
{
  if ( enemy->is_soldier() )
  {
    soldier * s = (soldier*) enemy;

    if ( s->get_rank() == 1 )
      return 1;
  }

  return soldier::attack(enemy);
}

