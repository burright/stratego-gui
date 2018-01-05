
#include "screen.h"



screen::screen(int h, int w, int bpp)
  : _height(h), _width(w), _pixel_depth(bpp)
{  // do init list

  if ( SDL_Init( SDL_INIT_VIDEO ) )
  {
    cerr<<"Could not init: "<<SDL_GetError()<<endl;
    exit(1);
  }

  atexit(SDL_Quit);

  _screen = SDL_SetVideoMode( _width, _height, _pixel_depth,0);
  
  if ( ! _screen )
  {
    cerr<<"Could not set video mode: "<<SDL_GetError()<<endl;
    exit(1);
  }
  
}

screen::~screen()
{
}

void screen::update()
{
  SDL_UpdateRect(_screen, 0,0,0,0);
}

/* image, sprite, screen saver */
