/*
Use arduino pro mini 3v 8mhz

Remove power LED and voltage regulator to save energy:
https://www.iot-experiments.com/arduino-pro-mini-power-consumption/

this way it will be working for months in sleep mode and waiting until you press 
BTN_LEFT or BTN_RIGHT.
*/
#include <GyverPower.h>

#define BTN_LEFT 2 // button you press to enable blinling left turn
#define BTN_RIGHT 3 // button you press to enable blinling right turn
#define LED_LEFT 5 // MOSFET which controls left turn LED lamps
#define LED_RIGHT 6 // MOSFET which controls left turn LED lamps

volatile bool awake = false;
volatile unsigned long lastBtnPress = 0;
byte state = 0;
/*
 * 0 - not blinking
 * 1 - blinking after pressed left
 * 2 - blinking after pressed right
*/


void setup() {
  Serial.begin(9600);
  
  power.hardwareDisable(
    PWR_ADC 
//    | PWR_TIMER1 
//    | PWR_TIMER2 
    | PWR_I2C
    | PWR_SPI
  );
  
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTN_LEFT), isrLeft, FALLING); // FALLING
  attachInterrupt(digitalPinToInterrupt(BTN_RIGHT), isrRight, FALLING); // FALLING 
  
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  
  power.setSleepMode(POWERDOWN_SLEEP);
  
}

unsigned long lastBtnPressWhenStarted = 0;

void loop() {
  if (awake) {
    
    lastBtnPressWhenStarted = lastBtnPress;
    if (isBtnPressed(BTN_LEFT)) {
    
      if (state == 1) { // blinking after pressed left
        // stop left blinking
      } else if (state == 2) { // blinking after pressed right
        // stop blinking right and start left
        state = 1;
        blink(LED_LEFT);
      } else {
        // when 0 - start blinking left
        state = 1;
        blink(LED_LEFT);
      }
      
    } else if (isBtnPressed(BTN_RIGHT)) {
      
      if (state == 2) { // blinking after pressed right
        // stop right blinking
      } else if (state == 1) { // blinking after pressed left
        // stop blinking leftand start right
        state = 2;
        blink(LED_RIGHT);
      } else {
        // when 0 - start blinking right
        state = 2;
        blink(LED_RIGHT);
      }
      
    }

    if (lastBtnPressWhenStarted == lastBtnPress) {
      // sleep if no buttons were pressed during execution
      awake = false;
    }

  } else {
    state = 0;
    power.sleep(SLEEP_FOREVER);
  }
}

bool isBtnPressed(byte btnPin) {
  if (digitalRead(btnPin) == LOW) {
    delay(15);
    if (digitalRead(btnPin) == LOW) {
      return true;
    }
  }
  return false;
}

void isrLeft() { 
  if (millis() - lastBtnPress > 200)
  {
    lastBtnPress = millis();
    awake = true;
  }
}
void isrRight() {
  if (millis() - lastBtnPress > 200)
  {
    awake = true;
    lastBtnPress = millis();
  }
}


void blink(byte pin) {
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
  for (int i = 0; i <= 255; i += 1) {
    if (btnPressedAgain()) {
      analogWrite(pwmPin, 0);
      return false;
      break;
    }
    analogWrite(pwmPin, i);
    delay(1);
  }
  return true;
}
// returns: true - finished, false - interrupted
bool ledOff(byte pwmPin) {
  for (int i = 255; i >= 0; i -= 1) {
    if (btnPressedAgain()) {
      analogWrite(pwmPin, 0);
      return false;
      break;
    }
    analogWrite(pwmPin, i); 
    delay(1);
  }
  return true;
}




bool btnPressedAgain() {
  if (
    lastBtnPress != lastBtnPressWhenStarted
    && (isBtnPressed(BTN_LEFT) || isBtnPressed(BTN_RIGHT))  
  ) {
    return true;
  }
  return false;
}
