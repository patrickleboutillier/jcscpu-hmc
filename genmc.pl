#!/usr/bin/perl

use strict ;

open(MICRO, ">MICROCODE.h") or die() ;

my %INSTS = (
    '0000' => { 
        'name' => 'LD',
        '4e' => 'RegA_e',
        '4s' => 'MAR_s',
        '5e' => 'RAM_e',
        '5s' => 'RegB_s',
    },
    '0001' => { 
        'name' => 'ST',
        '4e' => 'RegA_e',
        '4s' => 'MAR_s',
        '5e' => 'RegB_e',
        '5s' => 'RAM_s',
    },
    '0010' => { 
        'name' => 'DATA',
        '4e' => 'BUS1|IAR_e',
        '4s' => 'MAR_s|ACC_s',
        '5e' => 'RAM_e',
        '5s' => 'RegB_s',
        '6e' => 'ACC_e',
        '6s' => 'IAR_s',
        skip => sub { if ($_[0] > 3) { return "Invalid instruction"} ; return undef ;},
    },
    '0011' => { 
        'name' => 'JMPR',
        '4e' => 'RegB_e',
        '4s' => 'IAR_s',
        skip => sub { if ($_[0] > 3) { return "Invalid instruction"} ; return undef ;},
    },
    '0101' => { 
        'name' => 'JCOND',
        '4e' => 'BUS1|IAR_e',
        '4s' => 'MAR_s|ACC_s',
        '5e' => 'ACC_e',
        '5s' => 'IAR_s',
        '6e' => 'RAM_e',
        '6s' => 'JCOND',
    },
    '0100' => { 
        'name' => 'JMP',
        '4e' => 'IAR_e',
        '4s' => 'MAR_s',
        '5e' => 'RAM_e',
        '5s' => 'IAR_s',
        skip => sub { if ($_[0] > 0) { return "Invalid instruction"} ; return undef ;},
    },
    '01100' => { 
        'name' => 'CLF',
        '4e' => 'BUS1',
        '4s' => 'FLAGS_s',
        skip => sub { if ($_[0] > 0) { return "Invalid instruction"} ; return undef ;},
    },
    '01101' => { 
        'name' => 'HLT',
        '4e' => 'HLT',
        skip => sub { if ($_[0] > 0) { return "Invalid instruction"} ; return undef ;},
    },
    '0111' => { 
        'name' => 'IO',
        skip => sub { if ($_[0] >= 0) { return "Not implemented"} ; return undef ;},
    },
    ALU('1000', 'ADD'),
    ALU('1001', 'SHR'),
    ALU('1010', 'SHL'),
    ALU('1011', 'NOT'),
    ALU('1100', 'AND'),
    ALU('1101', 'OR'),
    ALU('1110', 'XOR'),
    ALU('1111', 'CMP'),
) ;

my $now = localtime() ;
print MICRO <<CPP ;
/*
 * Microcode dispatch table.
 * This file was generated on $now by $0.  
 */

#ifndef MICROCODE_h
#define MICROCODE_h

#define HLT       0b10000000000000000000000000000000
#define MAR_s     0b01000000000000000000000000000000
#define RAM_e     0b00100000000000000000000000000000
#define RAM_s     0b00010000000000000000000000000000
// #define X      0b00001000000000000000000000000000
#define ALU2      0b00000100000000000000000000000000
#define ALU1      0b00000010000000000000000000000000
#define ALU0      0b00000001000000000000000000000000

#define TMP_s     0b00000000100000000000000000000000
#define ACC_e     0b00000000010000000000000000000000
#define ACC_s     0b00000000001000000000000000000000
#define BUS1      0b00000000000100000000000000000000
#define FLAGS_s   0b00000000000010000000000000000000
#define Ctmp_e    0b00000000000001000000000000000000
#define IAR_e     0b00000000000000100000000000000000
// #define X      0b00000000000000010000000000000000

#define IO_s      0b00000000000000001000000000000000
#define IO_e      0b00000000000000000100000000000000
#define IO_d      0b00000000000000000010000000000000
#define IO_a      0b00000000000000000001000000000000
#define R0_e      0b00000000000000000000100000000000
#define R1_e      0b00000000000000000000010000000000
#define R0_s      0b00000000000000000000001000000000
#define R1_s      0b00000000000000000000000100000000

// #define X      0b00000000000000000000000010000000
#define JCOND     0b00000000000000000000000001000000
#define IAR_s     0b00000000000000000000000000100000
#define R2_e      0b00000000000000000000000000010000
#define R3_e      0b00000000000000000000000000001000
#define R2_s      0b00000000000000000000000000000100
#define R3_s      0b00000000000000000000000000000010
#define IR_s      0b00000000000000000000000000000001


CPP

my $n = 0 ;
print MICRO "PROGMEM const unsigned long microcode[] = {\n" ;
foreach my $inst (sort keys %INSTS){
    my $arg_len = 8 - length($inst) ;
    my $arg_max = (2 ** $arg_len) - 1 ;
    foreach my $arg (0 .. $arg_max){
        foreach my $step (4, 5, 6){
            foreach my $clk ('e', 's'){
                my $binarg = sprintf("%0*b", $arg_len, $arg) ;
                my $bits = $INSTS{$inst}->{"$step$clk"} || '0' ;
                my $info = '' ;
                if ($INSTS{$inst}->{skip}){
                    my $msg = $INSTS{$inst}->{skip}->($arg) ;
                    if ($msg){
                        $info = " ($msg)" ;
                        $bits = 0 ;
                    }
                }
                $bits =~ s/RegA/RegAB('A', $arg)/e ;
                $bits =~ s/RegB/RegAB('B', $arg)/e ;
                printf MICRO "  /* Entry %4d (inst*6+((step-4)*2)+clk) -> %5s:$inst$binarg\@$step$clk $info */    ", $n, $INSTS{$inst}->{name} ;
                print MICRO "$bits,\n" ;
                $n++ ;
            }
        }   
    }
}
print MICRO "} ;\n\n#endif" ;


sub ALU {
    my $code = shift ;
    my $name = shift ;

    return (
        $code => { 
            'name' => $name,
            '4e' => 'RegB_e',
            '4s' => 'TMP_s',
            '5e' => 'RegA_e|Ctmp_e',
            '5s' => 'ACC_s|FLAGS_s',
            '6e' => 'ACC_e',
            '6s' => ($code == '1111' ? '' : 'RegB_s'),
        }
    ) ;
}


sub RegAB {
    my $reg = shift ;
    my $arg = shift ;

    if ($reg eq 'B'){
        $arg = $arg & 0b0011 ;
    }
    if ($reg eq 'A'){
        $arg = $arg >> 2 ; 
    }

    return "R$arg" ;
}