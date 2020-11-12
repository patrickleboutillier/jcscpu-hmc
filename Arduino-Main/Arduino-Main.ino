#include "Extension.h"
#include "RAM.h"
#include "ALU.h"
#include "CLK.h"

Extension E1(1) ;
Extension E2(2) ;
Extension E3(3) ;


#define HZ  1


RAM RAM(&E1, A0, A1, A2) ;
ALU ALU(&E2, 12, 11, 10, 9, 5, 4, 3, 2, A0, A1, A2, A3) ;
CLK CLK(&E3, HZ, 9, 8, 7, 6, 5, 4, 3, 2) ;
int BUS = 0 ;


void setup(){
  Serial.begin(9600) ;
  E1.enableDigitalCache() ;
  E2.enableDigitalCache() ;
  RAM.setup() ;
  ALU.setup() ;
}


void loop(){
  int bus = BUS ;

  int alu_res = ALU.loop(bus) ;
  bus = (alu_res == -1 ? bus : alu_res) ;
  int ram_res = RAM.loop(bus) ;
  bus = (ram_res == -1 ? bus : ram_res) ;
  
  BUS = bus ;   
  Serial.print("BUS = ") ;
  Serial.println(BUS) ;
}
