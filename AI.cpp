#include "AI.h"
#include "piece.h"
#include "moves.h"


/*  name: constructor */
ai::ai(int team, char * filename, image *h, image **r)
  : player(team, filename, h, r)
{
}

/*   name: move */
/*   desc: gets the x,y of piece and its new x,y */
/*   params: board *b */
/*   return: int - true if game won */
/*   1) allocate a mover object */
/*   2) call possible moves on all pieces. */
/*   3) pick on move at random from the move object */
/*   4) if game was won, return 1, else 0 */
int ai::move(board *b, stratego * g)
{
  moves possible;
  int i, num;

  for ( i = 0; i < 40; i ++ )
    if ( _pieces[i]->get_is_alive() )
      _pieces[i]->possible_moves(b, &possible);

  if (possible.get_max_moves() == 0)
    return 0;

  num = rand() % possible.get_max_moves();

  return b->move( possible.get_oldx(num),
		  possible.get_oldy(num),
		  possible.get_newx(num),
		  possible.get_newy(num) );
}
