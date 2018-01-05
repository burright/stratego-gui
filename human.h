#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "player.h"

class human : public player
{
 public:

  /*   name: constructor */
  human(int team, char *file, image *h, image **r);
  /*    name: set up */
  /*   desc: places the player's peices on the board. */
  /*     places each piece one at a time. gets the x,y of a */
  /*     peice, then places it on the board.   */
  /*   params: board * b */
  /*   return: void */
  /*   1) for each piece, ask the user for an x and a y, and */
  /*    place it on the board */
  void set_up(board *b, stratego *g);
    
  /*   name: move */
  /*   desc: gets the x,y of piece and its new x,y */
  /*   params: board *b */
  /*   return: int - true if game won */
  /*   1) get an oldx, oldy, newx, newy from the user. */
  /*   2) if this is a valid move, make it.  */
  /*   3) if the game was won, return 1, else return 0 */
  int move(board *b, stratego *g);

 protected:

  virtual void send_pickup(int x, int y){}
  virtual void send_putdown(int x, int y){}
  virtual void send_motion(int x, int y){}
  virtual void send_location(int id, int x, int y){}
  virtual void send_move(int oldx, int oldy, int newx, int newy){}
  virtual void send_done(){}

  void send_setup();

  void handle_set_up_mouse(SDL_Event *e, board *b);
  void handle_set_up_key(SDL_Event *e);
  void handle_set_up_motion(SDL_Event *e);
  void handle_move_mouse(SDL_Event *e, board *b);
  void handle_move_key(SDL_Event *e);
  

  int _quit, _motionx, _motiony, _oldx, _oldy, _ret;
  piece * _move;


};

#endif
