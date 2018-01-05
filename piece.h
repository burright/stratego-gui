#ifndef __PIECE_H__
#define __PIECE_H__

#include "common.h"
#include "moves.h"
#include "image.h"

class board;  // a forward declaration
// 1 penalty, is in the .h file, you may only refer to board *'s,
//   not board objects, and not board methods
// 2 penalty, is in the .cpp file, we MUST include the .h file

class piece
{
  
 public:

  /*  -methods */
  /*     name: constructor */
  /*     desc: sets the team */
  /*     params: int team // 1 for Blue , 0 for Red */
  /*     return: n/a */
  piece(int team, image *h, image * r);

  /*     name: place */
  /*     desc: sets the initial x,y of the piece */
  /*           sets reveal to false */
  /* 	  set alive to true */
  /*     params: int x, int y */
  /*     return: void */
  virtual void place(int x, int y);

  /*     name: move */
  /*     desc: sets the x,y to the new x,y */
  /*     params: int newx, newy */
  /*     return: void */
  /*     1) returns */
  virtual void move(int newx, int newy){ /* do nothing */  }
  
  /*     name: attack */
  /*     desc: takes in the oppenent as a parameter, */
  /*        returns true if I win, false if I lose.  */
  /*        sets reveal to true on both */
  /*        calls the take away method */
  /*        base class just returns */
  /*     params: piece * enemy */
  /*     return: int - 1 if this object wins, 0 if tie,  */
  /*       -1 if this object loses, -2 n/a */
  /*     abstract     */

  virtual int attack(piece * enemy)=0;
  	    
  /*     name: possible moves */
  /*     desc: calculates the range of possible moves */
  /*       base class just returns */
  /*     params: board * b, moves * m */
  /*     return: void */
  /*     1) returns  */
  virtual void possible_moves( board * b, moves * m) { }
  
  /*     name: valid_move */
  /*     desc: checks to see if the given move is valid */
  /*     params: int checkx, int checky, board * b */
  /*     return: int - true if valid */
  /*     return false */
  virtual int valid_move(int checkx, int checky, board * b) { return 0; }

  /*     name: reveal */
  /*     desc: sets _reavel to true */
  /*     params: none */
  /*     return: void */
  void reveal() { _reveal = 1; }

  /*     name: is_flag */
  /*     returns false */
  virtual int is_flag() { return 0; }

  /*     name: is_bomb */
  /*     returns false */
  
  virtual int is_bomb() { return 0; }
    
  /*     name: is_soldier */
  /*     returns false */

  virtual int is_soldier() { return 0; }

  /*     name: is_miner */
  /*     returns false */

  virtual int is_miner() { return 0; }
  

  /*     name: is_spy */
  /*     returns false */
  virtual int is_spy() { return 0; }

    /* name: set_dead */
  void set_dead() { _is_alive = 0; }
  
    /* name: get_is_alive */
  int get_is_alive() { return _is_alive; }
  
  int get_team() { return _team; }

  void reset();
  void set_xy(int x, int y);
  
  void draw(screen * s, int x, int y, int center=1);
  
  int get_boardx(int mousex);
  
  int get_boardy(int mousey);

  void set_piece(int x, int y, piece * p);
  
  int get_x(){return _x;}
  int get_y(){return _y;}
  
  
 protected:
  int _x,_y;
  int _is_alive;
  int _reveal;
  int _team;
  
  //gui
  image * _hidden;
  image * _revealed;

};

#endif
