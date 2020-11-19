#include "Extension.h"
#include "BUS.h"
#include "RAM.h"
#include "ALU.h"
#include "CLK.h"


#define RAM_PART
#define ALU_PART  
#define CLK_PART
#define INST_PART 

#define HZ          4
#define RESET_MS    1000


unsigned long STARTED ;
bool RESET ;

BUS BUS(12, 11, 10, 9, 8, 7, 6, 5) ;
RAM RAM(&BUS, 4, 3, 2) ;
#ifdef ALU_PART
  Extension E1(1) ;
  ALU ALU(&E1, &BUS, A0, A1, A2, 8, 12, 11, 10, 9, 7, 6, 5, 4) ;
#endif
#ifdef CLK_PART
  Extension E2(2) ;
  CLK CLK(&E2, HZ, 4, 3, 12, 11, 10, 9, 8, 7, 6, 5) ;
#endif
#ifdef INST_PART
  // Extension E3(3) ;
#endif


void setup(){
  Serial.begin(9600) ;
  Serial.print("Waiting for extention Arduinos to powerup...") ;
  Serial.print("ok.") ;
  delay(1000) ;

  RAM.setup() ;
  #ifdef ALU_PART
    E1.enableDigitalCache() ;
    ALU.setup() ;
  #endif
  #ifdef CLK_PART
    E2.enableDigitalCache() ;
    CLK.setup() ;
  #endif
  // E3.enableDigitalCache() ;
  
  STARTED = millis() ;
  RESET = true ;
}


void loop(){
  #ifdef CLK_PART
    CLK.loop(RESET, true) ;
  #endif

  bool be = false ;
  be |= RAM.loop(true) ;
  
  #ifdef ALU_PART  
    be |= ALU.loop(false) ;
  #endif
    
  if (! be){
    // No parts are writing to the bus
    BUS.reset() ;
  }
 
  //Serial.print("BUS = ") ;
  //Serial.println(BUS.read()) ;

  // Placed here to make sure we pass at least once through the loop during RESET.
  if ((RESET)&&(millis() > STARTED + RESET_MS)){
    RESET = false ;
  }
}
