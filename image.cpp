#include "image.h"


image::image( char * filename )
{
  _img = IMG_Load( filename );

  if ( ! _img )
  {
    cerr<<"Could not load "<<filename<<": "<<SDL_GetError()
	<<endl;
    exit(1);
  }

  _src.w = _img->w;
  _src.h = _img->h;
  _src.x = 0;
  _src.y = 0;

  _dest = _src;
}

image::~image()
{
  SDL_FreeSurface(_img);
}

void image::draw(screen * s, int x, int y, int center)
{
  _dest.x = x;
  _dest.y = y;

  if ( center )
  {
    _dest.x -= _img-> w / 2;
    _dest.y -= _img-> h / 2;
  }

  SDL_BlitSurface(_img, &_src, s->get_screen(), &_dest);
}
