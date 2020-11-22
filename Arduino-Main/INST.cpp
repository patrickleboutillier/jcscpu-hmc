#include "Arduino.h"
#include "INST.h"
#include "MICROCODE.h"


INST::INST(Extension *e, int pin_bit7, int pin_bit6, int pin_bit5, int pin_bit4, int pin_bit3, int pin_bit2, int pin_bit1, int pin_bit0,
    int pin_JCOND, int pin_JINST, int pin_IAR_s_in, int pin_IAR_s_out){
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
  _pin_JINST = pin_JINST ;
  _pin_IAR_s_in = pin_IAR_s_in ;
  _pin_IAR_s_out = pin_IAR_s_out ;
  _cache = -1 ;
}


void INST::setup(){
  _e->pinMode(_pin_bit7, INPUT) ;
  _e->pinMode(_pin_bit6, INPUT) ;
  _e->pinMode(_pin_bit5, INPUT) ;
  _e->pinMode(_pin_bit4, INPUT) ;
  _e->pinMode(_pin_bit3, INPUT) ;
  _e->pinMode(_pin_bit2, INPUT) ;
  _e->pinMode(_pin_bit1, INPUT) ;
  _e->pinMode(_pin_bit0, INPUT) ;
  _e->pinMode(_pin_JCOND, INPUT) ;
  _e->pinMode(_pin_JINST, INPUT) ;
  _e->pinMode(_pin_IAR_s_in, INPUT) ;
  _e->pinMode(_pin_IAR_s_out, OUTPUT) ;
}


/*
 * Here we will lookup in the microcode table the control word value based on our input and return it
 */
unsigned long INST::loop(bool reset, bool clk_e, bool clk_s, byte step, bool debug){
  // First, handle the IAR_s_out signal
  bool jump = ((_e->digitalRead(_pin_JCOND))&&(_e->digitalRead(_pin_JINST))) ;
  if ((reset)||(_e->digitalRead(_pin_IAR_s_in))||(jump)){
    _e->digitalWrite(_pin_IAR_s_out, HIGH) ;
  }
  else {
    _e->digitalWrite(_pin_IAR_s_out, LOW) ;
  }
  
  // Now take care of the Control Word.
  unsigned long ret = 0 ;
  int inst = -1 ;
  unsigned int addr = 0 ;   
  if ((clk_e)||(clk_s)){
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
        inst = read() ;
        addr = (((byte)inst) * 6) + ((step - 4) * 2) ;
        if (clk_e){
          ret |= pgm_read_dword(microcode + addr) ;
        }
        if (clk_s){
          ret |= pgm_read_dword(microcode + (addr + 1)) ;
        }
        break ;
    }
  }

  if ((debug)&&(ret != _cache)){
    Serial.print("  INST(step:") ;
    Serial.print(step) ;
    Serial.print(", clk_e:") ;
    Serial.print(clk_e) ;
    Serial.print(", clk_s:") ;
    Serial.print(clk_s) ;
    Serial.print(", cw=") ;
    Serial.print(print_cw(ret)) ;
    if (inst != -1){
      Serial.print(", inst:") ;
      Serial.print(inst, BIN) ;
      Serial.print(", addr=") ;
      Serial.print(addr) ;
    }
    Serial.println(")") ;
  }
  _cache = ret ; 
  
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


char *print_cw(unsigned long cw){
  static char buf[40] ;

  byte dashes = 0 ;
  for (byte i = 0 ; i < 32 ; i++){
    if ((i == 8)||(i == 16)||(i == 24)){
      buf[i+dashes] = '-' ;
      dashes++ ;
    }
    buf[i+dashes] = '0' + ((cw >> (31-i)) & 1) ;
  }
  buf[32+dashes] = '\0' ;
   
  return buf ;
}
