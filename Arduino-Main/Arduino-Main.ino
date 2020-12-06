#include "Extension.h"
#include "BUS.h"
#include "RAM.h"
#include "ALU.h"
#include "CLK.h"
#include "INST.h"
#include "CW.h"
#include "IO.h"
#include "PROGRAMS.h"


#define PROGRAM       progggame   // The name of the program to run. See PROGRAMS.h

#define HZ            64          // Clock speed in HZ (1 step/sec = 4, 1 inst/sec = 24, max is about 53). Use 0 for manual clock.


#define DEBUG_ON      0           // Global debug flag. Must be set to 1 for any debug info to show up.
#define ALU_DEBUG     0           // Turn on ALU debug info.
#define RAM_DEBUG     0           // Turn on RAM debug info.
#define CLK_DEBUG     0           // Turn on CLK debug info.
#define INST_DEBUG    0           // Turn on INST debug info.
#define CW_DEBUG      0           // Turn on CW debug info.
#define IO_DEBUG      1           // Turn on IO debug info.

#define RESET_MS      1000        // Reset signal duration.
#define INIT_WAIT_MS  1000        // Initial wait period after power-on.


unsigned long STARTED = 0 ;
bool RESET = true ;
bool HALTED = false ;

bool ALU_PRESENT = false ;
bool CLK_IO_PRESENT = false ;
bool INST_PRESENT = false ;

CW CW(A0, A1, A2) ;
BUS BUS(12, 11, 10, 9, 8, 7, 6, 5) ;
RAM RAM(&BUS, PROGRAM, 4, 3, 2) ;
Extension E1(1, "ALU") ;
ALU ALU(&E1, &BUS, A0, A1, A2, 8, 12, 11, 10, 9, 7, 6, 5, 4) ;
Extension E2(2, "CLK & IO") ;
CLK CLK(&E2, HZ, 4, 3, 12, 11, 10, 9, 8, 7, 6, 5) ;
IO IO(&E2, &BUS, A0, A1, A2, A3) ;
Extension E3(3, "INST & CW") ;
INST INST(&E3, 12, 11, 10, 9, 8, 7, 6, 5, A3, 3, 2, 4) ;
int pin_HLT = A3 ;


void setup(){  
  Serial.begin(9600) ;
  Serial.println(F("SYSTEM: Waiting for extention Arduinos to power up...")) ;
  Serial.println(F("SYSTEM: Wait done.")) ;
  delay(INIT_WAIT_MS) ;

  if (E1.ping()){
    Serial.print(F("SYSTEM: Extension responsible for ")) ;
    Serial.print(E1.name()) ;
    Serial.println(F(" found.")) ;
    ALU_PRESENT = true ;
    if (E2.ping()){
      Serial.print(F("SYSTEM: Extension responsible for ")) ;
      Serial.print(E2.name()) ;
      Serial.println(F(" found.")) ;
      CLK_IO_PRESENT = true ;
      if (E3.ping()){
        Serial.print(F("SYSTEM: Extension responsible for ")) ;
        Serial.print(E3.name()) ;
        Serial.println(F(" found.")) ;
        INST_PRESENT = true ;
      }
    }
  }

  RAM.setup() ;
  if (ALU_PRESENT){
    E1.enableDigitalCache() ;
    ALU.setup() ;
  }
  if (CLK_IO_PRESENT){
    E2.enableDigitalCache() ;
    CLK.setup() ;
    IO.setup() ;
  }
  if (INST_PRESENT){
    E3.enableDigitalCache() ;
    INST.setup() ;
  }

  Serial.println(F("SYSTEM: Starting power-on reset...")) ;
  STARTED = millis() ;
  RESET = true ;
  
  pinMode(pin_HLT, INPUT) ;
  HALTED = false ;
}


void loop(){
  if (HALTED){
    return ;
  }
  
  if (CLK_IO_PRESENT){
    CLK.loop(RESET, DEBUG_ON & CLK_DEBUG) ;
  }

  bool be = false ;
  be |= RAM.loop(DEBUG_ON & RAM_DEBUG) ;
  
  if (ALU_PRESENT){  
    be |= ALU.loop(DEBUG_ON & ALU_DEBUG) ;
  }
  if (INST_PRESENT){  
    unsigned long cw = INST.loop(RESET, CLK.clk_e(), CLK.clk_s(), CLK.step(), DEBUG_ON & INST_DEBUG) ;
    // Send cw to the shift registers.
    CW.loop(RESET, cw, DEBUG_ON & CW_DEBUG) ;
  }
  if (CLK_IO_PRESENT){
    be |= IO.loop(DEBUG_ON & IO_DEBUG) ;
  }
  
  if (digitalRead(pin_HLT) == HIGH){
    Serial.print(F("SYSTEM: Halted after ")) ;
    Serial.print(millis() - STARTED) ;
    Serial.println(F("ms.")) ;
    HALTED  = true ;
  }
      
  if (! be){
    // No parts are writing to the bus, we reset it.
    BUS.reset() ;
  }
 
  // Placed here to make sure we pass at least once through the loop during RESET.
  if ((RESET)&&(millis() > STARTED + RESET_MS)){
    RESET = false ;
    Serial.println(F("SYSTEM: Reset done.")) ;
  }
}
