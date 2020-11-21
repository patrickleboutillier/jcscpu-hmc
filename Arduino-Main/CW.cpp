#include "Arduino.h"
#include "CW.h"


CW::CW(int pin_DATA, int pin_LATCH, int pin_CLK){
  _pin_DATA = pin_DATA ;
  _pin_LATCH = pin_LATCH ;
  _pin_CLK = pin_CLK ;
}


void CW::setup(){
  pinMode(_pin_CLK, OUTPUT) ;
  pinMode(_pin_LATCH, OUTPUT) ;
  pinMode(_pin_DATA, OUTPUT) ;
}


void CW::loop(unsigned long cw, bool debug = 0){
  digitalWrite(_pin_LATCH, LOW) ;
  cw = 7 ;
  shiftOut(_pin_DATA, _pin_CLK, LSBFIRST, (byte)(cw & 0xFF)) ;
  //shiftOut(_pin_DATA, _pin_CLK, MSBFIRST, (cw >> 8) & 0xFF) ;
  //shiftOut(_pin_DATA, _pin_CLK, MSBFIRST, (cw >> 16) & 0xFF) ;
  //shiftOut(_pin_DATA, _pin_CLK, MSBFIRST, (cw >> 24) & 0xFF) ;
  digitalWrite(_pin_LATCH, HIGH) ; 
}
