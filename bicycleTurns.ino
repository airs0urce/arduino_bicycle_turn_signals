/*
Use arduino pro mini 3v 8mhz

Remove power LED and voltage regulator to save energy:
https://www.iot-experiments.com/arduino-pro-mini-power-consumption/
This way it will be working for months in sleep mode and waiting until you press left or right button.
*/
#include "LowPower.h"
#include "MsTimer2.h"

#define BTN_LEFT 2 // button you press to enable blinling left turn
#define BTN_RIGHT 3 // button you press to enable blinling right turn

#define LED_LEFT 5 // MOSFET which controls left turn LED lamps
#define LED_RIGHT 6 // MOSFET which controls left turn LED lamps

#define SKIP_TICKS_UPPER 100 // how long to keep LED in "fully on" state while blinking
#define SKIP_TICKS_LOWER 100 // how long to keep LED in "fully off" state while blinking

#define SLEEP_INACTIVITY_MS 2000 // send arduino to sleep when LEDs are not blinking after N ms

volatile byte state = 0;
/*
 * state values:
 * 0 - not blinking
 * 1 - blinking after pressed left
 * 2 - blinking after pressed right
*/

void bothLedsOff() {
  analogWrite(LED_LEFT, 0);
  analogWrite(LED_RIGHT, 0);
}

unsigned int skipTicksUpper = SKIP_TICKS_UPPER;
unsigned int skipTicksLower = SKIP_TICKS_LOWER;

void ledsBlinkingHandler() {
  static byte ledPwmValue = 0;
  static bool ledPwmIncreasing = true;
  static byte prevState = 0;

  if (prevState != state) {
    ledPwmValue = 0;
    ledPwmIncreasing = true;
    skipTicksUpper = SKIP_TICKS_UPPER;
    skipTicksLower = SKIP_TICKS_LOWER;
    bothLedsOff();
  }
      
  switch (state) {
    case 1:
    case 2:
      if (ledPwmValue == 255 && skipTicksUpper > 0) {
        skipTicksUpper--;
        return;
      }
      if (!ledPwmIncreasing && ledPwmValue == 0 && skipTicksLower > 0) {
        skipTicksLower--;
        return;
      }
      skipTicksUpper = SKIP_TICKS_UPPER;
      skipTicksLower = SKIP_TICKS_LOWER;
      
      if (ledPwmIncreasing) {
        if (ledPwmValue < 255) {
          ledPwmValue += 1;
        } else {
          ledPwmIncreasing = false;  
        }
      } else {
        if (ledPwmValue > 0) {
          ledPwmValue -= 1;
        } else {
          ledPwmIncreasing = true;
        }
      }
      if (state == 1) {
        analogWrite(LED_LEFT, ledPwmValue);
      } else {
        analogWrite(LED_RIGHT, ledPwmValue);
      }
      
      break;
  } 
  prevState = state;
}

void setup() {
  Serial.begin(9600);
  
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_LEFT), isrBtnLeftChangeHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN_RIGHT), isrBtnRightChangeHandler, CHANGE);
  // sleep state
  state = 0;

  MsTimer2::set(1, ledsBlinkingHandler);
  MsTimer2::start();
}

void loop() {  
  handleInactivitySleep();  
}

unsigned long stateZeroFromMillis = 0;
void handleInactivitySleep() {
  // make sure we sleep in case of SLEEP_INACTIVITY_MS of inactivity
  if (state == 0) {
    if (stateZeroFromMillis == 0) {
      stateZeroFromMillis = millis();
    }
  } else {
    stateZeroFromMillis = 0;
  }
  if (stateZeroFromMillis != 0 && millis() - stateZeroFromMillis >= SLEEP_INACTIVITY_MS) {
    stateZeroFromMillis = 0;
    goSleep();
  }
}

void handleBtnLeftPress() {
    if (state == 1) { 
      // now: blinking after pressed left
      // we will: stop left blinking and go sleep
      state = 0;
      ledsBlinkingHandler();
    } else if (state == 2) { 
      // now: blinking after pressed right
      // we will: stop blinking right and start left
      state = 1;
    } else { 
      // now: turn lights disabled
      // we will: start blinking left
      state = 1;
    }
}

void handleBtnRightPress() {
  if (state == 2) { 
    // now: blinking after pressed right
    // we will: stop right blinking and go sleep
    state = 0;
    ledsBlinkingHandler();
  } else if (state == 1) { 
    // now: blinking after pressed left
    // we will: stop blinking left and start right
    state = 2;
  } else { 
    // now: turn lights disabled
    // we will: start blinking right
    state = 2;
  }
}


void goSleep() {
  //Serial.println("GOING TO SLEEP");Serial.flush();
  
  MsTimer2::stop();
  bothLedsOff();
  state = 0;
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  MsTimer2::start();
    
  //Serial.println("AWAKE");Serial.flush();
}


void isrBtnLeftChangeHandler() {
  static unsigned long lastPress = 0;
  if (millis() - lastPress < 350) {
    lastPress = millis();
    return;
  }
  lastPress = millis();

  if (digitalRead(BTN_LEFT) == LOW) {
  //Serial.println("Interrupt LEFT PRESS HANDLED");Serial.flush();
    handleBtnLeftPress();
  }
}
void isrBtnRightChangeHandler() {
  static unsigned long lastPress = 0;
  if (millis() - lastPress < 350) {
    lastPress = millis();
    return;
  }
  lastPress = millis();

  if (digitalRead(BTN_RIGHT) == LOW) {
  //Serial.println("Interrupt RIGHT PRESS HANDLED");Serial.flush();
    handleBtnRightPress();
  }
}
