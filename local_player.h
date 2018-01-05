#ifndef __LOCAL_PLAYER__
#define __LOCAL_PLAYER__

#include"human.h"

class local_player : public human
{
 public:
  local_player(int team, char * file, image * h, image ** r, TCPsocket sock);
  ~local_player(){SDLNet_TCP_Close(_sock);}

  
 protected:
  virtual void send_pickup(int x, int y);
  virtual void send_putdown(int x, int y);
  virtual void send_motion(int x, int y);
  virtual void send_location(int id, int x, int y);
  virtual void send_move(int oldx, int oldy, int newx, int newy);
  virtual void send_done();
  
  void send();

  TCPsocket _sock;
  char _mess[1024];
};

#endif
