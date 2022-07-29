//Attiny 414
// megatinycore 2.3.2 tested

#define firmware "v9.1-07.2022"

#include <tinyNeoPixel_Static.h>
#include <EEPROM.h>

#define touchSwitch PIN_PB0
#define LEDpin PIN_PB1
#define neopixelpin PIN_PA4
#define NUMPIXELS 8

byte pixels[NUMPIXELS * 3];

tinyNeoPixel leds = tinyNeoPixel(NUMPIXELS, neopixelpin, NEO_GRB, pixels);

#define serialMax 16

// EEPROM addresses

#define address_powerStatus 0
#define address_PWMvalue 20
#define address_LEDstatus 30


// TOUCH SWITCHES
boolean switchPressed = true;


//LED control
int PWMvalue = 10;
byte LEDstatus = 255;
int LEDPWMmapped;
int powerStatus = 0;

// SERIAL COMMUNICATION

char receivedString[serialMax] = "";
char receivedChar;
byte serialCount;
boolean correctFormat = false;

// CONFIGURATION
int statusLEDintensity = 10;

void setup() {
  configRead();
  Serial.begin(57600);
  pinMode(LEDpin, OUTPUT);
  pinMode(neopixelpin, OUTPUT);
  pinMode(touchSwitch, INPUT);
  analogWrite(LEDpin, statusLEDintensity);
  leds.clear();
}

void loop() {

  if (switchPressed == true) {

    if (powerStatus) {
      leds.clear();
      LEDPWMmapped = map(PWMvalue, 0, 100, 0, 255);

      for (int i = 0; i < 8; i++) {
        if (bitRead(LEDstatus, i) == 1) {
          leds.setPixelColor(i, leds.Color(LEDPWMmapped, LEDPWMmapped , LEDPWMmapped));
        }
        leds.show();
        delay(1);
      }
    }
    else {
      leds.clear();
      leds.show();
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
