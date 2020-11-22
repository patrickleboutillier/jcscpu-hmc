#include "Arduino.h"
#include "CLK.h"


#define DEBOUNCE_DELAY_MS 50


CLK::CLK(Extension *e, int HZ, int pin_BUTTON, int pin_WAITING, int pin_CLK_e, int pin_CLK_s, int pin_STEP_1, int pin_STEP_2, int pin_STEP_3,
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
  _pin_BUTTON = pin_BUTTON ;
  _pin_WAITING = pin_WAITING ;

  _mode = (!HZ ? CLK_MANUAL : CLK_AUTOMATIC) ;
  _button_state = (_mode == CLK_MANUAL ? HIGH : LOW) ;
  _last_button_state = _button_state ;
  _last_debounce_time = 0 ;
}


bool CLK::clk_e(){
  return _clk_e ;
}


bool CLK::clk_s(){
  return _clk_s ;
}


byte CLK::step(){
  return _step ;
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
  _e->pinMode(_pin_BUTTON, INPUT) ;
  _e->pinMode(_pin_WAITING, OUTPUT) ;
  
  if (_e->digitalRead(_pin_BUTTON) == HIGH){
    // Switch mode
    _mode = !_mode ;
  }

  if (_mode == CLK_MANUAL){
    _e->digitalWrite(_pin_WAITING, HIGH) ;
  }
}


bool CLK::loop(bool reset, bool debug = 0){
  bool tick  = false ;
  
  if (reset){
    // Turn on the waiting LED
    _e->digitalWrite(_pin_WAITING, HIGH) ; 
  }
  else {
    if (_mode == CLK_AUTOMATIC){
      _e->digitalWrite(_pin_WAITING, LOW) ;
      unsigned long now = millis() ;
      if ((now - _then) >= (1000 / _HZ)){
        tick = qtick(debug) ;
        _then = now ;
      }
    }
    else {
      if (button_pressed()){
        tick = qtick(debug) ;
      }
    }
  }

  _e->digitalWrite(_pin_CLK_e, _clk_e) ;
  _e->digitalWrite(_pin_CLK_s, _clk_s) ;
  _e->digitalWrite(_pin_STEP_1, (_step == 1)) ;
  _e->digitalWrite(_pin_STEP_2, (_step == 2)) ;
  _e->digitalWrite(_pin_STEP_3, (_step == 3)) ;
  _e->digitalWrite(_pin_STEP_4, (_step == 4)) ;
  _e->digitalWrite(_pin_STEP_5, (_step == 5)) ;
  _e->digitalWrite(_pin_STEP_6, (_step == 6)) ;

  return tick ;
}


bool CLK::qtick(bool debug){
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

  if (debug){
    Serial.print("  CLK(clk_e:") ;
    Serial.print(_clk_e) ;
    Serial.print(", clk_s:") ;
    Serial.print(_clk_s) ;
    Serial.print(", step:") ;
    Serial.print(_step) ;   
    Serial.println(")") ;
  }

  return true ;
}


/*
  Generic debouncing code from https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
*/
bool CLK::button_pressed(){
  bool ret = 0 ;
  int reading = _e->digitalRead(_pin_BUTTON) ;
  
  if (reading != _last_button_state) {
    _last_debounce_time = millis() ;
  }
  
  if ((millis() - _last_debounce_time) > DEBOUNCE_DELAY_MS){
    if (reading != _button_state){
      _button_state = reading ;
      if (_button_state == HIGH){
        ret = 1 ;
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  _last_button_state = reading ;
   
  return ret ;
}


/*
bool clk_automatic ;
bool clk_started ;
unsigned long clk_then ;
long clk_qtick ;
byte clk_step ; 

bool buttonState ;
bool lastButtonState ;



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
}


void setup_CLK(){
  pinMode(CLK_MANUAL, INPUT) ;
  pinMode(CLK_WAITING, OUTPUT) ;

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

*/
