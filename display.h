#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include"common.h"
#include"screen.h"
#include"array.h"


class display
{
 public:
  display(char * font, int pt_size, SDL_Color fg);
  
  virtual ~display();
  
  virtual void draw(screen * s);
  virtual void set_text(char * txt);
  virtual void clear_text();

  char * get_text(){return _msg.get_data();}

  virtual void add_char(char c);
  virtual void del_char();
  
 protected:
  SDL_Color _fg;
  TTF_Font * _font;
  array<char> _msg;
  
};

#endif
