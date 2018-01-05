#include"display.h"

display::display(char * font, int pt_size, SDL_Color fg)
{
  _font = TTF_OpenFont(font,pt_size);
  if (!font)
  {
    cerr<<"Could not open font: "<<TTF_GetError()<<endl;
    exit(1);
  }
  
  _fg = fg;

  _msg[0] = '\0';
}
  
display::~display()
{
  TTF_CloseFont(_font);
}
  
void display::draw(screen * s)
{
  if (_msg[0] == '\0')
    return;

  SDL_Rect src, dest;
  SDL_Surface * render;
  
  render = TTF_RenderText_Blended(_font,_msg.get_data(),_fg);
  
  if (!render)
  {
    cerr<<"Could not render text: "<<_msg.get_data()<<": "<<TTF_GetError()
	<<endl;
    exit(1);
  }
  
  src.x = src.y = 0;
  src.h = render->h;
  src.w = render->w;
  
  dest = src;

  dest.x = (s->get_width() - src.w) / 2;
  dest.y = (s->get_height() - src.h) / 2;

  SDL_BlitSurface(render,&src,s->get_screen(),&dest);

  SDL_FreeSurface(render);
}

void display::set_text(char * txt)
{
  _msg.copy_in(txt,strlen(txt) + 1);
}

void display::clear_text()
{
  _msg[0] = '\0';
}

void display::add_char(char c)
{
  int len = _msg.get_size();

  _msg[len-1] = c;
  _msg[len] = '\0';
}

void display::del_char()
{
  int len = _msg.get_size();
  
  _msg[len-2] = '\0';
  _msg.shrink(1);
}
