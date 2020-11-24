#include "Arduino.h"
#include "IO.h"


// Device ids
#define TTY           0
#define TTY_NUM       1
#define RNG           2


IO::IO(Extension *e, BUS *bus, int pin_IO_s, int pin_IO_e, int pin_IO_io, int pin_IO_da){
  _e = e ;
  _bus = bus ;
  
  _pin_IO_s = pin_IO_s ;
  _pin_IO_e = pin_IO_e ; 
  _pin_IO_io = pin_IO_io ; 
  _pin_IO_da = pin_IO_da ; 
  _cur_dev = 0 ;
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
  bool be = false ;
  byte state = (ve << 3) | (vs << 2) | (vio << 1) | vda ;
  if (state != _cache){    
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
  }
 
  return be ;
}


byte IO::produce_byte(){
  byte ret = 0 ;

  switch (_cur_dev){
    case TTY:
    case TTY_NUM:
      // Do nothing, TTYs are input only.
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
    case RNG:
      // Do nothing, RNG is output-only.
      break ;
  }
}

/* 

// Device das
#define TTY           0
#define TTY_NUM       1
#define RNG           2


// Control pins
#define IO_e      9
#define IO_s     12
#define IO_io  10
#define IO_da  11


void loop(){
  byte cur_IO_e = digitalRead(IO_e) ;
    if (cur_IO_e){
      if (digitalRead(IO_io) == LOW){ // INPUT
        if (digitalRead(IO_da) == LOW){ // DATA
          byte b = get_output() ;
        }
      }
    }
    else {
      digitalWrite(ENABLE_OUT, HIGH) ;
    }
    prev_IO_e = cur_IO_e ;
  }

  byte cur_IO_s = digitalRead(IO_s) ;
  if (cur_IO_s != prev_IO_s){
    if (cur_IO_s){
      if (digitalRead(IO_io) == HIGH){ // OUTPUT
        if (digitalRead(IO_da) == LOW){ // DATA
          digitalWrite(CLOCK_IN, HIGH) ;
          digitalWrite(LATCH_IN, HIGH) ;
          byte b = shiftIn(DATA_IN, CLOCK_IN, MSBFIRST) ;
          digitalWrite(LATCH_IN, LOW) ;
          Serial.print("Read from bus:") ;
          Serial.println(b) ;
          dispatch_input(b) ;
        }
        else { // ADDR
          digitalWrite(CLOCK_IN, HIGH) ;
          digitalWrite(LATCH_IN, HIGH) ;
          cur_dev = shiftIn(DATA_IN, CLOCK_IN, MSBFIRST) ;
          digitalWrite(LATCH_IN, LOW) ;
          Serial.print("Cur dev set to:") ;
          Serial.println(cur_dev) ;
        }
      }
    }
  }
}


void dispatch_input(byte b){
  switch (cur_dev){
    case TTY:
      tty_put(b) ;
      // Print the char on the LCD
      break ;
    case TTY_NUM:
      char s[8] ;
      sprintf(s, "%d", b) ;
      for (byte i = 0 ; i < strlen(s) ; i++){
        tty_put(s[i]) ;
      }
      break ;
    case RNG:
      // Do nothing, RNG is output-only.
      break ;
  }
}


byte get_output(){
  byte ret = 0 ;

  switch (cur_dev){
    case TTY:
    case TTY_NUM:
      // Do nothing, TTYs are input only.
      break ;
    case RNG:
      // Return a random byte
      ret = random(256) ;
  }

  return ret ;
}

*/
