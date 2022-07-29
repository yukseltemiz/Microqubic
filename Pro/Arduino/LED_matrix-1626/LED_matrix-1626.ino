//Attiny 1626
// megatinycore 2.3.2 tested

#define firmware "v9.2-07.2022"

#include <EEPROM.h>

#define LEDpin PIN_PB1

#define col10 PIN_PB0
#define col9 PIN_PC0
#define col8 PIN_PC1
#define col7 PIN_PC2
#define col6 PIN_PC3
#define col5 PIN_PB4
#define col4 PIN_PB5
#define col3 PIN_PA7
#define col2 PIN_PA6
#define col1 PIN_PA5

#define OE PIN_PA4
#define CLK PIN_PA2
#define SDI PIN_PA3 // shared with touchswitch
#define LE PIN_PA1

#define serialMax 64

// EEPROM addresses

#define address_powerStatus 0
#define address_statusLEDintensity 10
#define address_PWMvalue 20
#define address_LEDstatus 30

//LED CONTROL

int PWMvalue = 100;
int LEDstatus = 1024;
boolean clockSignal = false;
boolean dataSent = false;
boolean switchState = false;
int powerStatus = 0;
int columnData = 0b1111111111111111;
int columnDataMapped;


// SERIAL COMMUNICATION
char receivedString[serialMax] = "";
char receivedChar;
byte serialCount;
boolean correctFormat = false;

// CONFIGURATION
int statusLEDintensity = 10;

// TOUCH SWITCHES
boolean switchPressed = true;

//TIMING
unsigned long lastMillis = 0;
unsigned long nowMillis = 0;

char function;


long targetStepNumber;
long serialTargetSpeed;



void setup() {

  configRead();

  Serial.begin(57600);
  pinMode (LEDpin, OUTPUT);
  pinMode (col10, OUTPUT);
  pinMode (col9, OUTPUT);
  pinMode (col8, OUTPUT);
  pinMode (col7, OUTPUT);
  pinMode (col6, OUTPUT);
  pinMode (col5, OUTPUT);
  pinMode (col4, OUTPUT);
  pinMode (col3, OUTPUT);
  pinMode (col2, OUTPUT);
  pinMode (col1, OUTPUT);

  pinMode (OE, OUTPUT);
  pinMode (CLK, OUTPUT);
  pinMode (SDI, INPUT);
  pinMode (LE, OUTPUT);

  digitalWrite(OE, HIGH);
  digitalWrite(LE, LOW);
 
  analogWrite(LEDpin, statusLEDintensity);

  for (int j = 0; j < 16; j++) {
    if (j < 8) {
      bitWrite(columnDataMapped, 7 - j, bitRead(columnData, j));
    }
    if (j >= 8) {
      bitWrite(columnDataMapped, j, bitRead(columnData, j));
    }
  }

  rowControl();
  delay(1);
  columnControl();

}

void loop() {


  if (switchPressed == true) {

    if (powerStatus) {
      analogWrite(OE, map(PWMvalue, 0, 100, 255, 0));
    }
    else {
      digitalWrite(OE, HIGH);
    }
    switchPressed = false;
  }

  if (switchPressed == false && digitalRead(SDI) == HIGH) {
    while (digitalRead(SDI) == HIGH) {}
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
