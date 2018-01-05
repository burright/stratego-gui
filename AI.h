#ifndef __AI_H__
#define __AI_H__

#include "player.h"


class ai : public player
{
 public:

  /*  name: constructor */
  ai(int team, char * filename, image *h, image **r);

  /*   name: move */
  /*   desc: gets the x,y of piece and its new x,y */
  /*   params: board *b */
  /*   return: int - true if game won */
  /*   1) allocate a mover object */
  /*   2) call possible moves on all pieces. */
  /*   3) pick on move at random from the move object */
  /*   4) if game was won, return 1, else 0 */
  int move(board *b, stratego *g);
};


#endif
