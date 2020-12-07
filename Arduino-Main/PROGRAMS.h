#ifndef PROGRAMS_h
#define PROGRAMS_h

#include "ASM.h"


PROGMEM const byte progggamehll[] = {
  /* addr   0 */ DATA(R0, 255),  // (11111111)
  /* addr   2 */ DATA(R1, 255),  // (11111111)
  /* addr   4 */ ST(R1, R0),
  /* addr   5 */ DATA(R0, 0),    // (00000000)
  /* addr   7 */ DATA(R1, 253),  // (11111101)
  /* addr   9 */ ST(R1, R0),
  /* addr  10 */ // Label 'WHILE10'
  /* addr  10 */ DATA(R0, 1),    // (00000001)
  /* addr  12 */ DATA(R1, 252),  // (11111100)
  /* addr  14 */ ST(R1, R0),
  /* addr  15 */ DATA(R0, 252),  // (11111100)
  /* addr  17 */ LD(R0, R0),
  /* addr  18 */ OR(R0, R0),
  /* addr  19 */ JZ(219),   // (@ELSE19)
  /* addr  21 */ // guess
  /* addr  21 */ DATA(R0, 255),  // (11111111)
  /* addr  23 */ LD(R0, R0),     
  /* addr  24 */ DATA(R1, 253),  // (11111101)
  /* addr  26 */ LD(R1, R1),
  /* addr  27 */ NOT(R1, R1),
  /* addr  28 */ DATA(R2, 1),    // (00000001)
  /* addr  30 */ CLF,
  /* addr  31 */ ADD(R2, R1),
  /* addr  32 */ CLF,
  /* addr  33 */ ADD(R0, R1),
  /* addr  34 */ DATA(R0, 251),  // (11111011)
  /* addr  36 */ ST(R0, R1),
  /* addr  37 */ DATA(R1, 251),  // (11111011)
  /* addr  39 */ LD(R1, R0),
  /* addr  40 */ CLF,
  /* addr  41 */ SHR(R0, R0),
  /* addr  42 */ ST(R1, R0),
  /* addr  43 */ DATA(R0, 253),  // (11111101)
  /* addr  45 */ LD(R0, R0),
  /* addr  46 */ DATA(R1, 251),  // (11111011)
  /* addr  48 */ LD(R1, R1),
  /* addr  49 */ CLF,
  /* addr  50 */ ADD(R0, R1),
  /* addr  51 */ DATA(R0, 254),  // (11111110)
  /* addr  53 */ ST(R0, R1),
  /* addr  54 */ DATA(R0, 254),  // (11111110)
  /* addr  56 */ LD(R0, R0),
  /* addr  57 */ DATA(R1, 1),    // (00000001)
  /* addr  59 */ OUTA(R1),
  /* addr  60 */ OUTD(R0),
  /* addr  61 */ DATA(R0, 63),   // (00111111)
  /* addr  63 */ DATA(R1, 250),  // (11111010)
  /* addr  65 */ ST(R1, R0),
  /* addr  66 */ DATA(R0, 250),  // (11111010)
  /* addr  68 */ LD(R0, R0),     
  /* addr  69 */ XOR(R1, R1),
  /* addr  70 */ OUTA(R1),
  /* addr  71 */ OUTD(R0),
  /* addr  72 */ DATA(R0, 32),   // (00100000)
  /* addr  74 */ DATA(R1, 249),  // (11111001)
  /* addr  76 */ ST(R1, R0),
  /* addr  77 */ DATA(R0, 249),  // (11111001)
  /* addr  79 */ LD(R0, R0),
  /* addr  80 */ XOR(R1, R1),
  /* addr  81 */ OUTA(R1),
  /* addr  82 */ OUTD(R0),
  /* addr  83 */ // Get char
  /* addr  83 */ DATA(R0, 0),    // (00000000)
  /* addr  85 */ DATA(R1, 248),  // (11111000)
  /* addr  87 */ ST(R1, R0),
  /* addr  88 */ DATA(R0, 0),    // (00000000)
  /* addr  90 */ DATA(R1, 247),  // (11110111)
  /* addr  92 */ ST(R1, R0),
  /* addr  93 */ // Label 'WHILE93'
  /* addr  93 */ DATA(R0, 247),  // (11110111)
  /* addr  95 */ LD(R0, R0),
  /* addr  96 */ DATA(R1, 248),  // (11111000)
  /* addr  98 */ LD(R1, R1),
  /* addr  99 */ DATA(R2, 1),    // (00000001)
  /* addr 101 */ CMP(R0, R1),
  /* addr 102 */ JE(105),    // (@EQ102)
  /* addr 104 */ XOR(R2, R2),
  /* addr 105 */ // Label 'EQ102'
  /* addr 105 */ DATA(R0, 246),  // (11110110)
  /* addr 107 */ ST(R0, R2),
  /* addr 108 */ DATA(R0, 246),  // (11110110)
  /* addr 110 */ LD(R0, R0),
  /* addr 111 */ OR(R0, R0),     
  /* addr 112 */ JZ(122),  // (@ELSE112)
  /* addr 114 */ XOR(R0, R0),
  /* addr 115 */ OUTA(R0),
  /* addr 116 */ IND(R0),
  /* addr 117 */ DATA(R1, 247),  // (11110111)
  /* addr 119 */ ST(R1, R0),
  /* addr 120 */ // GOTO @FI112
  /* addr 120 */ JMP(124),   // (@FI112)
  /* addr 122 */ // Label 'ELSE112'
  /* addr 122 */ // GOTO @ELIHW93
  /* addr 122 */ JMP(126),  // (@ELIHW93)
  /* addr 124 */ // Label 'FI112'
  /* addr 124 */ // GOTO @WHILE93
  /* addr 124 */ JMP(93),  // (@WHILE93)
  /* addr 126 */ // Label 'ELIHW93'
  /* addr 126 */ // Check char
  /* addr 126 */ DATA(R0, 104),  // (01101000)
  /* addr 128 */ DATA(R1, 245),  // (11110101)
  /* addr 130 */ ST(R1, R0),
  /* addr 131 */ DATA(R0, 247),  // (11110111)
  /* addr 133 */ LD(R0, R0),
  /* addr 134 */ DATA(R1, 245),  // (11110101)
  /* addr 136 */ LD(R1, R1),
  /* addr 137 */ DATA(R2, 1),    // (00000001)
  /* addr 139 */ CMP(R0, R1),
  /* addr 140 */ JE(143),    // (@EQ140)
  /* addr 142 */ XOR(R2, R2),    
  /* addr 143 */ // Label 'EQ140'
  /* addr 143 */ DATA(R0, 244),  // (11110100)
  /* addr 145 */ ST(R0, R2),
  /* addr 146 */ DATA(R0, 244),  // (11110100)
  /* addr 148 */ LD(R0, R0),
  /* addr 149 */ OR(R0, R0),
  /* addr 150 */ JZ(158),    // (@FI150)
  /* addr 152 */ DATA(R0, 254),  // (11111110)
  /* addr 154 */ LD(R0, R0),
  /* addr 155 */ DATA(R1, 253),  // (11111101)
  /* addr 157 */ ST(R1, R0),
  /* addr 158 */ // Label 'FI150'
  /* addr 158 */ DATA(R0, 108),  // (01101100)
  /* addr 160 */ DATA(R1, 243),  // (11110011)
  /* addr 162 */ ST(R1, R0),
  /* addr 163 */ DATA(R0, 247),  // (11110111)
  /* addr 165 */ LD(R0, R0),
  /* addr 166 */ DATA(R1, 243),  // (11110011)
  /* addr 168 */ LD(R1, R1),
  /* addr 169 */ DATA(R2, 1),    // (00000001)
  /* addr 171 */ CMP(R0, R1),
  /* addr 172 */ JE(175),    // (@EQ172)
  /* addr 174 */ XOR(R2, R2),
  /* addr 175 */ // Label 'EQ172'
  /* addr 175 */ DATA(R0, 242),  // (11110010)
  /* addr 177 */ ST(R0, R2),
  /* addr 178 */ DATA(R0, 242),  // (11110010)
  /* addr 180 */ LD(R0, R0),
  /* addr 181 */ OR(R0, R0),
  /* addr 182 */ JZ(190),    // (@FI182)
  /* addr 184 */ DATA(R0, 254),  // (11111110)
  /* addr 186 */ LD(R0, R0),
  /* addr 187 */ DATA(R1, 255),  // (11111111)
  /* addr 189 */ ST(R1, R0),
  /* addr 190 */ // Label 'FI182'
  /* addr 190 */ DATA(R0, 61),   // (00111101)
  /* addr 192 */ DATA(R1, 241),  // (11110001)
  /* addr 194 */ ST(R1, R0),
  /* addr 195 */ DATA(R0, 247),  // (11110111)
  /* addr 197 */ LD(R0, R0),     
  /* addr 198 */ DATA(R1, 241),  // (11110001)
  /* addr 200 */ LD(R1, R1),
  /* addr 201 */ DATA(R2, 1),    // (00000001)
  /* addr 203 */ CMP(R0, R1),
  /* addr 204 */ JE(207),    // (@EQ204)
  /* addr 206 */ XOR(R2, R2),
  /* addr 207 */ // Label 'EQ204'
  /* addr 207 */ DATA(R0, 240),  // (11110000)
  /* addr 209 */ ST(R0, R2),
  /* addr 210 */ DATA(R0, 240),  // (11110000)
  /* addr 212 */ LD(R0, R0),
  /* addr 213 */ OR(R0, R0),
  /* addr 214 */ JZ(217),    // (@FI214)
  /* addr 216 */ HALT,
  /* addr 217 */ // Label 'FI214'
  /* addr 217 */ // GOTO @FI19
  /* addr 217 */ JMP(221),    // (@FI19)
  /* addr 219 */ // Label 'ELSE19'
  /* addr 219 */ // GOTO @ELIHW10
  /* addr 219 */ JMP(223),  // (@ELIHW10)
  /* addr 221 */ // Label 'FI19'
  /* addr 221 */ // GOTO @WHILE10
  /* addr 221 */ JMP(10),  // (@WHILE10)
  /* addr 223 */ // Label 'ELIHW10'
} ;


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
