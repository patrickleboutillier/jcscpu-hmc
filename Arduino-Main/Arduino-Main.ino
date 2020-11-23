#include "Extension.h"
#include "BUS.h"
#include "RAM.h"
#include "ALU.h"
#include "CLK.h"
#include "INST.h"
#include "CW.h"
#include "IO.h"
#include "PROGRAMS.h"


#define ALU_DEBUG     0
#define RAM_DEBUG     0
#define CLK_DEBUG     0
#define INST_DEBUG    1
#define CW_DEBUG      1
#define IO_DEBUG      1

#define HZ            0
#define RESET_MS      1000
#define INIT_WAIT_MS  1000

#define PROGRAM       prog42


unsigned long STARTED = false;
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
  HALTED = false ;
}


void loop(){
  if (HALTED){
    return ;
  }
  
  if (CLK_IO_PRESENT){
    CLK.loop(RESET, CLK_DEBUG) ;
  }

  bool be = false ;
  be |= RAM.loop(RAM_DEBUG) ;
  
  if (ALU_PRESENT){  
    be |= ALU.loop(ALU_DEBUG) ;
  }
  if (INST_PRESENT){  
    unsigned long cw = INST.loop(RESET, CLK.clk_e(), CLK.clk_s(), CLK.step(), INST_DEBUG) ;
    // Send cw to the shift registers.
    CW.loop(RESET, cw, CW_DEBUG) ;
  }
  if (CLK_IO_PRESENT){
    be |= IO.loop(IO_DEBUG) ;
  }
      
  if (! be){
    // No parts are writing to the bus
    BUS.reset() ;
  }
 
  // Placed here to make sure we pass at least once through the loop during RESET.
  if ((RESET)&&(millis() > STARTED + RESET_MS)){
    RESET = false ;
    Serial.println(F("SYSTEM: Reset done.")) ;
  }
}
