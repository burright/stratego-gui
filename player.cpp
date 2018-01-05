#include"player.h"
#include<iomanip>
#include<fstream>
#include<string.h>
#include "soldier.h"
#include "boom_flag.h"
#include "spy_miner.h"
#include "scout.h"

/*   name: constructor */
/*   desc: sets the team number, */
/*    allocates an array of piece pointers, */
/*    and then allocates each of the player's  */
/*    pieces. flag first, then set up in order from 
      1's to 10's.   */
/*    then bombs, then flag.   */
/*   params: int team */
/*   return: n/a */

/* input file will consist of 40 lines....
each line is a type of piece to be found in the game...
soldier 1
soldier 2
soldier 3
soldier 3
soldier 4
soldier 4
soldier 4
..
..
miner
scout
spy
bomb
flag
*/
player::player(int team, char * filename, image * h, image **r)
{
  _team = team;

  _pieces = new piece*[40];
  assert(_pieces);

  ifstream in(filename, ios::in);
  if ( ! in )
  {
    cerr<<"Could not open "<<filename<<endl;
    exit(1);
  }

  int i, rank;
  char type[1024];

  for ( i = 0; i < 40; i ++ )
  {
    in>>type;

    if ( strcmp(type, "soldier") == 0 )
    {
      in>>rank;
      _pieces[i] = new soldier(team, rank, h, r[rank-1]);
    }
    else if ( strcmp(type, "miner") == 0 )
      _pieces[i] = new miner(team,h, r[MINER_R]);
    else if ( strcmp(type, "bomb") == 0 )
      _pieces[i] = new bomb(team,h, r[BOMB_R]);
    else if ( strcmp(type, "spy") == 0 )
      _pieces[i] = new spy(team,h, r[SPY_R]);
    else if ( strcmp(type, "flag") == 0 )
      _pieces[i] = new flag(team,h, r[FLAG_R]);
    else if ( strcmp(type, "scout") == 0 )
      _pieces[i] = new scout(team,h, r[SCOUT_R]);

    assert(_pieces[i]);
  }

  in.close();
}


/*   name: destructor */
/*   desc: deletes the pieces, then the array.  */
/*   params: none */
/*   return: n/a */
player::~player()
{
  int i;

  for ( i = 0; i < 40; i ++ )
    delete _pieces[i];

  delete [] _pieces;
}

/*   name: set up */
/*   desc: places the player's peices on the board. */
/*     places each piece one at a time. gets the x,y of a */
/*     peice, then places it on the board.   */
/*   params: board * b */
/*   return: void */
/*   1) place all pieces on the board in order */
/*   2) randomly swap two pieces 1000 times.  */
void player::set_up(board *b, stratego * g)
{
  int i, r, c;

  for ( i = 0; i < 40; )
  {
    r = rand() % 4 + _team * 6;
    c = rand() % COLS;
    
    _pieces[i]->reset();
    if ( b->put(c, r, _pieces[i]) )
      i++;
  }
}

