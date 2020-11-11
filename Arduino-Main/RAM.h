#ifndef RAM_h
#define RAM_h

#include "Arduino.h"
#include "Extension.h"


class RAM {
  public:
    RAM(Extension *e, int pin_MAR_s, int pin_RAM_e, int pin_RAM_s) ;
    void setup() ;
    int loop(int bus) ;
  private:
    Extension *_e ;
    byte _MAR ;
    byte _RAM[256] ;
    int _pin_MAR_s ;
    int _pin_RAM_e ;
    int _pin_RAM_s ;
} ;

#endif
