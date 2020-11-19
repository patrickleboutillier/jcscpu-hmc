#ifndef CLK_H
#define CLK_H

#include "Arduino.h"
#include "Extension.h"


#define CLK_MANUAL    0
#define CLK_AUTOMATIC 1


class CLK {
  public:
    CLK(Extension *e, int HZ, int pin_BUTTON, int pin_WAITING, int pin_CLK_e, int pin_CLK_s, int pin_STEP_1, int pin_STEP_2, int pin_STEP_3,
      int pin_STEP_4, int pin_STEP_5, int pin_STEP_6) ;
    void setup() ;
    bool loop(bool reset, bool debug = 0) ;
    bool clk_e() ;
    bool clk_s() ;
    byte step() ;
  private:
    bool qtick(bool debug) ;
    bool button_pressed() ;
    Extension *_e ;
    unsigned long _then ;
    long _qtick ;
    bool _clk_e ;
    bool _clk_s ;
    byte _step ;
    int _HZ ;
    int _pin_CLK_e ;
    int _pin_CLK_s ;
    int _pin_STEP_1 ;
    int _pin_STEP_2 ;
    int _pin_STEP_3 ;
    int _pin_STEP_4 ;
    int _pin_STEP_5 ;
    int _pin_STEP_6 ;
    int _pin_BUTTON ;
    int _pin_WAITING ;

    bool _mode ;
    bool _button_state ;
    bool _last_button_state ;
    unsigned long _last_debounce_time ;
} ;

#endif
