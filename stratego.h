#ifndef __STRATEGO_H__
#define __STRATEGO_H__

#include "image.h"
#include "board.h"
#include "player.h"
#include "display.h"
#include <SDL_mixer.h>

#define NUM_IMAGES 12
#define PORT 5000

class stratego
{
 public:

  stratego();
  ~stratego();

  void play_game();
  int play_again();

  void draw();
  void update();
  screen * get_screen();

 private:

  // needed for networking
  int start_ai();
  int start_join();
  int start_host();
  int choose_game();
  void get_ip();
  void set_title(char * t);
  
  void load_images();

  screen * _screen;
  
  board * _b;
  
  player * _blue;
  player * _red;

  display * _disp;

  //images...
  image * _blue_hidden;
  image * _red_hidden;

  image * _blue_reveal[NUM_IMAGES];
  image * _red_reveal[NUM_IMAGES];

  char _ip[64];
};


#endif
