#include "human.h"
#include "piece.h"
#include "stratego.h"

/*  name: constructor */
human::human(int team, char * filename, image *h, image **r)
  : player(team, filename, h, r)
{
}

/*   name: set up */
/*   desc: places the player's peices on the board. */
/*     places each piece one at a time. gets the x,y of a */
/*     peice, then places it on the board.   */
/*   params: board * b */
/*   return: void */
/*   1) place all pieces on the board in order */
/*   2) randomly swap two pieces 1000 times.  */
void human::set_up(board *b, stratego * g)
{
  int i;
  SDL_Event e;

  player::set_up(b,g);

  for ( i = 0; i < 40; i++)
    _pieces[i]->reveal();

  _quit = 0;
  _move = 0;
  
  while ( ! _quit )
  {
    while ( SDL_PollEvent(&e) )
    {
      if ( e.type == SDL_QUIT )
	exit(1);

      if ( e.type == SDL_MOUSEBUTTONDOWN )
	handle_set_up_mouse(&e, b);

      if ( e.type == SDL_KEYDOWN )
	handle_set_up_key(&e);

      if ( e.type == SDL_MOUSEMOTION )
	handle_set_up_motion(&e);
    }

    g->draw();
    if ( _move )
      _move->draw( g->get_screen(), _motionx, _motiony, 1);
    g->update();
  }

  send_setup();

}

void human::send_setup()
{
  int i;

  for (i = 0; i < 40; i++)
  {
    send_location(i,_pieces[i]->get_x(), _pieces[i]->get_y());
    SDL_Delay(10);
  }

  send_done();
}

void human::handle_set_up_mouse(SDL_Event *e, board *b)
{
  int x,y;
  piece * p;

  x = b->get_boardx( e->button.x );
  y = b->get_boardy( e->button.y );
  p = b->get_piece( x, y );
  
  if ( _move )
  {
    if ( p && p->get_team() == _team )
    {
      b->set_piece( x, y, _move );
      b->set_piece( _oldx, _oldy, p);
      _move = 0;
    }
    if ( x == _oldx && y == _oldy )
    {
      b->set_piece(x,y,_move);
      _move = 0;
    }
  }
  else
  {
    if ( p && p->get_team() == _team )
    {
      _oldx = x;
      _oldy = y;
      _motionx = e->button.x;
      _motiony = e->button.y;
      _move = p;
      b->set_piece(x,y,0);
    }
  }
}

void human::handle_set_up_key(SDL_Event *e)
{
  if ( e->key.keysym.sym == SDLK_RETURN )
    _quit = 1;
  if ( e->key.keysym.sym == SDLK_q )
    exit(0);
}

void human::handle_set_up_motion(SDL_Event *e)
{
  if ( _move )
  {
    _motionx = e->motion.x;
    _motiony = e->motion.y;
    send_motion(_motionx, _motiony);
  }
}


/*   name: move */
/*   desc: gets the x,y of piece and its new x,y */
/*   params: board *b */
/*   return: int - true if game won */
/*   1) allocate a mover object */
/*   2) call possible moves on all pieces. */
/*   3) pick on move at random from the move object */
/*   4) if game was won, return 1, else 0 */
int human::move(board *b, stratego * g)
{
 SDL_Event e;

  _quit = 0;
  _move = 0;
  _ret = 0;
  
  while ( ! _quit )
  {
    while ( SDL_PollEvent(&e) )
    {
      if ( e.type == SDL_QUIT )
	exit(1);

      if ( e.type == SDL_MOUSEBUTTONDOWN )
	handle_move_mouse(&e, b);

      if ( e.type == SDL_KEYDOWN )
	handle_move_key(&e);

      if ( e.type == SDL_MOUSEMOTION )
	handle_set_up_motion(&e);
    }

    g->draw();
    if ( _move )
      _move->draw( g->get_screen(), _motionx, _motiony, 1);
    g->update();
  }

  g->draw();
  g->update();

  return _ret;
}


void human::handle_move_mouse(SDL_Event *e, board *b)
{
  int x,y;
  piece * p;

  x = b->get_boardx( e->button.x );
  y = b->get_boardy( e->button.y );
  p = b->get_piece( x, y );
  
  if ( _move )
  {
    if (_oldx == x && _oldy == y)
    {
      b->set_piece(x,y,_move);
      _move = 0;
      send_putdown(x,y);
      return;
    }

    if ( _move->valid_move(x,y,b) )
    {
      b->set_piece(_oldx, _oldy, _move);
      _ret = b->move(_oldx, _oldy, x, y);
      _quit = 1;
      send_move(_oldx,_oldy,x,y);
    }
  }
  else
  {
    if ( p && p->get_team() == _team )
    {
      _oldx = x;
      _oldy = y;
      _motionx = e->button.x;
      _motiony = e->button.y;
      _move = p;
      b->set_piece(x,y,0);
      send_pickup(x,y);
    }
  }
}

void human::handle_move_key(SDL_Event *e)
{
  if ( e->key.keysym.sym == SDLK_q )
    exit(0);
}
