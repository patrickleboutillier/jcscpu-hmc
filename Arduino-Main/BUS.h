#ifndef BUS_h
#define BUS_h

#include "Arduino.h"
#include "Extension.h"


class BUS {
  public:
    BUS(int pin_bit7, int pin_bit6, int pin_bit5, int pin_bit4, int pin_bit3, int pin_bit2, int pin_bit1, int pin_bit0) ;
    void setup() ;
    void reset() ;
    byte read() ;
    void write(byte b) ;    
  private:
    bool _enabled ;
    byte _cache ;
    int _pin_bit7 ;
    int _pin_bit6 ;
    int _pin_bit5 ;
    int _pin_bit4 ;
    int _pin_bit3 ;
    int _pin_bit2 ;
    int _pin_bit1 ; 
    int _pin_bit0 ;
} ;

#endif
