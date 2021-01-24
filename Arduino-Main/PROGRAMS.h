#ifndef PROGRAMS_h
#define PROGRAMS_h

#include "ASM.h"


PROGMEM const byte progggame[] = {
  /* addr   0 */ // R2=min, R3=max
  /* addr   0 */ DATA(R2, 0),    // (00000000)
  /* addr   2 */ DATA(R3, 255),  // (11111111)
  /* addr   4 */ // Label 'RETRY'
  /* addr   4 */ JMP(52),     // (@TRY)
  /* addr   6 */ // Label 'TRY_RETURN'
  /* addr   6 */ // Save R1 to RAM at address 255
  /* addr   6 */ DATA(R0, 255),  // (11111111)
  /* addr   8 */ ST(R0, R1),
  /* addr   9 */ // Label 'GET_CHAR'
  /* addr   9 */ DATA(R0, 0),    // (00000000)
  /* addr  11 */ OUTA(R0),
  /* addr  12 */ IND(R0),
  /* addr  13 */ // \0
  /* addr  13 */ DATA(R1, 0),    // (00000000)
  /* addr  15 */ CMP(R0, R1),
  /* addr  16 */ JE(9),  // (@GET_CHAR)
  /* addr  18 */ // h
  /* addr  18 */ DATA(R1, 104),  // (01101000)
  /* addr  20 */ CMP(R0, R1),
  /* addr  21 */ JE(35),        // (@H)
  /* addr  23 */ // l
  /* addr  23 */ DATA(R1, 108),  // (01101100)
  /* addr  25 */ CMP(R0, R1),
  /* addr  26 */ JE(40),        // (@L)
  /* addr  28 */ // =
  /* addr  28 */ DATA(R1, 61),   // (00111101)
  /* addr  30 */ CMP(R0, R1),
  /* addr  31 */ JE(45),       // (@EQ)
  /* addr  33 */ JMP(4),   // (@RETRY)
  /* addr  35 */ // Label 'H'
  /* addr  35 */ DATA(R0, 255),  // (11111111)
  /* addr  37 */ LD(R0, R2),
  /* addr  38 */ JMP(4),   // (@RETRY)
  /* addr  40 */ // Label 'L'
  /* addr  40 */ DATA(R0, 255),  // (11111111)
  /* addr  42 */ LD(R0, R3),
  /* addr  43 */ JMP(4),   // (@RETRY)
  /* addr  45 */ // Label 'EQ'
  /* addr  45 */ DATA(R0, 33),   // (00100001)
  /* addr  47 */ OUTD(R0),
  /* addr  48 */ DATA(R0, 10),   // (00001010)
  /* addr  50 */ OUTD(R0),
  /* addr  51 */ HALT,
  /* addr  52 */ // Label 'TRY'
  /* addr  52 */ NOT(R2, R1),
  /* addr  53 */ DATA(R0, 1),    // (00000001)
  /* addr  55 */ CLF,
  /* addr  56 */ ADD(R0, R1),
  /* addr  57 */ CLF,
  /* addr  58 */ ADD(R3, R1),
  /* addr  59 */ CLF,
  /* addr  60 */ SHR(R1, R1),
  /* addr  61 */ CLF,
  /* addr  62 */ ADD(R2, R1),
  /* addr  63 */ DATA(R0, 1),    // (00000001)
  /* addr  65 */ OUTA(R0),
  /* addr  66 */ OUTD(R1),
  /* addr  67 */ DATA(R0, 0),    // (00000000)
  /* addr  69 */ OUTA(R0),
  /* addr  70 */ DATA(R0, 63),   // (00111111)
  /* addr  72 */ OUTD(R0),
  /* addr  73 */ DATA(R0, 32),
  /* addr  75 */ OUTD(R0),
  /* addr  76 */ JMP(6),  // (@TRY_RETURN)
} ;



PROGMEM const byte progjc[] = {
  DATA(R0, 200),
  DATA(R1, 200),
  CLF,
  ADD(R0, R1),
  JC(9),
  HALT,
  DATA(R0, 3),
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


PROGMEM const byte progsquares[] = {
  /* addr   0 */ DATA(R2, 0),    // (00000000)
  /* addr   2 */ ST(R2, R2),
  /* addr   3 */ DATA(R0, 1),    // (00000001)
  /* addr   5 */ // Label 'do'
  /* addr   5 */ DATA(R2, 0),    // (00000000)
  /* addr   7 */ CLF,
  /* addr   8 */ ADD(R0, R2),
  /* addr   9 */ DATA(R3, 0),    // (00000000)
  /* addr  11 */ CLF,
  /* addr  12 */ ADD(R0, R3),
  /* addr  13 */ XOR(R1, R1),
  /* addr  14 */ // Label 'loop'
  /* addr  14 */ CLF,
  /* addr  15 */ SHR(R2, R2),
  /* addr  16 */ JC(20),         // (@add)
  /* addr  18 */ JMP(24),        // (@pass)
  /* addr  20 */ // Label 'add'
  /* addr  20 */ CLF,
  /* addr  21 */ ADD(R3, R1),
  /* addr  22 */ JMP(27),        // (@next)
  /* addr  24 */ // Label 'pass'
  /* addr  24 */ JZ(30),         // (@diff)
  /* addr  26 */ CLF,
  /* addr  27 */ // Label 'next'
  /* addr  27 */ SHL(R3, R3),
  /* addr  28 */ JMP(14),        // (@loop)
  /* addr  30 */ // Label 'diff'
  /* addr  30 */ DATA(R3, 0),    // (00000000)
  /* addr  32 */ LD(R3, R2),
  /* addr  33 */ ST(R3, R1),
  /* addr  34 */ NOT(R2, R2),
  /* addr  35 */ DATA(R3, 1),    // (00000001)
  /* addr  37 */ CLF,
  /* addr  38 */ ADD(R3, R2),
  /* addr  39 */ CLF,
  /* addr  40 */ ADD(R1, R2),
  /* addr  41 */ DATA(R3, 2),    // (00000011)
  /* addr  43 */ OUTA(R3),
  /* addr  44 */ OUTD(R0),
  /* addr  45 */ OUTD(R1),
  /* addr  46 */ OUTD(R2),
  /* addr  47 */ DATA(R3, 0),    // (00000000)
  /* addr  49 */ OUTA(R3),
  /* addr  50 */ DATA(R3, 10),   // (00001010)
  /* addr  52 */ OUTD(R3),
  /* addr  53 */ DATA(R2, 1),    // (00000001)
  /* addr  55 */ CLF,
  /* addr  56 */ ADD(R2, R0),
  /* addr  57 */ DATA(R2, 15),   // (00001111)
  /* addr  59 */ CMP(R0, R2),
  /* addr  60 */ JA(64),         // (@done)
  /* addr  62 */ JMP(5),         // (@do)
  /* addr  64 */ // Label 'done'
  /* addr  64 */ HALT,
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
  DATA(R0, 5),
  DATA(R1, 0),
  DATA(R2, 47),
  ST(R0, R2),
  DATA(R2, 92),
  ST(R1, R2),
  DATA(R2, 10),
  OUTA(R1),
  OUTD(R2),
  DATA(R3, 216),
  OUTA(R0),
  IND(R2),
  SHR(R2, R2),
  OUTA(R1),
  JC(25),
  LD(R0, R2),
  JMP(26),
  LD(R1, R2),
  OUTD(R2),
  DATA(R2, 1),
  CLF,
  ADD(R2, R3),
  JZ(10),  
  JMP(16),
  HALT
} ;


#endif
