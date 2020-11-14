#ifndef CLK_H
#define CLK_H

#include "Arduino.h"
#include "Extension.h"


#define CLK_MANUAL    A4
#define CLK_WAITING   A5


class CLK {
  public:
    CLK(Extension *e, int HZ, int pin_CLK_e, int pin_CLK_s, int pin_STEP_1, int pin_STEP_2, int pin_STEP_3,
      int pin_STEP_4, int pin_STEP_5, int pin_STEP_6) ;
    void setup() ;
    byte loop(bool debug = 0) ;
  private:
    byte qtick() ;
    Extension *_e ;
    unsigned long _then ;
    long _qtick ;
    byte _step ;
    byte _state ;
    int _HZ ;
    int _pin_CLK_e ;
    int _pin_CLK_s ;
    int _pin_STEP_1 ;
    int _pin_STEP_2 ;
    int _pin_STEP_3 ;
    int _pin_STEP_4 ;
    int _pin_STEP_5 ;
    int _pin_STEP_6 ;
} ;

#endif
