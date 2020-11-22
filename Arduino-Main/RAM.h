#ifndef RAM_h
#define RAM_h

#include "Arduino.h"
#include "BUS.h"


class RAM {
  public:
    RAM(BUS *bus, void *program, int pin_MAR_s, int pin_RAM_e, int pin_RAM_s) ;
    void setup() ;
    bool loop(bool debug = 0) ;
  private:
    BUS *_bus ;
    byte _MAR ;
    byte _RAM[256] ;
    int _pin_MAR_s ;
    int _pin_RAM_e ;
    int _pin_RAM_s ;
} ;

#endif
