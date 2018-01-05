

#include "boom_flag.h"

flag::flag(int team, image * h, image * r)
  : piece(team, h, r)
{
}


bomb::bomb(int team, image * h, image * r)
  : piece(team,h,r)
{
}
