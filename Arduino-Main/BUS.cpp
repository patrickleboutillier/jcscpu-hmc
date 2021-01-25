#include "Arduino.h"
#include "BUS.h"


BUS::BUS(int pin_bit7, int pin_bit6, int pin_bit5, int pin_bit4, int pin_bit3, int pin_bit2, int pin_bit1, int pin_bit0){  
  _enabled = false ;
  _cache = 0 ;
  _pin_bit7 = pin_bit7 ;
  _pin_bit6 = pin_bit6 ;
  _pin_bit5 = pin_bit5 ;
  _pin_bit4 = pin_bit4 ;
  _pin_bit3 = pin_bit3 ;
  _pin_bit2 = pin_bit2 ;
  _pin_bit1 = pin_bit1 ;
  _pin_bit0 = pin_bit0 ;
}


void BUS::setup(){
  pinMode(_pin_bit7, INPUT) ;
  pinMode(_pin_bit6, INPUT) ;
  pinMode(_pin_bit5, INPUT) ;
  pinMode(_pin_bit4, INPUT) ;
  pinMode(_pin_bit3, INPUT) ;
  pinMode(_pin_bit2, INPUT) ;
  pinMode(_pin_bit1, INPUT) ;
  pinMode(_pin_bit0, INPUT) ;
}


void BUS::reset(){
  if (_enabled){
    pinMode(_pin_bit7, INPUT) ;
    pinMode(_pin_bit6, INPUT) ;
    pinMode(_pin_bit5, INPUT) ;
    pinMode(_pin_bit4, INPUT) ;
    pinMode(_pin_bit3, INPUT) ;
    pinMode(_pin_bit2, INPUT) ;
    pinMode(_pin_bit1, INPUT) ;
    pinMode(_pin_bit0, INPUT) ;
    _enabled = false ;  
  }
}


byte BUS::read(){
  if (_enabled){
    // One part wants to read from the BUS, while another one is writing.
    // We give the reader the out cached value.
    return _cache ;
  }
  
  return 
    (digitalRead(_pin_bit7) << 7) |
    (digitalRead(_pin_bit6) << 6) |
    (digitalRead(_pin_bit5) << 5) |
    (digitalRead(_pin_bit4) << 4) |
    (digitalRead(_pin_bit3) << 3) |
    (digitalRead(_pin_bit2) << 2) |
    (digitalRead(_pin_bit1) << 1) |
    digitalRead(_pin_bit0) ;
}


void BUS::write(byte b){
  if (! _enabled){
    pinMode(_pin_bit7, OUTPUT) ;
    pinMode(_pin_bit6, OUTPUT) ;
    pinMode(_pin_bit5, OUTPUT) ;
    pinMode(_pin_bit4, OUTPUT) ;
    pinMode(_pin_bit3, OUTPUT) ;
    pinMode(_pin_bit2, OUTPUT) ;
    pinMode(_pin_bit1, OUTPUT) ;
    pinMode(_pin_bit0, OUTPUT) ;
    _enabled = true ;
  }

  digitalWrite(_pin_bit7, (b >> 7) & 0x01) ;
  digitalWrite(_pin_bit6, (b >> 6) & 0x01) ;
  digitalWrite(_pin_bit5, (b >> 5) & 0x01) ;
  digitalWrite(_pin_bit4, (b >> 4) & 0x01) ;
  digitalWrite(_pin_bit3, (b >> 3) & 0x01) ;
  digitalWrite(_pin_bit2, (b >> 2) & 0x01) ;
  digitalWrite(_pin_bit1, (b >> 1) & 0x01) ;
  digitalWrite(_pin_bit0, b & 0x01) ;

  _cache = b ;
}
