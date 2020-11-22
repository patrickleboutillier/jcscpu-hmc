#include "Arduino.h"
#include "INST.h"
#include "CW.h"


CW::CW(int pin_DATA, int pin_LATCH, int pin_CLK){
  _pin_DATA = pin_DATA ;
  _pin_LATCH = pin_LATCH ;
  _pin_CLK = pin_CLK ;
  _cache = -1 ;
}


void CW::setup(){
  pinMode(_pin_DATA, OUTPUT) ;
  pinMode(_pin_LATCH, OUTPUT) ;
  pinMode(_pin_CLK, OUTPUT) ;
}


void CW::loop(bool reset, unsigned long cw, bool debug = 0){
  if (reset){
    cw = 0 ;
  }
  
  if (cw == _cache){
    return ;
  }
  
  digitalWrite(_pin_LATCH, LOW) ;

  if (debug){
    Serial.print("  CW(cw:") ;
    Serial.print(print_cw(cw)) ;
    Serial.println(")") ;
  }

  shiftOut(_pin_DATA, _pin_CLK, LSBFIRST, (byte)(cw & 0xFF)) ;
  shiftOut(_pin_DATA, _pin_CLK, LSBFIRST, (byte)((cw >> 8) & 0xFF)) ;
  shiftOut(_pin_DATA, _pin_CLK, LSBFIRST, (byte)((cw >> 16) & 0xFF)) ;
  byte b = (byte)((cw >> 24) & 0xFF) ;
  shiftOut(_pin_DATA, _pin_CLK, LSBFIRST, b) ;
  digitalWrite(_pin_LATCH, HIGH) ;
  _cache = cw ; 
}
