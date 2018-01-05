#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <SDL.h>
#include <iostream>

using namespace std;

#include <stdlib.h>
#include <SDL_image.h>
#include "screen.h"


class image
{
 public:

  image( char * filename );
  virtual ~image();

  virtual void draw(screen * s, int x, int y, int center=1);

  int get_width() { return _img->w; }
  int get_height() { return _img->h; }

 protected:

  SDL_Rect _src, _dest;
  SDL_Surface * _img;
};

#endif
