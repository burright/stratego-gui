#ifndef __SCREEN_H__
#define __SCREEN_H__
#include<SDL.h>
#include<iostream>

using namespace std;

#include<stdlib.h>
#include<assert.h>

class screen
{
 public:

  screen(int h, int w, int bpp);
  ~screen();

  // access methods
  int get_height() { return _height; }
  int get_width() { return _width; }
  int get_pixel_depth() {return _pixel_depth;}
  SDL_Surface * get_screen() {return _screen; }
  
  void update();

 private:

  int _height, _width, _pixel_depth;

  SDL_Surface * _screen;
};

#endif
