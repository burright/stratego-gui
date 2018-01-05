#include "stratego.h"
#include "human.h"
#include "AI.h"
#include "local_player.h"
#include "remote_player.h"


stratego::stratego()
{
  _b = new board( (char*) "images/board/board.png");
  assert(_b);
  
  _screen = new screen(_b->get_height(), _b->get_width(),
		       32);
  assert(_screen);

  SDL_WM_SetCaption((char*) "Stratego", 
		    (char*) "Stratego");

  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
  {
    cerr<<"Error initializing SDL_mixer: "<<Mix_GetError()
	<<endl;
    exit(1);
  }

  atexit(Mix_CloseAudio);

  if (TTF_Init())
  {
    cerr<<"Could not init TTF library."<<TTF_GetError()<<endl;
    exit(1);
  }
  
  atexit(TTF_Quit);
  
  if (SDLNet_Init())
  {
    cerr<<"Could not init SDLNet. "<<SDLNet_GetError()<<endl;
    exit(1);
  }
  
  atexit(SDLNet_Quit);

  load_images();

    
  SDL_Color f;
  f.r = 255;
  f.g = 255;
  f.b = 255;

  _disp = new display((char*) "font/gearmyblockcaps.ttf",40,f);
  assert(_disp);

  //_disp->set_text((char*) "This is a Test message!!!");
		    
}

void stratego::load_images()
{
  _blue_hidden = new image((char*) "images/blue/hidden.png");
  assert(_blue_hidden);
  
  _red_hidden = new image((char*) "images/red/hidden.png");
  assert(_red_hidden);

  int i;
  char name[1024];

  for (i = 0; i < NUM_IMAGES; i++)
  {
    sprintf(name,"images/blue/reveal-%d.png",i + 1);
    _blue_reveal[i] = new image(name);
    assert(_blue_reveal[i]);

    sprintf(name,"images/red/reveal-%d.png",i + 1);
    _red_reveal[i] = new image(name);
    assert(_red_reveal[i]);
  }
}

stratego::~stratego()
{
  int i;
  
  delete _b;
  delete _screen;
  delete _disp;

  delete _blue_hidden;
  delete _red_hidden;
  
  for (i = 0; i < NUM_IMAGES; i++)
  {
    delete _blue_reveal[i];
    delete _red_reveal[i];
  }
}

void stratego::play_game()
{
  _b->reset();
  _disp->clear_text();
  
  while (choose_game() == 0)
  {
    draw();
    update();
    SDL_Delay(1000);
  }
  
  _disp->clear_text();

  set_title((char *) "Stratego - Blue's Turn");
  _blue->set_up(_b,this);
  set_title((char *) "Stratego - Red's Turn");
  _red->set_up(_b,this);

  while (1)
  {
    set_title((char *) "Stratego - Blue's Turn");
    if (_blue->move(_b,this))
    {
      _disp->set_text((char*)"Blue Wins!!");
      //cout<<"blue wins!"<<endl;
      break;
    }
    
    set_title((char *) "Stratego - Red's Turn");
    if (_red->move(_b,this))
    {
      _disp->set_text((char*)"Red Wins!!");
      //cout<<"red wins!"<<endl;
      break;
    }
  }

  set_title((char *) "Stratego");

  draw();
  update();
  delete _red;
  delete _blue;
  
  SDL_Delay(1000);
}

int stratego::play_again()
{
  SDL_Event e;

  _b->reset();
  
  _disp->set_text((char*)"Play again? y/n");
  draw();
  update();
  
  while (1)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
	return 0;
      if (e.type == SDL_KEYDOWN)
      {
	if (e.key.keysym.sym == SDLK_y)
	  return 1;
	if (e.key.keysym.sym == SDLK_n)
	  return 0;	
      }
    }
    
  }
}

void stratego::draw()
{
  _b->draw(_screen,0,0,0);
}

void stratego::update()
{
  _disp->draw(_screen);
  _screen->update();
}

screen * stratego::get_screen()
{
  return _screen;
}

int stratego::start_ai()
{
  _blue = new human(BLUE,(char*) "pieces.txt",_blue_hidden,_blue_reveal);
  assert(_blue);

  _red = new ai(RED,(char*) "pieces.txt",_red_hidden,_red_reveal);
  assert(_red);

  return 1;
}

int stratego::start_join()
{
  TCPsocket socket;
  IPaddress ipaddress;

  get_ip();

  if (SDLNet_ResolveHost(&ipaddress,_ip,PORT))
  {
    _disp->set_text(SDLNet_GetError());
    return 0;
  }

  socket = SDLNet_TCP_Open(&ipaddress);

  if (!socket)
  {
    _disp->set_text(SDLNet_GetError());
    return 0;
  }

  _blue = new remote_player(BLUE,(char*) "pieces.txt",_blue_hidden,
			    _blue_reveal,socket);
  assert(_blue);

  _red = new local_player(RED,(char*) "pieces.txt",_red_hidden,_red_reveal,
			  socket);
  assert(_red);
  
  _disp->set_text((char*) "Waiting for connection...");
  draw();
  update();

  return 1;
}

int stratego::start_host()
{
  IPaddress ipaddress;
  TCPsocket client, server;
  
  if (SDLNet_ResolveHost(&ipaddress,0,PORT))
  {
    _disp->set_text(SDLNet_GetError());
    return 0;
  }

  server = SDLNet_TCP_Open(&ipaddress);
  
  if (!server)
  {
    _disp->set_text(SDLNet_GetError());
    return 0;
  }
  
  _disp->set_text((char*) "Waiting for connection...");
  draw();
  update();

  do
  {
    client = SDLNet_TCP_Accept(server);
  } while (!client);

  _blue = new local_player(BLUE,(char*) "pieces.txt", _blue_hidden,
			   _blue_reveal,client);
  assert(_blue);
  
  _red = new remote_player(RED,(char*) "pieces.txt",_red_hidden,_red_reveal,
			   client);
  assert(_red);

  SDLNet_TCP_Close(server);

  return 1;
}

int stratego::choose_game()
{
  SDL_Event e;
  
  _disp->set_text((char*) "vs AI (a), Host (h), Join (j)");
  draw();
  update();

  while (1)
  {// start while (1)
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
	exit(0);
      if (e.type == SDL_KEYDOWN)
      {
	if (e.key.keysym.sym == SDLK_a)
	  return start_ai();
	if (e.key.keysym.sym == SDLK_h)
	  return start_host();
	if (e.key.keysym.sym == SDLK_j)
	  return start_join();
	if (e.key.keysym.sym == SDLK_q)
	  exit(0);		
      }
    }
  }// end while (1)
}

void stratego::get_ip()
{
  SDL_Event e;
  
  _disp->set_text((char*) "Host: ");
  draw();
  update();

  while (1)
  {// begin while(1)
    
    while (SDL_PollEvent(&e))
    {// begin poll
      
      if (e.type == SDL_QUIT)
	exit(0);
      
      if (e.type != SDL_KEYDOWN)
	continue;
      
      if (e.key.keysym.sym == SDLK_BACKSPACE)
      {
	_disp->del_char();
	if (strlen(_disp->get_text()) < strlen("Host: "))
	  _disp->set_text((char*) "Host: " );
	continue;
      }

      if (e.key.keysym.sym == SDLK_RETURN)
      {
	strcpy(_ip, _disp->get_text() + 6);
	return;
      }

      char c = (char) e.key.keysym.sym;
      _disp->add_char(c);
    }// end poll
    
    draw();
    update();
  }// end while(1)
}

void stratego::set_title(char * t)
{
  SDL_WM_SetCaption(t,t);
}
