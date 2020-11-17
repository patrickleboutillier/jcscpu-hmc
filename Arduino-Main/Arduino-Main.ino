#include "Extension.h"
#include "BUS.h"
#include "RAM.h"
#include "ALU.h"
#include "CLK.h"


#define RAM_PART
#define ALU_PART   

#define HZ  4


BUS BUS(12, 11, 10, 9, 8, 7, 6, 5) ;
RAM RAM(&BUS, 4, 3, 2) ;
#ifdef ALU_PART
  Extension E1(1) ;
  ALU ALU(&E1, &BUS, A0, A1, A2, 8, 12, 11, 10, 9, 7, 6, 5, 4) ;
#endif
#ifdef CLK_PART
  Extension E2(2) ;
  CLK CLK(&E2, HZ, 9, 8, 7, 6, 5, 4, 3, 2) ;
#endif
// Extension E3(3) ;


void setup(){
  Serial.begin(9600) ;
  Serial.println("Waiting for extention Arduinos to powerup...") ;
  delay(1000) ;

  // E1.enableDigitalCache() ;
  // E2.enableDigitalCache() ;
  // E3.enableDigitalCache() ;
  RAM.setup() ;
  #ifdef ALU_PART
    ALU.setup() ;
  #endif
  #ifdef CLK_PART
    CLK.setup() ;
  #endif
}


void loop(){
  bool be = false ;

  #ifdef CLK_PART 
    CLK.loop(true) ;
  #endif
  
  be |= RAM.loop(true) ;
  
  #ifdef ALU_PART  
    be |= ALU.loop(true) ;
  #endif

  if (! be){
    // No parts are writing to the bus
    BUS.reset() ;
  }
 
  Serial.print("BUS = ") ;
  Serial.println(BUS.read()) ;
}
