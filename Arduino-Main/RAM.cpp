#include "Arduino.h"
#include "RAM.h"


RAM::RAM(BUS *bus, int pin_MAR_s, int pin_RAM_s, int pin_RAM_e){
  _bus = bus ;
  _MAR = 0 ;
  for (int i = 0 ; i < 255 ; i++){
    _RAM[i] = 0 ;
  }

  _pin_MAR_s = pin_MAR_s ;
  _pin_RAM_e = pin_RAM_e ;
  _pin_RAM_s = pin_RAM_s ;
}


void RAM::setup(){
  pinMode(_pin_MAR_s, INPUT) ;
  pinMode(_pin_RAM_e, INPUT) ;
  pinMode(_pin_RAM_s, INPUT) ;
}


bool RAM::loop(bool debug = 0){
  if (digitalRead(_pin_MAR_s)){
    _MAR = _bus->read() ;
    if (debug){
      Serial.print("  RAM(op:mar_s, mar:") ;
      Serial.print(_MAR) ;
      Serial.println(")") ;
    }
  }
   
  if (digitalRead(_pin_RAM_s)){
    _RAM[_MAR] = _bus->read() ;
    if (debug){
      Serial.print("  RAM(op:ram_s, mar:") ;
      Serial.print(_MAR) ;
      Serial.print(", v:") ;
      Serial.print(_RAM[_MAR]) ;    
      Serial.println(")") ;
    }
  }

  bool be = false ;
  if (digitalRead(_pin_RAM_e)){
    _bus->write(_RAM[_MAR]) ;
    be = true ;
    if (debug){
      Serial.print("  RAM(op:ram_e, mar:") ;
      Serial.print(_MAR) ;
      Serial.print(", v:") ;
      Serial.print(_RAM[_MAR]) ;
      Serial.println(")") ;
    }
  }

  return be ;
}
