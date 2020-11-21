#ifndef INST_h
#define INST_h

#include "Arduino.h"
#include "Extension.h"


class INST {
  public:
    INST(Extension *e, int pin_bit7, int pin_bit6, int pin_bit5, int pin_bit4, int pin_bit3, int pin_bit2, int pin_bit1, int pin_bit0, 
      int pin_JCOND, int pin_IAR_s_in, int pin_IAR_s_out) ;
    void setup() ;
    unsigned long loop(bool clk_e, bool clk_s, byte step, bool debug) ;   
  private:
    byte read() ;
    Extension *_e ;
    int _pin_bit7 ;
    int _pin_bit6 ;
    int _pin_bit5 ;
    int _pin_bit4 ;
    int _pin_bit3 ;
    int _pin_bit2 ;
    int _pin_bit1 ; 
    int _pin_bit0 ;
    int _pin_JCOND ;
    int _pin_IAR_s_in ;
    int _pin_IAR_s_out ;
} ;

#endif
