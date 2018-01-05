#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "board.h"

class stratego;

class player
{
 public:

/*   name: constructor */
/*   desc: sets the team number, */
/*    allocates an array of piece pointers, */
/*    and then allocates each of the player's  */
/*    pieces. flag first, then set up in order from 
      1's to 10's.   */
/*    then bombs, then flag.   */
/*   params: int team */
/*   return: n/a */
  player(int team, char * filename, image * h, image **r);


/*   name: destructor */
/*   desc: deletes the pieces, then the array.  */
/*   params: none */
/*   return: n/a */
  virtual ~player();

/*   name: set up */
/*   desc: places the player's peices on the board. */
/*     places each piece one at a time.   gets the x,y of a */
/*     peice, then places it on the board.   */
/*   params: board * b */
/*   return: void */
/*   abstract */
  virtual void set_up(board *b, stratego * g);


/*   name: move */
/*   desc: gets the x,y of piece and its new x,y */
/*   params: board *b */
/*   return: int - true if game won */
/*   abstract  */
  virtual int move(board *b, stratego * g)=0;

 protected:

  piece ** _pieces;
  int _team;

};

#endif
