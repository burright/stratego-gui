#ifndef __BOOM_FLAG_H__
#define __BOOM_FLAG_H__

#include "piece.h"

class flag : public piece
{    

 public:

  flag(int team, image * h, image * r);

  /*  -method */
      
  /*     name: attack */
  /*     desc:  returns nothing - flags don't attack */
  /*     params: piece * enemy */
  /*     return: int  */
  /*     1) return -2  */

  int attack(piece * enemy) { return -2; }

  /*     name: is_flag */
  /*     return true */

  int is_flag() { return 1; }

};

class bomb : public piece
{
 public:

  bomb(int team, image * h, image * r);

  /*   name: is_bomb */
  /*   return true */

  int is_bomb() { return 1; }

  /*   name: attack */
  /*   desc: returns false */
  /*   params: piece * enemy */
  /*   return: int  */
  /*   1) return -2 */

  int attack(piece * enemy) { return -2; }

};



#endif
