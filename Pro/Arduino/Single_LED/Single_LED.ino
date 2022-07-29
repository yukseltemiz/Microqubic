//Attiny 402
// megatinycore 2.3.2 tested

#define firmware "v9.1-07.2022"

#include <EEPROM.h>

#define LEDpin PIN_PA2
#define touchSwitch PIN_PA1
#define PWMpin PIN_PA3

#define serialMax 16

// EEPROM addresses

#define address_powerStatus 0 
#define address_PWMvalue 20 

//LED control
int PWMvalue = 100;
int powerStatus = 0;
int LEDPWMmapped;

// SERIAL COMMUNICATION
char receivedString[serialMax] = "";
char receivedChar;
byte serialCount;
boolean correctFormat = false;

// CONFIGURATION
int statusLEDintensity = 10;

// TOUCH SWITCHES
boolean switchPressed = true;

void setup() {

  configRead();
  Serial.begin(57600);
  pinMode (PWMpin, OUTPUT);
  pinMode (LEDpin, OUTPUT);
  pinMode (touchSwitch, INPUT);
  analogWrite(LEDpin, statusLEDintensity);
}

void loop() {


  if (switchPressed == true) {

    if (powerStatus) {
      LEDPWMmapped = map(PWMvalue, 0, 100, 0, 255);
      analogWrite(PWMpin, LEDPWMmapped);
    }
    else {
      analogWrite(PWMpin, 0);
    }
    switchPressed = false;
  }

  if (switchPressed == false && digitalReadFast(touchSwitch) == HIGH) {
    while (digitalReadFast(touchSwitch) == HIGH) {}
    switchPressed = true;
    powerStatus = !powerStatus;
  }


  if (Serial.available() > 0) {

    receivedChar = Serial.read();

    if (receivedChar == '$') {
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
