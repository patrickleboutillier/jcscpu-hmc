#ifndef ASM_H
#define ASM_H


typedef enum Reg { R0 = 0, R1 = 1, R2 = 2, R3 = 3 } ;


#define C   B1000
#define A   B0100
#define E   B0010
#define Z   B0001

// ALU instructions
#define ADD(ra, rb)       (B10000000 | (ra << 2) | rb)
#define SHL(ra, rb)       (B10010000 | (ra << 2) | rb)
#define SHR(ra, rb)       (B10100000 | (ra << 2) | rb)
#define NOT(ra, rb)       (B10110000 | (ra << 2) | rb)
#define AND(ra, rb)       (B11000000 | (ra << 2) | rb)
#define OR(ra, rb)        (B11010000 | (ra << 2) | rb)
#define XOR(ra, rb)       (B11100000 | (ra << 2) | rb)
#define CMP(ra, rb)       (B11110000 | (ra << 2) | rb)

// Load RB from RAM address in RA
#define LD(ra, rb)        (B00000000 | (ra << 2) | rb)
// Store RB to RAM address in RA
#define ST(ra, rb)        (B00010000 | (ra << 2) | rb)
// #define DATA(rb, data)    _DATA(rb), data
#define DATA(rb, data)    (B00100000 | rb), data

#define JMPR(rb)          (B00110000 | rb)
#define JMP(addr)         B01000000, addr

#define JC(addr)          (B01010000 | C), addr
#define JA(addr)          (B01010000 | A), addr
#define JE(addr)          (B01010000 | E), addr
#define JZ(addr)          (B01010000 | Z), addr
#define JCA(addr)         (B01010000 | C | A), addr
#define JCE(addr)         (B01010000 | C | E), addr
#define JCZ(addr)         (B01010000 | C | Z), addr
#define JAE(addr)         (B01010000 | A | E), addr
#define JAZ(addr)         (B01010000 | A | Z), addr
#define JEZ(addr)         (B01010000 | E | Z), addr
#define JCAE(addr)        (B01010000 | C | A | E), addr
#define JCAZ(addr)        (B01010000 | C | A | Z), addr
#define JCEZ(addr)        (B01010000 | C | E | Z), addr
#define JAEZ(addr)        (B01010000 | A | E | Z), addr
#define JCAEZ(addr)       (B01010000 | C | A | E | Z), addr

#define CLF               B01100000
#define HALT              B01101000

#define IND(rb)          (B01110000 | rb)
#define INA(rb)          (B01110100 | rb)
#define OUTD(rb)         (B01111000 | rb)
#define OUTA(rb)         (B01111100 | rb)

#endif
