/*
Use arduino pro mini 3v 8mhz

Remove power LED and voltage regulator to save energy:
https://www.iot-experiments.com/arduino-pro-mini-power-consumption/

this way it will be working for months in sleep mode and waiting until you press 
BTN_LEFT or BTN_RIGHT.
*/
#include "LowPower.h"

#define BTN_LEFT 2 // button you press to enable blinling left turn
#define BTN_RIGHT 3 // button you press to enable blinling right turn
#define LED_LEFT 5 // MOSFET which controls left turn LED lamps
#define LED_RIGHT 6 // MOSFET which controls left turn LED lamps

volatile unsigned long lastBtnPress = 0;
byte state = 0;
/*
 * 0 - not blinking
 * 1 - blinking after pressed left
 * 2 - blinking after pressed right
*/


void setup() {
  Serial.begin(9600);
  
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  
  // sleep
  state = 0;
  goSleep();
}

unsigned long lastBtnPressOnLoopStart = 0;

void loop() {
  Serial.println("CHECK BUTTONS PRESSED");
  
  lastBtnPressOnLoopStart = lastBtnPress;
  if (isBtnPressed(BTN_LEFT)) {
    if (state == 1) { // now blinking after pressed left
      // stop left blinking and go sleep
      state = 0;
      goSleep();
    } else if (state == 2) { // now blinking after pressed right
      // stop blinking right and start left
      state = 1;
      blinkTurn(LED_LEFT);
    } else { // now 0 - start blinking left
      state = 1;
      blinkTurn(LED_LEFT);
    }
    
  } else if (isBtnPressed(BTN_RIGHT)) {
    if (state == 2) { // now blinking after pressed right
      // stop right blinking and go sleep
      state = 0;
      goSleep();
    } else if (state == 1) { // now blinking after pressed left
      // stop blinking left and start right
      state = 2;
      blinkTurn(LED_RIGHT);
    } else { // now 0 - start blinking right
      state = 2;
      blinkTurn(LED_RIGHT);
    }
  }
}


void goSleep() {
  Serial.println("GOING TO SLEEP");Serial.flush();

  // remove interruptions to make sure buttons bouces will not wake up
  // the microcontroller on moment when you remove finger from pressed button
  detachInterrupt(digitalPinToInterrupt(BTN_LEFT));
  detachInterrupt(digitalPinToInterrupt(BTN_RIGHT));
  LowPower.powerDown(SLEEP_250MS, ADC_OFF, BOD_OFF);

  // ok, now let's enable interruptions and go to sleep
  attachInterrupt(digitalPinToInterrupt(BTN_LEFT), isrHandler, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RIGHT), isrHandler, FALLING);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    
  Serial.println("AWAKE");Serial.flush();
}

bool isBtnPressed(byte btnPin) {
  if (digitalRead(btnPin) == LOW) {
    delay(5);
    if (digitalRead(btnPin) == LOW) {
      return true;
    }
  }
  return false;
}

void isrHandler() {
  if (millis() - lastBtnPress > 300)
  {
    lastBtnPress = millis();
  }
}

void blinkTurn(byte pin) {  
  bool finished;
  while (true) {
    finished = ledOn(pin);
    if (!finished) {
      break;
    } else {
      delay(120);
      finished = ledOff(pin);
      if (!finished) {
        break;
      }
      delay(100);
    }
  }
}

// returns: true - finished, false - interrupted
bool ledOn(byte pwmPin) {
  for (int i = 0; i <= 255; i += 2) {
    if (btnPressedAgain()) {
      analogWrite(pwmPin, 0);
      return false;
    }
    analogWrite(pwmPin, (i > 255 ? 255: i));
    delay(1);
  }
  analogWrite(pwmPin, 255);
  return true;
}

// returns: true - finished, false - interrupted
bool ledOff(byte pwmPin) {
  for (int i = 255; i >= 0; i -= 2) {
    if (btnPressedAgain()) {
      analogWrite(pwmPin, 0);
      return false;
    }
    analogWrite(pwmPin, (i < 0 ? 0: i)); 
    delay(1);
  }
  analogWrite(pwmPin, 0);
  return true;
}

bool btnPressedAgain() {
  if (lastBtnPress != lastBtnPressOnLoopStart
    && (isBtnPressed(BTN_LEFT) || isBtnPressed(BTN_RIGHT))  
  ) {
    return true;
  }
  return false;
}
