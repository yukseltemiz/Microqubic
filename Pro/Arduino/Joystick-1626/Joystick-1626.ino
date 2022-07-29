// Attiny1626
// megatinycore 2.3.2 tested

#define firmware "v9.1-07.2022"

#include <EEPROM.h>

#define LED_CR PIN_PA4
#define switch_CR PIN_PA5
#define switch_XY PIN_PA6
#define pot3 PIN_PA7
#define pot1 PIN_PB5
#define pot2 PIN_PB4
#define LED_XY PIN_PB0
#define LED_AT PIN_PC0
#define switch_AT PIN_PC1
#define haptic PIN_PA3

#define hapticAmp 200
#define serialMax 64

// EEPROM addresses

#define address_sensitivity 0
#define address_directionA 10
#define address_directionB 20
#define address_directionC 30
#define address_directionX 40
#define address_directionY 50
#define address_directionZ 60
#define address_directionR 70


// TIMING
unsigned long lastMillis = 0;
unsigned long nowMillis;

// TOUCH SWITCHES
boolean doublePressed = false;
boolean switchPressed_XY = true;
boolean switchPressed_AT = false;
boolean switchPressed_CR = false;
int state = 1;

// JOYSTICK POT VALUES
int firstPot1value = 0;
int firstPot2value = 0;
int firstPot3value = 0;
int lastPot1value = 0;
int lastPot2value = 0;
int lastPot3value = 0;
int pot1value = 0;
int pot2value = 0;
int pot3value = 0;

// RESULTANT SPEED
int speed1 = 0;
int speed2 = 0;
int speed3 = 0;
int lastSpeed1 = 0;
int lastSpeed2 = 0;
int lastSpeed3 = 0;

// SERIAL COMMUNICATION
char receivedString[serialMax] = "";
char receivedChar;
byte serialCount;
boolean correctFormat = false;

// CONFIGURATION
boolean configMode = false;
boolean ledToggle = false;
boolean configPrint;
int directionA = 1;
int directionB = 1;
int directionC = 1;
int directionX = 1;
int directionY = 1;
int directionZ = 1;
int directionR = 1;


void setup() {

  configRead();
  delay(100);

  ADCPowerOptions(0x0B);

  Serial.begin(57600);
  pinMode (LED_CR, OUTPUT);
  pinMode (switch_CR, INPUT);
  pinMode (switch_XY, INPUT_PULLUP);
  pinMode (pot3, INPUT);
  pinMode (pot2, INPUT);
  pinMode (pot1, INPUT);
  pinMode (LED_XY, OUTPUT);
  pinMode (LED_AT, OUTPUT);
  pinMode (switch_AT, INPUT);
  pinMode (haptic, OUTPUT);

  digitalWrite(LED_XY, HIGH);
  analogWrite(haptic, 255);

  firstPot1value = analogReadEnh(pot1, 10, 0);
  firstPot2value = analogReadEnh(pot2, 10, 0);
  firstPot3value = analogReadEnh(pot3, 10, 0);

}

void loop() {

  checkValue();

  if (!configMode) {

    if (doublePressed == false && digitalReadFast(switch_XY) == LOW && switchPressed_XY == false) {
      while (digitalReadFast(switch_XY) == LOW) {
        analogWrite(haptic, (255 - hapticAmp));
        if (millis() - lastMillis > 500) {
          break;
        }
      }
      analogWrite(haptic, 255);
      state = 1; //XY
    }

    if (doublePressed == false && digitalReadFast(switch_CR) == HIGH && switchPressed_CR == false ) {
      lastMillis = millis();
      while (digitalReadFast(switch_CR) == HIGH ) {
        analogWrite(haptic, (255 - hapticAmp));
        if ((millis() - lastMillis > 500) || digitalReadFast(switch_AT) == HIGH) {
          break;
        }
      }
      analogWrite(haptic, 255);
      if (digitalReadFast(switch_AT) == LOW) {
        state = 2;
      }
    }

    if (doublePressed == false && digitalReadFast(switch_AT) == HIGH && switchPressed_AT == false) {
      while (digitalReadFast(switch_AT) == HIGH) {
        analogWrite(haptic, (255 - hapticAmp));
        if (millis() - lastMillis > 500 || digitalReadFast(switch_CR) == HIGH ) {
          break;
        }
      }
      analogWrite(haptic, 255);
      if (digitalReadFast(switch_CR) == LOW) {
        state = 3;
      }
    }

  }

  if (state == 1 && switchPressed_XY == false) {
    digitalWriteFast(LED_XY, HIGH);
    digitalWriteFast(LED_AT, LOW);
    digitalWriteFast(LED_CR, LOW);
    switchPressed_XY = true;
    switchPressed_AT = false;
    switchPressed_CR = false;
    Serial.println("$X1,0");
    Serial.println("$Y1,0");
    Serial.println("$Z1,0");

  }

  if (state == 2 && switchPressed_CR == false) {
    digitalWriteFast(LED_XY, LOW);
    digitalWriteFast(LED_AT, LOW);
    digitalWriteFast(LED_CR, HIGH);
    switchPressed_XY = false;
    switchPressed_AT = false;
    switchPressed_CR = true;
    Serial.println("$C1,0");
    Serial.println("$R1,0");
    Serial.println("$Z1,0");
  }


  if (state == 3 && switchPressed_AT == false) {
    digitalWriteFast(LED_XY, LOW);
    digitalWriteFast(LED_AT, HIGH);
    digitalWriteFast(LED_CR, LOW);
    switchPressed_XY = false;
    switchPressed_AT = true;
    switchPressed_CR = false;
    Serial.println("$A1,0");
    Serial.println("$B1,0");
    Serial.println("$Z1,0");
  }


  if (doublePressed == false && digitalReadFast(switch_CR) == HIGH && digitalReadFast(switch_AT) == HIGH) {
    doublePressed = true;
    digitalWriteFast(LED_XY, HIGH);
    digitalWriteFast(LED_AT, LOW);
    digitalWriteFast(LED_CR, LOW);
    lastMillis = millis();
    analogWrite(haptic, (255 - hapticAmp));
    while (millis() - lastMillis < 1000) {
      if (digitalReadFast(switch_CR) == LOW || digitalReadFast(switch_AT) == LOW) {
        switchPressed_XY = false;
        switchPressed_CR = false;
        switchPressed_AT = false;
        break;
      }
    }
    analogWrite(haptic, 255);

    if (digitalReadFast(switch_CR) == HIGH && digitalReadFast(switch_AT) == HIGH) {
      configControl();
    }
  }

  if (doublePressed == true && digitalReadFast(switch_AT) == LOW && digitalReadFast(switch_CR) == LOW) {
    doublePressed = false;
  }


  if (configMode) {

    nowMillis = millis();
    if (nowMillis - lastMillis >= 100) {
      ledToggle = !ledToggle;
      digitalWrite(LED_XY, ledToggle);
      lastMillis = nowMillis;
    }

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
