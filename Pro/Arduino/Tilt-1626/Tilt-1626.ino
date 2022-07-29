// Attiny1626
// TMCstepper library 0.7.1 tested
// megatinycore 2.3.2 tested

#define firmware "v9.1-07.2022"
#define deviceType "Tilt"

#include <TMCStepper.h>
#include <EEPROM.h>
//#include <avr/sleep.h>

#define SW_TX PIN_PA4
#define motorEN PIN_PA5
#define sensorBoom PIN_PA6
#define sensorPower PIN_PA7
#define sensorArm PIN_PB5
#define sensorT PIN_PB4
#define LEDpin PIN_PB1
//#define NC PIN_PB0
#define switchArmLeft PIN_PC3
#define switchArmRight PIN_PC2
#define switchBoomLeft PIN_PC0
#define switchBoomRight PIN_PC1
#define motorDIAG PIN_PA1
#define motorVIO PIN_PA2
#define SW_RX PIN_PA3

#define DRIVER_ADDRESS 0b00
#define R_SENSE 0.33f
#define serialMax 64
#define measureAvg 10

// EEPROM addresses

#define address_statusLEDintensity 10
#define address_smoothStop 40
#define address_sensor_0degA 50
#define address_sensor_neg90degA 60
#define address_sensor_pos90degA 70
#define address_sensor_0degB 80
#define address_sensor_neg90degB 90
#define address_sensor_pos90degB 100

TMC2209Stepper driver(SW_RX, SW_TX, R_SENSE, DRIVER_ADDRESS);

boolean startMeasurement = false;

// MOTORS

long targetPositionSingle[2];
long targetSpeedSingle[2] = {0, 0};
long serialTargetSpeed[2] = {0, 0};
long targetSpeed = 0;
long lastTargetSpeedSingle[2] = {0, 0};
boolean checkStall = true;
//int lastDirection[2] = {0, 0};
boolean serialAngle[2] = {false, false};
int smoothStop = 1;

// TOUCH SWITCHES
float touchMotorSpeed[2] = {50, 50}; //touch switch speed
boolean switchPressed[2] = {false, false};
boolean doublePressed = false;

// TIMING
unsigned long lastMillis = 0;
unsigned long nowMillis;
unsigned long lastMillis2 = 0;
unsigned long nowMillis2;

// SERIAL COMMUNICATION
char receivedString[serialMax] = "";
char receivedChar;
byte serialCount;
boolean correctFormat = false;

// CONFIGURATION
boolean configMode = false;
boolean ledToggle = false;
boolean configPrint;
int statusLEDintensity = 1;

// SENSORS

float targetAngle[2];
float currentAngle[2] = {0, 0};
boolean sensorDebug = false;
long sensorValue[2] = {0, 0};
long sensorValueB = 0;
long lastSensorValue[2] = {0, 0};
long targetSensorValue[2] = {0, 0};
long sensor_0deg[2] = {0, 0};
long sensor_neg90deg[2] = {0, 0};
long sensor_pos90deg[2] = {0, 0};


//int directionArm = 1;
//int directionBoom = 1;

void setup() {

  configRead();
  delay(100);

  ADCPowerOptions(0x0B);

  Serial.begin(57600);


  pinMode (LEDpin, OUTPUT);
  pinMode (sensorPower, OUTPUT);
  pinMode (sensorArm, INPUT);
  pinMode (sensorBoom, INPUT);
  pinMode (sensorT, INPUT);
  pinMode (motorEN, OUTPUT);
  pinMode (motorVIO, OUTPUT);
  pinMode (motorDIAG, INPUT);
  pinMode (switchArmLeft, INPUT);
  pinMode (switchArmRight, INPUT);
  pinMode (switchBoomLeft, INPUT);
  pinMode (switchBoomRight, INPUT);

  digitalWrite (motorEN, LOW);
  digitalWrite (motorVIO, HIGH);
  digitalWrite (sensorPower, HIGH);

  driver.beginSerial(57600);     // SW UART drivers
  driver.en_spreadCycle(false);
  driver.pwm_autoscale(false);
  driver.shaft(false);
  driver.index_otpw(false);
  driver.pdn_disable(false);
  driver.mstep_reg_select(false);
  driver.multistep_filt(false);
  driver.irun(31);
  driver.ihold(15);
  driver.pwm_freq(0);
  driver.I_scale_analog(true);

  driver.toff(1);

  analogWrite(LEDpin, map(statusLEDintensity, 1, 100, 250, 0));

}

