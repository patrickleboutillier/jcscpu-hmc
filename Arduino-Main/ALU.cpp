#include "Arduino.h"
#include "ALU.h"


ALU::ALU(Extension *e, int pin_op2, int pin_op1, int pin_op0, int pin_ci, int pin_c, int pin_a, int pin_e, int pin_z,
    int pin_TMP_s, int pin_ACC_e, int pin_ACC_s, int pin_BUS1){
  _e = e ;
  _TMP = 0 ;
  _ACC = 0 ;
  _result = 0 ;
  
  _pin_op2 = pin_op2 ;
  _pin_op1 = pin_op1 ; 
  _pin_op0 = pin_op0 ; 
  _pin_ci = pin_ci ; 
  _pin_c = pin_c ; 
  _pin_a = pin_a ; 
  _pin_e = pin_e ; 
  _pin_z = pin_z ;
  _pin_TMP_s = pin_TMP_s ;
  _pin_ACC_e = pin_ACC_e ;
  _pin_ACC_s = pin_ACC_s ;
  _pin_BUS1 = pin_BUS1 ;
}


void ALU::setup(){
  _e->pinMode(_pin_op2, INPUT) ;
  _e->pinMode(_pin_op1, INPUT) ;
  _e->pinMode(_pin_op0, INPUT) ;
  _e->pinMode(_pin_ci, INPUT) ;
  _e->pinMode(_pin_c, OUTPUT) ;
  _e->pinMode(_pin_a, OUTPUT) ;
  _e->pinMode(_pin_e, OUTPUT) ;
  _e->pinMode(_pin_z, OUTPUT) ;
  _e->pinMode(_pin_TMP_s, INPUT) ;
  _e->pinMode(_pin_ACC_e, INPUT) ;
  _e->pinMode(_pin_ACC_s, INPUT) ;
  _e->pinMode(_pin_BUS1, INPUT) ;
}


int ALU::loop(int bus){
  if (_e->digitalRead(_pin_TMP_s)){
    _TMP = bus ;
  }

  byte a = bus ;
  byte b = _TMP ;
  if (_e->digitalRead(_pin_BUS1)){
    b = 1 ;
  }

  byte op = (_e->digitalRead(_pin_op2) << 2) | (_e->digitalRead(_pin_op1) << 1) | _e->digitalRead(_pin_op0) ;
  bool ci = _e->digitalRead(_pin_ci) ;
  int res = soft_alu(op, a, b, ci) ;
  _result = res & 0xFF ;
  _e->digitalWrite(_pin_c, (res >> 11) & 0b0001) ;
  _e->digitalWrite(_pin_a, (res >> 10) & 0b0001) ;
  _e->digitalWrite(_pin_e, (res >> 9) & 0b0001) ;
  _e->digitalWrite(_pin_z, (res >> 8) & 0b0001) ; 
   
  if (_e->digitalRead(_pin_ACC_s)){
    _ACC = _result ;
  }
  
  if (_e->digitalRead(_pin_ACC_e)){
    bus = _ACC ;
  }
  else {
    bus = -1 ;
  }

  Serial.println(bus) ;
  return bus ;
}


int ALU::soft_alu(byte op, byte a, byte b, bool ci){
  byte c = 0 ;
  byte co = 0 ;
  switch (op){
    case 0: {  // ADD
      int sum = (int)a + (int)b + (int)ci ;
      c = (byte)sum ;
      if (sum >= 256){
        c = sum - 256 ;
        co = 1 ;
      }
      break ;
    }
    case 1: // SHR
      if (a % 2){
        co = 1 ;
      }
      c = (ci << 7) | (a >> 1) ;
      break ;
    case 2: // SHL
      if (a >= 128){
        co = 1 ;
      }
      c = (a << 1) | ci ;
      break ;
    case 3: // NOT
      c = ~a ;
      break ;
    case 4: // AND
      c = a & b ;
      break ;
    case 5: // OR
      c = a | b ;
      break ;
    case 6: // XOR
      c = a ^ b ;
      break ;
    case 7: // CMP
      break ;
  }
 
  bool alarger = (a > b) ;
  bool eq = (a == b) ;
  bool zero = (c == 0) ;
  bool carry_out = co ;

  Serial.print("  ALU(op:") ;
  Serial.print(op) ;
  Serial.print(", a:") ;
  Serial.print(a) ;
  Serial.print(", b:") ;
  Serial.print(b) ;
  Serial.print(", ci:") ;  
  Serial.print(ci) ;
  Serial.print(") = (res:") ;
  Serial.print(c) ;  
  Serial.print(", c:") ;
  Serial.print(carry_out) ; 
  Serial.print(", a:") ;
  Serial.print(alarger) ; 
  Serial.print(", e:") ;
  Serial.print(eq) ; 
  Serial.print(", z:") ;
  Serial.print(zero) ; 
  Serial.println(")") ;
  
  return (carry_out << 11) | (alarger << 10) | (eq << 9) | (zero << 8) | c ; 
} 
