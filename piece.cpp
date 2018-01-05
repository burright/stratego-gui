#include "piece.h"
#include "board.h"


piece::piece(int team, image *h, image * r)
{
  _team = team;
  _hidden = h;
  _revealed = r;
}

void piece::draw(screen * s, int x, int y, int center)
{
  if (_reveal)
    _revealed->draw(s,x,y,center);
  else
    _hidden->draw(s,x,y,center);
}

/*     name: place */
  /*     desc: sets the initial x,y of the piece */
  /*           sets reveal to false */
  /* 	  set alive to true */
  /*     params: int x, int y */
  /*     return: void */
void piece::place(int x, int y)
{
  _x = x;
  _y = y;
  _reveal = 0;
  _is_alive = 1;
}

void piece::reset()
{
  _reveal = 0;
  _is_alive = 1;
}

void piece::set_xy(int x, int y)
{
  _x = x;
  _y = y;
}
