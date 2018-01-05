#ifndef __SPY_MINER_H__
#define __SPY_MINER_H__

#include "soldier.h"

class miner : public soldier
{
 public:
  /*  name: constructor */
  /*   desc: calls the parent's contructor and passes it an */
  /*    8. */
  /*   params: none */
  /*   return: n/a */
  miner(int team, image * r, image * h);

  /*   name: is_miner */
  /*   return true */
  int is_miner() { return 1; }

  /*   name: attack */
  /*   desc: if attacking a mine, return 1, */
  /*   else call the parent's method */
  /*   params: piece * enemy */
  int attack(piece * enemy);

};

class spy : public soldier
{
 public:

  /*  name: constructor */
  /*   desc: calls the parent's contructor and passes it an */
  /*    10. */
  /*   params: none */
  /*   return: n/a */
  spy( int team, image * r, image * h );

  /*   name: is_spy */
  /*   return true */
  int is_spy() { return 1; }

  /*   name: attack */
  /*   desc: if attacking a 1, return 1, */
  /*   else call the parent's method */
  /*   params: piece * enemy */
  int attack(piece * enemy);


};

#endif
