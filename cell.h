#ifndef __CELL_H__
#define __CELL_H__

#include "common.h"

class piece;

class cell
{
 public:

  /*   name: constructor */
  /*   desc: sets all members to zero */
  /*   params: none */
  /*   return: n/a */
  cell(int x, int y);


  /*   name: set_water */
  void set_water() { _is_water = 1; }

  /*   name: is_occupied */
  int is_occupied() { return _unit != 0; }

  /*   name: is_water */
  int is_water() { return _is_water; }

  /*   name: set_piece */
  void set_piece(piece * p); 

  /*   name: get_piece */
  piece* get_piece() { return _unit; }

  /*   name: print */
  /*   desc: if water, print ww */
  /*         if empty, print oo */
  /*         else call the peice's print method */
  /*   params: none */
  /*   return: void */
  void print();

 protected:

  int _x, _y;
  int _is_water; 
  piece * _unit; // set to zero for unoccupied */

};


#endif 
