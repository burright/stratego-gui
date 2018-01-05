#include "stratego.h"

int main()
{
  stratego g;
  int again = 1;

  srand( time(0) );

  while ( again )
  {
    g.play_game();

    again = g.play_again();
  }
  

  return 0;
}
