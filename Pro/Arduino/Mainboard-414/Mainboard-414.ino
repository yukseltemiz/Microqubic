//Attiny 402
// megatinycore 2.3.2 tested

#define firmware "v8.1-02.2022"

#include <avr/sleep.h>
#include <EEPROM.h>

#define LEDpin PIN_PA1
#define touchSwitch PIN_PA2
#define powerEN PIN_PA3

#define serialMax 64

char receivedString[serialMax] = "";
char receivedChar;
byte serialCount;
boolean correctFormat = false;

boolean switchPressed = false;
boolean LEDstatus = false;

unsigned long lastMillis = 0;
unsigned long nowMillis = 0;
unsigned long lastMillis2 = 0;
unsigned long nowMillis2 = 0;
unsigned long sleepTimer = 0;

int statusLEDintensity = 100;
boolean configMode = false;

boolean powerState = 1;

void setup() {

  Serial.begin(57600);
  pinMode (LEDpin, OUTPUT);
  pinMode (powerEN, OUTPUT);
  pinMode (touchSwitch, INPUT);

  digitalWriteFast (powerEN, HIGH); // can be off, TBD
  analogWrite(LEDpin, 255);

}

void loop() {

  if (digitalReadFast(touchSwitch) == HIGH) {

    if (powerState == HIGH) {
      for (int i = 255; i >= 10; i--) {
        analogWrite(LEDpin, i);
        delay(2);
      }
      digitalWriteFast (powerEN, LOW);
      powerState = LOW;
    }

    else {
      for (int j = 10; j <= 255; j++) {
        analogWrite(LEDpin, j);
        delay(2);

      }
      digitalWriteFast (powerEN, HIGH);
      powerState = HIGH;
      
    }

    while (digitalReadFast(touchSwitch) == HIGH) {}
  }




  if (Serial.available() > 0) {

    lastMillis2 = 0;

    if (receivedChar == '*') {
      correctFormat = true;
    }

    if (correctFormat) {

      if (receivedChar != '\n') {
        receivedString[serialCount] = receivedChar;
        serialCount++;
      }

      if (serialCount > 1 && (receivedChar == '\n')) {
        interpreter(receivedString, serialCount);
        resetReceived();
      }
    }
  }
}
