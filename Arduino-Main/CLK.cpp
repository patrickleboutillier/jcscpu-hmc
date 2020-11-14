#include "Arduino.h"
#include "CLK.h"


CLK::CLK(Extension *e, int HZ, int pin_CLK_e, int pin_CLK_s, int pin_STEP_1, int pin_STEP_2, int pin_STEP_3,
      int pin_STEP_4, int pin_STEP_5, int pin_STEP_6){
  _e = e ;
  _then = 0 ;
  _qtick = -1 ;
  _clk_e = 0 ;
  _clk_s = 0 ;
  _step = 0 ;
  _HZ = HZ ;
  
  _pin_CLK_e = pin_CLK_e ;
  _pin_CLK_s = pin_CLK_s ;
  _pin_STEP_1 = pin_STEP_1 ;
  _pin_STEP_2 = pin_STEP_2 ;
  _pin_STEP_3 = pin_STEP_3 ;
  _pin_STEP_4 = pin_STEP_4 ;
  _pin_STEP_5 = pin_STEP_5 ;
  _pin_STEP_6 = pin_STEP_6 ;
}


void CLK::setup(){
  _e->pinMode(_pin_CLK_e, OUTPUT) ;
  _e->pinMode(_pin_CLK_s, OUTPUT) ;
  _e->pinMode(_pin_STEP_1, OUTPUT) ;
  _e->pinMode(_pin_STEP_2, OUTPUT) ;
  _e->pinMode(_pin_STEP_3, OUTPUT) ;
  _e->pinMode(_pin_STEP_4, OUTPUT) ;
  _e->pinMode(_pin_STEP_5, OUTPUT) ;
  _e->pinMode(_pin_STEP_6, OUTPUT) ;
}


bool CLK::loop(bool debug = 0){
  unsigned long now = millis() ;
  if ((now - _then) >= (1000 / _HZ)){
    qtick(debug) ;
    _e->digitalWrite(_pin_CLK_e, _clk_e) ;
    _e->digitalWrite(_pin_CLK_s, _clk_s) ;
    _e->digitalWrite(_pin_STEP_1, (_step == 1)) ;
    _e->digitalWrite(_pin_STEP_2, (_step == 2)) ;
    _e->digitalWrite(_pin_STEP_3, (_step == 3)) ;
    _e->digitalWrite(_pin_STEP_4, (_step == 4)) ;
    _e->digitalWrite(_pin_STEP_5, (_step == 5)) ;
    _e->digitalWrite(_pin_STEP_6, (_step == 6)) ;
    _then = now ;
  }

  return false ;
}


void CLK::qtick(bool debug){
  // Update qtick
  _qtick++ ;

  switch (_qtick % 4){
    case 0:
      _clk_e = 1 ;
      _clk_s = 0 ;
      break ;
    case 1:
      _clk_e = 1 ;
      _clk_s = 1 ;
      break ;
    case 2:
      _clk_e = 1 ;
      _clk_s = 0 ;
      break ;
    case 3:
      _clk_e = 0 ;
      _clk_s = 0 ;
      break ;
  }

  if ((_qtick % 4) == 0){
    _step++ ;
    if (_step == 7){
      _step = 1 ;
    }
  }

  Serial.print("  CLK(clk_e:") ;
  Serial.print(_clk_e) ;
  Serial.print(", clk_s:") ;
  Serial.print(_clk_s) ;
  Serial.print(", step:") ;
  Serial.print(_step) ;   
  Serial.println(")") ;
}


/*
bool clk_automatic ;
bool clk_started ;
unsigned long clk_then ;
long clk_qtick ;
byte clk_step ; 

bool buttonState ;
bool lastButtonState ;
unsigned long lastDebounceTime = 0 ;
unsigned long debounceDelay = 50 ;


bool button_pressed(byte button) ;
void qtick() ;


void reset_CLK(){
  clk_started = 0 ;
  clk_then = millis() ;
  clk_qtick = -1 ;
  clk_step = 0 ; 

  if (clk_automatic){
    buttonState = LOW ;
    lastButtonState = LOW ;
  }
  else {
    buttonState = HIGH ;
    lastButtonState = HIGH ;
  }
  
  digitalWrite(CLK_WAITING, HIGH) ;  
  digitalWrite(CLKSTP_ENABLE, HIGH) ; 
}


void setup_CLK(){
  pinMode(CLK_MANUAL, INPUT) ;
  pinMode(CLK_WAITING, OUTPUT) ;

  pinMode(CLKSTP_DATA, OUTPUT) ; 
  pinMode(CLKSTP_LATCH, OUTPUT) ; 
  pinMode(CLKSTP_CLOCK, OUTPUT) ; 
  pinMode(CLKSTP_ENABLE, OUTPUT) ; 

  clk_automatic = 1 ;
  if (digitalRead(CLK_MANUAL) == HIGH){
    // Request to have clock in manual mode
    clk_automatic = 0 ;
  }  
}


void loop_CLK(byte slowdown){
  if (clk_automatic){
    if (! clk_started){
      //if (button_pressed(CLK_MANUAL)){
        //delay(1000) ;
        clk_started = 1 ;
        digitalWrite(CLK_WAITING, LOW) ;
        return ;
      //}
    }
    else {
      // Automatic clock
      unsigned long clk_now = millis() ;
      if ((clk_now - clk_then) >= (1000 / ((CLK_HZ / slowdown) * 4))){
        qtick() ;
        clk_then = clk_now ;
      }
    }
  }
  else {
    // Manual clock
    if (button_pressed(CLK_MANUAL)){
      qtick() ;
    }
  }
}


// Generic debouncing code from https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
bool button_pressed(byte button){
  bool ret = 0 ;
  int reading = digitalRead(button) ;
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis() ;
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay){
    if (reading != buttonState){
      buttonState = reading ;
      if (buttonState == HIGH){
        ret = 1 ;
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading ;
   
  return ret ;
}

*/
