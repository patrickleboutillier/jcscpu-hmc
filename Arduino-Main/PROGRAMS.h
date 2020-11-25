#ifndef PROGRAMS_h
#define PROGRAMS_h

#include "ASM.h"


PROGMEM const byte progggame[] = {
  // R2=min, R3=max
  DATA(R2, 0),
  DATA(R3, 255),
  // Label 'RETRY'
  JMP(52),
  // Label 'TRY_RETURN' at pos 6
  // Save R1 to RAM at address 255
  DATA(R0, 255),
  ST(R0, R1),
  // Label 'GET_CHAR' at pos 9
  DATA(R0, 0), // TTY
  OUTA(R0),
  IND(R0),
  // '\0'
  DATA(R1, 0),
  CMP(R0, R1),
  JE(9), 
  // 'h'
  DATA(R1, 104),
  CMP(R0, R1),
  JE(35),
  // 'l'
  DATA(R1, 108),
  CMP(R0, R1),
  JE(40),
  // '='
  DATA(R1, 61),
  CMP(R0, R1),
  JE(45),
  JMP(4),
  // Label 'H' at pos 35
  DATA(R0, 255),
  LD(R0, R2),
  JMP(4),
  // Label 'L' at pos 40
  DATA(R0, 255),
  LD(R0, R3),
  JMP(4),
  // Label 'EQ' at pos 45
  DATA(R0, 33),
  OUTD(R0),
  DATA(R0, 10),
  OUTD(R0),
  HALT,
  // Label 'TRY' at pos 49
  NOT(R2, R1),
  DATA(R0, 1),
  CLF,
  ADD(R0, R1),
  CLF,
  ADD(R3, R1),
  CLF,
  SHR(R1, R1),
  CLF,
  ADD(R2, R1),
  DATA(R0, 1), // TTY_NUM
  OUTA(R0),
  OUTD(R1),
  DATA(R0, 0), // TTY
  OUTA(R0),
  DATA(R0, 63),
  OUTD(R0),
  DATA(R0, 32),
  OUTD(R0),
  JMP(6),
} ;


PROGMEM const byte progjc[] = {
  DATA(R0, 200),
  DATA(R1, 200),
  CLF,
  ADD(R0, R1),
  JC(9),
  HALT,
  DATA(R0, 0),
  OUTA(R0),
  DATA(R1, 74),
  OUTD(R1),
  HALT
} ;


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


PROGMEM const byte prog5x5[] = {
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
  DATA(R0, 1),
  OUTA(R0),
  OUTD(R2),
  HALT
} ;


PROGMEM const byte prog10print[] = {
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


#endif
