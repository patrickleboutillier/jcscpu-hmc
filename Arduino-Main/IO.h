#ifndef IO_h
#define IO_h

#include "Arduino.h"
#include "BUS.h"


class IO {
  public:
    IO(Extension *e, BUS *bus, int pin_IO_s, int pin_IO_e, int pin_IO_io, int pin_IO_da) ;
    void setup() ;
    bool loop(bool debug = 0) ;
  private:
    byte produce_byte() ;
    void consume_byte(byte b) ;
    Extension *_e ;
    BUS *_bus ;
    int _pin_IO_s ;
    int _pin_IO_e ;
    int _pin_IO_io ;
    int _pin_IO_da ;
    byte _cur_dev ;
} ;

#endif
