#include "Arduino.h"
#include "IO.h"


// Device ids
#define TTY           0
#define TTY_NUM       1
#define TTY_NUM_T     2
#define RNG           5


IO::IO(Extension *e, BUS *bus, int pin_IO_s, int pin_IO_e, int pin_IO_io, int pin_IO_da){
  _e = e ;
  _bus = bus ;
  
  _pin_IO_s = pin_IO_s ;
  _pin_IO_e = pin_IO_e ; 
  _pin_IO_io = pin_IO_io ; 
  _pin_IO_da = pin_IO_da ; 
  _cur_dev = 0 ;
  _be_cache = false ;
  _cache = 0 ;
}


void IO::setup(){
  _e->pinMode(_pin_IO_s, INPUT) ;
  _e->pinMode(_pin_IO_e, INPUT) ;
  _e->pinMode(_pin_IO_io, INPUT) ;
  _e->pinMode(_pin_IO_da, INPUT) ;
}


bool IO::loop(bool debug = 0){
  bool ve = _e->digitalRead(_pin_IO_e) ;
  bool vs = _e->digitalRead(_pin_IO_s) ;
  bool vio = _e->digitalRead(_pin_IO_io) ;
  bool vda = _e->digitalRead(_pin_IO_da) ;

  // IO modules cannot be constantly evaluating. They must react only when these indicators change.
  bool be = _be_cache ;
  byte state = (ve << 3) | (vs << 2) | (vio << 1) | vda ;
  if (state != _cache){ 
    be = false ;   
    if (ve){
      if (vio == LOW){ // INPUT
        if (vda == LOW){ // DATA
          byte b = produce_byte() ;
          _bus->write(b) ;
          be = true ;
        }
      }
    }
  
    if (vs){
      if (vio == HIGH){ // OUTPUT
        if (vda == LOW){ // DATA
          byte b = _bus->read() ;
          consume_byte(b) ;
        }
        else { // ADDR
          _cur_dev = _bus->read() ;
        }
      }
    }

    if (debug){
      Serial.print("  IO(io_s:") ;
      Serial.print(vs) ;
      Serial.print(", io_e:") ;
      Serial.print(ve) ;
      Serial.print(", io_io:") ;
      Serial.print(vio) ;
      Serial.print(", io_da:") ;  
      Serial.print(vda) ; 
      Serial.print(", cur_dev:") ;  
      Serial.print(_cur_dev) ; 
      Serial.println(")") ;
    }
    
    _cache = state ;
    _be_cache = be ;
  }
 
  return be ;
}


byte IO::produce_byte(){
  byte ret = 0 ;

  switch (_cur_dev){
    case TTY:
      if (Serial.available()){
        ret = Serial.read() ;
      }
      break ;
    case TTY_NUM:
    case TTY_NUM_T:
      if (Serial.available()){
        ret = Serial.read() - '0' ;
        if ((ret < 0)||(ret > 9)){
          ret = 0 ;
        }
      }
      break ;
    case RNG:
      // Return a random byte
      ret = random(256) ;
  }

  return ret ;
}


void IO::consume_byte(byte b){
  switch (_cur_dev){
    case TTY:
      Serial.print((char)b) ;
      break ;
    case TTY_NUM:
      Serial.println(b) ;
      break ;
    case TTY_NUM_T:
      char buf[8] ;
      sprintf(buf, "%4d", b) ;
      Serial.print(buf) ;
      break ;
    case RNG:
      // Do nothing, RNG is output-only.
      break ;
  }
}