void loop() {

  motorMove();

  if (sensorDebug) {
    nowMillis = millis();
    if (nowMillis - lastMillis >= 100) {
      sensorValue[0] = measureSensor(0);
      sensorValue[1] = measureSensor(1);
      Serial.print(sensorValue[0]);
      Serial.print(",");
      Serial.println(sensorValue[1]);
      lastMillis = nowMillis;
    }
  }

  /// ARM

  if (doublePressed == false  && digitalReadFast(switchArmLeft) == HIGH) { //&& stallState <= 0
    switchPressed[0] = true;

    targetSpeedSingle[0] = (touchMotorSpeed[0]);

    if (touchMotorSpeed[0] < 250) {
      touchMotorSpeed[0] = touchMotorSpeed[0] + 5;
    }
    delay(50);
  }

  if (doublePressed == false  && digitalReadFast(switchArmRight) == HIGH) { //&& stallState <= 0
    switchPressed[0] = true;

      targetSpeedSingle[0] = (touchMotorSpeed[0]) * -1;
    
    if (touchMotorSpeed[0] < 250) {
      touchMotorSpeed[0] = touchMotorSpeed[0] + 5;
    }
    delay(50);
  }

  if (switchPressed[0] == true && digitalReadFast(switchArmLeft) == LOW && digitalReadFast(switchArmRight) == LOW) {
    switchPressed[0] = false;
    doublePressed = false;
    targetSpeedSingle[0] = 0;
    touchMotorSpeed[0] = 50;
  }

  /// BOOM

  if (digitalReadFast(switchBoomLeft) == HIGH) { //&& stallState <= 0
    switchPressed[1] = true;

      targetSpeedSingle[1] = (touchMotorSpeed[1]);
    
    if (touchMotorSpeed[1] < 250) {
      touchMotorSpeed[1] = touchMotorSpeed[1] + 5;
    }
    delay(50);
  }

  if (digitalReadFast(switchBoomRight) == HIGH) { //&& stallState <= 0
    switchPressed[1] = true;

      targetSpeedSingle[1] = (touchMotorSpeed[1]) * -1;
    
    if (touchMotorSpeed[1] < 250) {
      touchMotorSpeed[1] = touchMotorSpeed[1] + 5;
    }
    delay(50);
  }

  if (switchPressed[0] == true && digitalReadFast(switchArmLeft) == LOW && digitalReadFast(switchArmRight) == LOW) {
    switchPressed[0] = false;
    doublePressed = false;
    targetSpeedSingle[0] = 0;
    touchMotorSpeed[0] = 50;
  }

  if (switchPressed[1] == true && digitalReadFast(switchBoomLeft) == LOW && digitalReadFast(switchBoomRight) == LOW) {
    switchPressed[1] = false;
    targetSpeedSingle[1] = 0;
    touchMotorSpeed[1] = 50;
  }

  /// CONFIG

  if (doublePressed == false && digitalReadFast(switchArmLeft) == HIGH && digitalReadFast(switchArmRight) == HIGH) {

    doublePressed = true;
    targetSpeed = 0;
    driver.VACTUAL(0);
    digitalWrite(LEDpin, HIGH);
    lastMillis = millis();
    while (millis() - lastMillis < 2000) {
      if (digitalReadFast(switchArmLeft) == LOW || digitalReadFast(switchArmRight) == LOW) {
        analogWrite(LEDpin, map(statusLEDintensity, 1, 100, 250, 0));
        break;
      }
    }

    if (digitalReadFast(switchArmLeft) == HIGH && digitalReadFast(switchArmRight) == HIGH) {
      configControl();
    }
  }

  if (configMode) {

    if (sensorDebug == false) {
      nowMillis = millis();
      if (nowMillis - lastMillis >= 100) {
        ledToggle = !ledToggle;
        digitalWrite(LEDpin, ledToggle);
        lastMillis = nowMillis;
      }
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
