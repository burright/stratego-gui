#ifndef __BOARD_H__
#define __BOARD_H__

#include "cell.h"
#include "image.h"

#define ROWS 10 
#define COLS 10

class board : public image
{
 public:

  /*   name: constructor */
  /*   desc: allocate a 2d array of cell pointers, */
  /*         allocate the cell objects. */
  /* 	mark 8 of the cells as water */
  /*   params: none */
  /*   return: n/a */
  board(char * filename);

  /*   name: destructor */
  /*   desc: delete the cell objects */
  /*         delete the 2d array of cell pointers */
  /*   params: none */
  /*   return: n/a */
  ~board();

  /*   name: move */
  /*   desc: moves the piece at oldx, oldy to newx, newy */
  /*    if there is a battle, calls the battle method */
  /*   params: int oldx, int oldy, int newx, newy */
  /*   return: int - true if flag is attacked */
  int move(int oldx, int oldy, int newx, int newy);

  /*   name: battle */
  /*   desc: has the piece at attackerx,y attack the piece */
  /*     at defenderx,y.  returns true if the flag was attacked. */
  /*     removes dead pieces from the board.   */
  /*     if the attacker wins, attacker is moved to defenderx, */
  /*     defendery */
  /*   params: int attackerx, int attackery, */
  /*           int defenderx, int defendery */
  /*   return: int true if flag was attacked */
  int battle( int attackerx, int attackery,
	      int defenderx, int defendery);

  /*   name: reset */
  /*   desc: removes all the pieces from the board */
  /*   params: none */
  /*   return: void */
  void reset();
    

  /*   name: put */
  /*   desc: puts a peice on the board */
  /*   params: int x, int y, piece * p */
  /*   return: int - true if this is okay */
  int put(int x, int y, piece *p);


  /*   name: print */
  /*   desc: prints each cell of the board, row by row */
  /*   params: none */
  /*   return: void */
  void print();

  /*   name: valid_move */
  /*   desc: if x,y is not on the board, or water, or occupied */
  /*   by your teammate, then return false */
  /*   params: int x, int y, int team */
  /*   return: int - true if this is okay  */
  int valid_move(int x, int y, int team);

  piece * get_piece(int x, int y);

  int is_empty(int x, int y);
  
  void draw(screen * s, int x, int y, int center);

  int get_boardx(int mousex);
  
  int get_boardy(int mousey);

  void set_piece(int x, int y, piece * p);
  
 protected:

  cell *** _board;


};


#endif
