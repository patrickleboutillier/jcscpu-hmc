#include "Extension.h"
#include "BUS.h"
#include "RAM.h"
#include "ALU.h"
#include "CLK.h"


#define HZ  4


Extension E1(1) ;
Extension E2(2) ;
Extension E3(3) ;

BUS BUS(12, 11, 10, 9, 8, 7, 6, 5) ;
RAM RAM(&BUS, 4, 3, 2) ;
ALU ALU(&E2, &BUS, 12, 11, 10, 9, 5, 4, 3, 2, A0, A1, A2, A3) ;
CLK CLK(&E3, HZ, 9, 8, 7, 6, 5, 4, 3, 2) ;


void setup(){
  Serial.begin(9600) ;
  E1.enableDigitalCache() ;
  E2.enableDigitalCache() ;
  E3.enableDigitalCache() ;
  RAM.setup() ;
  ALU.setup() ;
  CLK.setup() ;
}


void loop(){
  bool be = false ;
  CLK.loop(true) ;
  be |= RAM.loop(true) ;
  be |= ALU.loop(true) ;
  //bus = run_loop(bus, RAM.loop(bus, true)) ;
  //Serial.print("RAM sends to bus: ") ;
  //Serial.println(bus) ;
  //bus = run_loop(bus, ALU.loop(bus)) ;

  if (! be){
    // No parts are writing to the bus
    BUS.reset() ;
  }
 
  Serial.print("BUS = ") ;
  Serial.println(BUS.read()) ;
}


byte run_loop(byte bus, int part){
  return (part == -1 ? bus : part) ;
}
