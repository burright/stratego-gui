

#include "cell.h"
#include "piece.h"


/*   name: constructor */
/*   desc: sets all members to zero */
/*   params: none */
/*   return: n/a */
cell::cell(int x, int y)
{
  _is_water = 0;
  _unit = 0;
  _x = x;
  _y = y;
}


void cell::set_piece(piece * p)
{ 
  _unit = p; 
  if ( p )
    p->set_xy(_x,_y);
}
