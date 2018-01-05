#ifndef __REMOTE_PLAYER_H__
#define __REMOTE_PLAYER_H__

#include"AI.h"

class remote_player : public ai
{
 public:
  remote_player(int team, char * file, image *h, image **r, TCPsocket s);
  
  void set_up(board * b, stratego * g);
  int move(board *b, stratego *g);

 private:
  TCPsocket _sock;
  
};

#endif
