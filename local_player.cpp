#include"local_player.h"

local_player::local_player(int team, char * file, image * h, image ** r, 
			   TCPsocket sock)
  : human(team, file, h,r)
{
  _sock = sock;
}

void local_player::send_pickup(int x, int y)
{
  sprintf(_mess,"pickup %d %d", x,y);
  
  send();
}

void local_player::send_putdown(int x, int y)
{
  sprintf(_mess,"putdown %d %d", x,y);
  send();
}

void local_player::send_motion(int x, int y)
{
  sprintf(_mess,"motion %d %d", x,y);
  send();
}

void local_player::send_location(int id, int x, int y)
{
  sprintf(_mess,"location %d %d %d",id,x,y);
  send();
}

void local_player::send_move(int oldx, int oldy, int newx, int newy)
{
  sprintf(_mess,"move %d %d %d %d",oldx ,oldy, newx, newy);
  SDL_Delay(100);
  send();
}

void local_player::send_done()
{
  sprintf(_mess,"done");
  send();
}
  
void local_player::send()
{
  int len, ret;
  
  len = strlen(_mess) + 1;

  ret = SDLNet_TCP_Send(_sock, _mess, len);
  
  if (ret < len)
  {
    cerr<<"Client disconnected....I quit!"<<endl;
    exit(1);
  }
}
