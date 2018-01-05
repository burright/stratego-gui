#include"remote_player.h"
#include"stratego.h"
#include"piece.h"
#include<sstream>

remote_player::remote_player(int team, char * file, image *h, image **r, 
			     TCPsocket s)
  : ai(team,file,h,r)
{
  _sock = s;
}
  
void remote_player::set_up(board * b, stratego * g)
{
  int res, i, x, y, id;
  piece * p;
  char mess[1024];
  char action[1024];
  
  for (i = 0; i < 40; i++)
    _pieces[i]->reset();

  while (1)
  {// start while(1)
    res = SDLNet_TCP_Recv(_sock,mess,1024);
    
    if (res <= 0)
    {
      cerr<<"Client disconnected"<<endl;
      exit(1);
    }

    istringstream in(mess);
    
    in>>action;

    if (strcmp(action, "motion") == 0)
      continue;

    if (strcmp(action, "done") == 0)
      break;
    
    in>>id;
    in>>x;
    in>>y;
    
    p = _pieces[id];
    
    b->set_piece(x,y,p);
  }// end while(1)
  
  g->draw();
  g->update();
}

int remote_player::move(board *b, stratego *g)
{
  int res, oldx, oldy, x, y;
  piece * p;
  char mess[1024];
  char action[1024];

  while (1)
  {// start while(1)
    g->draw();
    
    res = SDLNet_TCP_Recv(_sock, mess, 1024);
    
    if (res <= 0)
    {
      cerr<<"disconnect"<<endl;
      exit(1);
    }

    istringstream in(mess);
    
    in>>action;

    if (strcmp(action,"pickup") == 0)
    {
      in>>oldx;
      in>>oldy;

      p = b->get_piece(oldx,oldy);
      b->set_piece(oldx,oldy,0);
    }

    else if (strcmp(action,"putdown") == 0)
    {
      in>>oldx;
      in>>oldy;
      
      b->set_piece(oldx,oldy,p);
      p = 0;
      g->draw();
    }
    
    else if (strcmp(action,"motion") == 0)
    {
      in>>x;
      in>>y;
      cout<<"x: "<<x<<" y: "<<y<<endl;
      if (p && p->get_is_alive())
	p->draw(g->get_screen(),x,y,1);
    }
    
    else if (strcmp(action,"move") == 0)
    {
      in>>oldx;
      in>>oldy;
      in>>x;
      in>>y;
      
      b->set_piece(oldx,oldy,p);
      p = 0;

      return b->move(oldx,oldy,x,y);
    }
    
    g->update();
    
  }// end while(1)
}
