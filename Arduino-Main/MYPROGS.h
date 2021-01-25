#ifndef MYPROGS_h
#define MYPROGS_h

#include "ASM.h"


PROGMEM const byte progtemplate[] = {
  HALT,
} ;


PROGMEM const byte progtest[] = {
  DATA(R0, 5),
  // ...
  HALT,
} ;

#endif
