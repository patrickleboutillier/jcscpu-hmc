#ifndef CW_h
#define CW_h

#include "Arduino.h"
#include "BUS.h"


class CW {
  public:
    CW(int pin_DATA, int pin_LATCH, int pin_CLK) ;
    void setup() ;
    void loop(unsigned long cw, bool debug = 0) ;
  private:
    int _pin_CLK ;
    int _pin_LATCH ;
    int _pin_DATA ;
} ;

#endif
