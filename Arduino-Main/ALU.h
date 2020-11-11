#ifndef ALU_h
#define ALU_h

#include "Arduino.h"
#include "Extension.h"


class ALU {
  public:
    ALU(Extension *e, int pin_op2, int pin_op1, int pin_op0, int pin_ci, int pin_c, int pin_a, int pin_e, int pin_z,
      int pin_TMP_s, int pin_ACC_e, int pin_ACC_s, int pin_BUS1) ;
    void setup() ;
    int loop(int bus) ;
    int soft_alu(byte op, byte a, byte b, bool ci) ;
  private:
    Extension *_e ;
    byte _TMP ;
    byte _ACC ;
    byte _result ;
    int _pin_op2 ;
    int _pin_op1 ; 
    int _pin_op0 ; 
    int _pin_ci ; 
    int _pin_c ; 
    int _pin_a ; 
    int _pin_e ; 
    int _pin_z ;
    int _pin_TMP_s ;
    int _pin_ACC_e ;
    int _pin_ACC_s ;
    int _pin_BUS1 ;
} ;

#endif
