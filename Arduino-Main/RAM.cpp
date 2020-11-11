#include "Arduino.h"
#include "RAM.h"


RAM::RAM(Extension *e, int pin_MAR_s, int pin_RAM_e, int pin_RAM_s){
    _e = e ;
    _MAR = 0 ;
    for (int i = 0 ; i < 255 ; i++){
      _RAM[i] = 0 ;
    }

    _pin_MAR_s = pin_MAR_s ;
    _pin_RAM_e = pin_RAM_e ;
    _pin_RAM_s = pin_RAM_s ;
}


void RAM::setup(){
    _e->pinMode(_pin_MAR_s, INPUT) ;
    _e->pinMode(_pin_RAM_e, INPUT) ;
    _e->pinMode(_pin_RAM_s, INPUT) ;
}


int RAM::loop(int bus){
  if (_e->digitalRead(_pin_MAR_s)){
    _MAR = bus ;
    Serial.print("  RAM(mar:") ;
    Serial.print(_MAR) ;
    Serial.println(")") ;
  }
   
  if (_e->digitalRead(_pin_RAM_s)){
    _RAM[_MAR] = bus ;
    Serial.print("  RAM(mar:") ;
    Serial.print(_MAR) ;
    Serial.print(", v:") ;
    Serial.print(_RAM[_MAR]) ;    
    Serial.println(")") ;
  }
  
  if (_e->digitalRead(_pin_RAM_e)){
    bus = _RAM[_MAR] ;
  }
  else {
    bus = -1 ;
  }

  return bus ;
}
