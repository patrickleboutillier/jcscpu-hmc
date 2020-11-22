#ifndef PROGRAMS_h
#define PROGRAMS_h

#include "ASM.h"


PROGMEM const byte prog42[] = {
  DATA(R0, 20),
  DATA(R1, 22),
  CLF,
  ADD(R0, R1),
  DATA(R0, 1),
  OUTA(R0),
  OUTD(R1),
  HALT
} ;

/*
byte insts5x5[] = {
  DATA(R0, 5),
  DATA(R1, 5),
  DATA(R3, 1),
  XOR(R2, R2),
  CLF,
  SHR(R0, R0),
  JC(13),
  JMP(15),
  CLF,
  ADD(R1, R2),
  CLF,
  SHL(R1, R1),
  SHL(R3, R3),
  JC(22),
  JMP(7),
  DATA(R3, 100),
  ST(R3, R2),
  DATA(R0, 1),
  OUTA(R0),
  OUTD(R2),
  HALT
} ;


byte insts10print[] = {
  DATA(R0, 2),
  OUTA(R0),
  IND(R0),
  CLF,
  SHR(R0, R0),
  JC(12),
  DATA(R1, 47),
  JMP(14),
  DATA(R1, 92),
  DATA(R0, 0),
  OUTA(R0),
  OUTD(R1),
  JMP(0),
  HALT
} ;

*/

#endif
