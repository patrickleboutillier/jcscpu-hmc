#ifndef ASM_H
#define ASM_H


#define C   0b1000
#define A   0b0100
#define E   0b0010
#define Z   0b0001


typedef enum Reg { R0 = 0, R1 = 1, R2 = 2, R3 = 3 } ;


// ALU instructions
#define ADD(ra, rb)       (0b10000000 | (ra << 2) | rb)
#define SHR(ra, rb)       (0b10010000 | (ra << 2) | rb)
#define SHL(ra, rb)       (0b10100000 | (ra << 2) | rb)
#define NOT(ra, rb)       (0b10110000 | (ra << 2) | rb)
#define AND(ra, rb)       (0b11000000 | (ra << 2) | rb)
#define OR(ra, rb)        (0b11010000 | (ra << 2) | rb)
#define XOR(ra, rb)       (0b11100000 | (ra << 2) | rb)
#define CMP(ra, rb)       (0b11110000 | (ra << 2) | rb)

// Load RB from RAM address in RA
#define LD(ra, rb)        (0b00000000 | (ra << 2) | rb)
// Store RB to RAM address in RA
#define ST(ra, rb)        (0b00010000 | (ra << 2) | rb)
// Store DATA byte in RB
#define DATA(rb, data)    (0b00100000 | rb), data

#define JMPR(rb)          (0b00110000 | rb)
#define JMP(addr)         0b01000000, addr

#define JC(addr)          (0b01010000 | C), addr
#define JA(addr)          (0b01010000 | A), addr
#define JE(addr)          (0b01010000 | E), addr
#define JZ(addr)          (0b01010000 | Z), addr
#define JCA(addr)         (0b01010000 | C | A), addr
#define JCE(addr)         (0b01010000 | C | E), addr
#define JCZ(addr)         (0b01010000 | C | Z), addr
#define JAE(addr)         (0b01010000 | A | E), addr
#define JAZ(addr)         (0b01010000 | A | Z), addr
#define JEZ(addr)         (0b01010000 | E | Z), addr
#define JCAE(addr)        (0b01010000 | C | A | E), addr
#define JCAZ(addr)        (0b01010000 | C | A | Z), addr
#define JCEZ(addr)        (0b01010000 | C | E | Z), addr
#define JAEZ(addr)        (0b01010000 | A | E | Z), addr
#define JCAEZ(addr)       (0b01010000 | C | A | E | Z), addr

#define CLF               0b01100000
#define HALT              0b01101000

#define IND(rb)          (0b01110000 | rb)
#define INA(rb)          (0b01110100 | rb)
#define OUTD(rb)         (0b01111000 | rb)
#define OUTA(rb)         (0b01111100 | rb)

#endif
