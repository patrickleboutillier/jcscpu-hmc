/* 

// Device types
#define TTY           0
#define TTY_NUM       1
#define RNG           2

// Shift register pins
#define CLOCK_OUT     2
#define DATA_OUT      3
#define LATCH_OUT     4
#define CLOCK_IN      5
#define DATA_IN       6
#define LATCH_IN      7
#define ENABLE_OUT    8
#define RESET         

// Control pins
#define IO_e      9
#define IO_s     12
#define IO_mode  10
#define IO_type  11


byte cur_dev = 0 ;

byte prev_IO_e ;
byte prev_IO_s ;


// Initialize LCC library
LiquidCrystal lcd(A0, A1, A5, A4, A3, A2) ;    
byte cur_pos = 0 ;
char buf[33] ;


void reset_IO(){
  prev_IO_e = LOW ;
  prev_IO_s = LOW ;

  // Clear TTY buffer
  cur_pos = 0 ;
  for (byte i = 0 ; i < 32 ; i++){
    buf[i] = ' ' ;
    tty_put(buf[i]) ;
  }
  buf[32] = '\0' ;
  cur_pos = 0 ;

  digitalWrite(CLOCK_OUT, LOW) ;
  digitalWrite(CLOCK_IN, LOW) ;
  digitalWrite(DATA_OUT, LOW) ;
  digitalWrite(LATCH_IN, LOW) ;
  digitalWrite(LATCH_OUT, HIGH) ;
  digitalWrite(ENABLE_OUT, HIGH) ;
}


void setup_IO(){
  pinMode(CLOCK_OUT, OUTPUT) ;
  pinMode(CLOCK_IN, OUTPUT) ;
  pinMode(DATA_OUT, OUTPUT) ;
  pinMode(DATA_IN, INPUT) ;
  pinMode(LATCH_OUT, OUTPUT) ;
  pinMode(LATCH_IN, OUTPUT) ;
  pinMode(ENABLE_OUT, OUTPUT) ;
  
  // Set up the number of columns and rows on the LCD
  lcd.begin(16, 2) ;
  // Create slash
  char slash[] = {0b00001, 0b00001, 0b00010, 0b00100, 0b00100, 0b01000, 0b10000, 0b10000} ;
  lcd.createChar(0, slash) ;
  // Create backslash
  char backslash[] = {0b10000, 0b10000, 0b01000, 0b00100, 0b00100, 0b00010, 0b00001, 0b00001} ;
  lcd.createChar(1, backslash) ;
}


void setup(){
  Serial.begin(9600) ;
  setup_IO() ;
  reset_IO() ;  
}


void loop(){
  byte cur_IO_e = digitalRead(IO_e) ;
  if (cur_IO_e != prev_IO_e){
    if (cur_IO_e){
      if (digitalRead(IO_mode) == LOW){ // INPUT
        if (digitalRead(IO_type) == LOW){ // DATA
          byte b = get_output() ;
          digitalWrite(LATCH_OUT, LOW) ;
          shiftOut(DATA_OUT, CLOCK_OUT, MSBFIRST, b) ;
          digitalWrite(LATCH_OUT, HIGH) ; 
          digitalWrite(ENABLE_OUT, LOW) ;
        }
      }
    }
    else {
      digitalWrite(ENABLE_OUT, HIGH) ;
    }
    prev_IO_e = cur_IO_e ;
  }

  byte cur_IO_s = digitalRead(IO_s) ;
  if (cur_IO_s != prev_IO_s){
    if (cur_IO_s){
      Serial.println(cur_IO_s) ;
      Serial.println(digitalRead(IO_mode)) ;
      Serial.println(digitalRead(IO_type)) ;
      if (digitalRead(IO_mode) == HIGH){ // OUTPUT
        if (digitalRead(IO_type) == LOW){ // DATA
          digitalWrite(CLOCK_IN, HIGH) ;
          digitalWrite(LATCH_IN, HIGH) ;
          byte b = shiftIn(DATA_IN, CLOCK_IN, MSBFIRST) ;
          digitalWrite(LATCH_IN, LOW) ;
          Serial.print("Read from bus:") ;
          Serial.println(b) ;
          dispatch_input(b) ;
        }
        else { // ADDR
          digitalWrite(CLOCK_IN, HIGH) ;
          digitalWrite(LATCH_IN, HIGH) ;
          cur_dev = shiftIn(DATA_IN, CLOCK_IN, MSBFIRST) ;
          digitalWrite(LATCH_IN, LOW) ;
          Serial.print("Cur dev set to:") ;
          Serial.println(cur_dev) ;
        }
      }
    }
    prev_IO_s = cur_IO_s ;
  }
}


void dispatch_input(byte b){
  switch (cur_dev){
    case TTY:
      tty_put(b) ;
      // Print the char on the LCD
      break ;
    case TTY_NUM:
      char s[8] ;
      sprintf(s, "%d", b) ;
      for (byte i = 0 ; i < strlen(s) ; i++){
        tty_put(s[i]) ;
      }
      break ;
    case RNG:
      // Do nothing, RNG is output-only.
      break ;
  }
}


byte get_output(){
  byte ret = 0 ;

  switch (cur_dev){
    case TTY:
    case TTY_NUM:
      // Do nothing, TTYs are input only.
      break ;
    case RNG:
      // Return a random byte
      ret = random(256) ;
  }

  return ret ;
}


void tty_put(char c){
  Serial.print("tty_put: ") ;
  Serial.println(c) ;
  if (cur_pos == 32){
    // Scroll up
    for (byte j = 0 ; j < 16 ; j++){
      buf[j] = buf[j+16] ;
      buf[j+16] = ' ' ;
    }
    cur_pos = 16 ;
  }
    
  buf[cur_pos] = c ;
  cur_pos++ ;

  for (int i = 0 ; i < 16 ; i++){
    lcd.setCursor(i, 0) ;
    tty_write(buf[i]) ;
  }
  for (int i = 0 ; i < 16 ; i++){
    lcd.setCursor(i, 1) ;
    tty_write(buf[i+16]) ; 
  }
}


void tty_write(byte b){
  switch (b){
    case 47:
      b = 0 ;
      break ;
    case 92:
      b = 1 ;
      break ;
  }
  lcd.write(b) ;
}

*/
