
#include "board.h"
#include "piece.h"

/*   name: constructor */
/*   desc: allocate a 2d array of cell pointers, */
/*         allocate the cell objects. */
/* 	mark 8 of the cells as water */
/*   params: none */
/*   return: n/a */
board::board(char * filename)
  : image(filename)
{
  int i,j;

  _board = new cell**[COLS];
  assert(_board);

  for ( i = 0; i < COLS; i ++ )
  {
    _board[i] = new cell*[ROWS];
    assert(_board[i]);
  }

  for ( i = 0; i < COLS; i ++ )
    for ( j = 0; j < ROWS; j ++ )
    {
      _board[i][j] = new cell(i,j);
      assert( _board[i][j] );
    }
  
  _board[2][4]->set_water();
  _board[3][4]->set_water();
  _board[2][5]->set_water();
  _board[3][5]->set_water();

  _board[6][4]->set_water();
  _board[7][4]->set_water();
  _board[6][5]->set_water();
  _board[7][5]->set_water();

}

/*   name: destructor */
/*   desc: delete the cell objects */
/*         delete the 2d array of cell pointers */
/*   params: none */
/*   return: n/a */
board::~board()
{
  int i,j;

    for ( i = 0; i < COLS; i ++ )
    {
      for ( j = 0; j < ROWS; j ++ )
	delete _board[i][j];

      delete [] _board[i];
    }

    delete [] _board;
}

/*   name: move */
/*   desc: moves the piece at oldx, oldy to newx, newy */
/*    if there is a battle, calls the battle method */
/*   params: int oldx, int oldy, int newx, newy */
/*   return: int - true if flag is attacked */
int board::move(int oldx, int oldy, int newx, int newy)
{
  piece * me, * you;

  me = _board[oldx][oldy]->get_piece();
  you = _board[newx][newy]->get_piece();

  if ( you )
    return battle(oldx,oldy,newx,newy);

  _board[oldx][oldy]->set_piece(0);
  _board[newx][newy]->set_piece(me);

  return 0;
}

/*   name: battle */
/*   desc: has the piece at attackerx,y attack the piece */
/*     at defenderx,y.  returns true if the flag was attacked. */
/*     removes dead pieces from the board.   */
/*     if the attacker wins, attacker is moved to defenderx, */
/*     defendery */
/*   params: int attackerx, int attackery, */
/*           int defenderx, int defendery */
/*   return: int true if flag was attacked */
int board::battle( int attackerx, int attackery,
		   int defenderx, int defendery)
{
  piece * me, * you;
  int result;

  me = _board[attackerx][attackery]->get_piece();
  you = _board[defenderx][defendery]->get_piece();

  result = me->attack(you);

  if ( result == 1 ) //me win
  {
    you->set_dead(); // the loser is DEAD

    // me leave here
    _board[attackerx][attackery]->set_piece(0); 

    // me arrive here
    _board[defenderx][defendery]->set_piece(me);

    // everyone can se me
    me->reveal();
  }
  else if ( result == 0 ) // me tie
  {
    // in case of a tie, everyone dies
    you->set_dead();
    me->set_dead();

    // me dead
    _board[attackerx][attackery]->set_piece(0); 

    // you dead
    _board[defenderx][defendery]->set_piece(0);
  }
  else // result is -1 // me lose
  {
    me->set_dead(); // the loser is DEAD
    
    // me leave here
    _board[attackerx][attackery]->set_piece(0); 

    // everyone can se me
    you->reveal();
  }
    
  return you->is_flag();
}

/*   name: reset */
/*   desc: removes all the pieces from the board */
/*   params: none */
/*   return: void */
void board::reset()
{
  int i,j;

  for ( i = 0; i < COLS; i ++ )
    for ( j = 0; j < ROWS; j ++ )
      _board[i][j]->set_piece(0);
}


/*   name: put */
/*   desc: puts a peice on the board */
/*   params: int x, int y, piece * p */
/*   return: int - true if this is okay */
int board::put(int x, int y, piece *p)
{
  if ( p->get_team() == BLUE )
  {
    if ( x < 0 || x >= COLS || y >= ROWS || y < 6 )
      return 0;
  }

  if ( p->get_team() == RED )
  {
    if ( x < 0 || x >= COLS || y >= 4 || y < 0 )
      return 0;
  }

  if ( _board[x][y]->is_occupied() )
    return 0;
  
  _board[x][y]->set_piece(p);
  
  return 1;
}


/*   name: valid_move */
/*   desc: if x,y is not on the board, or water, or occupied */
/*   by your teammate, then return false */
/*   params: int x, int y, int team */
/*   return: int - true if this is okay  */

int board::valid_move(int x, int y, int team)
{
  if ( x < 0 || x >= COLS )
    return 0;

  if ( y < 0 || y >= ROWS )
    return 0;
  
  if ( _board[x][y]->is_water() )
    return 0;

  piece * p = _board[x][y]->get_piece();

  if ( p && p->get_team() == team )
    return 0;

  return 1;
}

       
       
      
piece * board::get_piece(int x, int y)
{
  assert( x >= 0 && x < COLS && y >= 0 && y < ROWS );

  return _board[x][y]->get_piece();
}




int board::is_empty(int x, int y)
{
  assert( x >= 0 && x < COLS && y >= 0 && y < ROWS );

  return ! _board[x][y]->is_water() &&
    _board[x][y]->get_piece() == 0;
}

void board::draw(screen * s, int x, int y, int center)
{
  int c,r;
  int h = get_height() / ROWS;
  int w = get_width() / COLS;
  piece * p;
  
  if (center)
  {
    x -= get_width() / 2;
    y -= get_height() / 2;
  }

  image::draw(s,x,y,0);
  
  for (r = 0; r < ROWS; r++)
    for (c = 0; c < COLS; c++)
    {
      p = _board[c][r]->get_piece();
      
      if (p)
	p->draw(s,x+c*w,y+r*h,0);
    }
}

int board::get_boardx(int mousex)
{
  return mousex / (get_width() / COLS);
}
  
int board::get_boardy(int mousey)
{
  return mousey / (get_height() / ROWS);
}

void board::set_piece(int x, int y, piece * p)
{
  _board[x][y]->set_piece(p);
}
