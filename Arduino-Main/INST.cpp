#include "Arduino.h"
#include "INST.h"
#include "MICROCODE.h"


INST::INST(Extension *e, int pin_bit7, int pin_bit6, int pin_bit5, int pin_bit4, int pin_bit3, int pin_bit2, int pin_bit1, int pin_bit0,
    int pin_JCOND, int pin_IAR_s_in, int pin_IAR_s_out){
  _e = e ; 
  _pin_bit7 = pin_bit7 ;
  _pin_bit6 = pin_bit6 ;
  _pin_bit5 = pin_bit5 ;
  _pin_bit4 = pin_bit4;
  _pin_bit3 = pin_bit3 ;
  _pin_bit2 = pin_bit2 ;
  _pin_bit1 = pin_bit1 ;
  _pin_bit0 = pin_bit0 ;
  _pin_JCOND = pin_JCOND ;
  _pin_IAR_s_in = pin_IAR_s_in ;
  _pin_IAR_s_out = pin_IAR_s_out ;
}


void INST::setup(){
  pinMode(_pin_bit7, INPUT) ;
  pinMode(_pin_bit6, INPUT) ;
  pinMode(_pin_bit5, INPUT) ;
  pinMode(_pin_bit4, INPUT) ;
  pinMode(_pin_bit3, INPUT) ;
  pinMode(_pin_bit2, INPUT) ;
  pinMode(_pin_bit1, INPUT) ;
  pinMode(_pin_bit0, INPUT) ;
  pinMode(_pin_IAR_s_in, INPUT) ;
  pinMode(_pin_IAR_s_out, OUTPUT) ;
}


/*
 * Here we will lookup in the microcode table the control word value based on our input and return it
 */
unsigned long INST::loop(bool clk_e, bool clk_s, byte step, bool debug){
  unsigned long ret = 0 ;

  if ((! clk_e)&&(! clk_s)){
    return 0 ;
  }
  
  switch (step){
    case 1:
      ret |= BUS1 ;
      ret |= (clk_e ? IAR_e : 0) ;
      ret |= (clk_s ? MAR_s|ACC_s : 0) ;
      break ;
    case 2:
      ret |= (clk_e ? RAM_e : 0) ;
      ret |= (clk_s ? IR_s : 0) ;
      break ;
   case 3:
      ret |= (clk_e ? ACC_e : 0) ;
      ret |= (clk_s ? IAR_s : 0) ;
      break ;
    default:
      byte inst = read() ;
      unsigned int addr = (inst * 6) + ((step - 4) * 2) ;
      if (clk_e){
        ret |= pgm_read_dword(addr) ;
      }
      if (clk_s){
        ret |= pgm_read_dword(addr + 1) ;
      }
      break ;
  }

  return ret ;
}


byte INST::read(){
  return 
    (_e->digitalRead(_pin_bit7) << 7) |
    (_e->digitalRead(_pin_bit6) << 6) |
    (_e->digitalRead(_pin_bit5) << 5) |
    (_e->digitalRead(_pin_bit4) << 4) |
    (_e->digitalRead(_pin_bit3) << 3) |
    (_e->digitalRead(_pin_bit2) << 2) |
    (_e->digitalRead(_pin_bit1) << 1) |
    _e->digitalRead(_pin_bit0) ;
}
