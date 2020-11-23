#ifndef CW_h
#define CW_h

#include "Arduino.h"


class CW {
  public:
    CW(int pin_DATA, int pin_LATCH, int pin_CLK) ;
    void setup() ;
    void loop(bool reset, unsigned long cw, bool debug = 0) ;
  private:
    unsigned long _cache ;
    int _pin_CLK ;
    int _pin_LATCH ;
    int _pin_DATA ;
} ;

#endif
