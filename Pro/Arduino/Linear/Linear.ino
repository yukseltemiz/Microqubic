// Attiny1626
// TMCstepper library 0.7.1 tested, now 0.7.3
// megatinycore 2.3.2 tested

//new:
//touchswitches: longer pressed, faster goes
//status led intensity controlled by commands

#define firmware "v9.1-07.2022"
#define maxStagePosition 70000 //in micrometer
#define deviceType "L70"
#define speedCoefficient 100 //100 * microStepValue;
#define maxTargetSpeed 1500.0 // 15mm/s
#define backlashSpeed 500 // in terms of native motor speed

#include <TMCStepper.h>
#include <EEPROM.h>
//#include <avr/sleep.h>

#define sensorPowerL PIN_PA4
#define sensorL PIN_PA5
#define sensorPowerR PIN_PA6
#define sensorR PIN_PA7
#define sensorT PIN_PB4
#define LEDpin PIN_PB1 //inverted
#define motorDIAG PIN_PB0
#define motorVIO PIN_PC0
#define SW_RX PIN_PC1
#define SW_TX PIN_PC2
#define motorEN PIN_PC3
#define switchL PIN_PA3
#define switchR PIN_PA2
#define stageType PIN_PB5

#define DRIVER_ADDRESS 0b00
#define R_SENSE 0.33f
#define serialMax 64
#define microStepValue 0
#define measureAvg 10

// EEPROM addresses

#define address_deviceID 0
#define address_statusLEDintensity 10
#define address_touchSwitchControl 20
#define address_backlashValue 30
#define address_smoothStop 35
#define address_distance_per_step 40
#define address_stepNumber 50
#define address_lastDirection 60
#define address_homingState 70
#define address_sensorThresholdL 80
#define address_sensorThresholdR 90

TMC2209Stepper driver(SW_RX, SW_TX, R_SENSE, DRIVER_ADDRESS);

// MOTOR

long stepNumber = 0;
byte tempStepIncrement = 0;
long lastStepNumber = 0;
long lastStepNumber2 = 0;
float distance_per_step;
int backlashValue;
int lastDirection = 0;
int stallState = 0;
long targetStepNumber;
long serialTargetSpeed;
long targetSpeed;
long lastTargetSpeed = 0;
float currentStagePosition = 0;
int smoothStop = 1;

boolean checkStall = true;
boolean backlash = false;
boolean serialMove = false;

// TOUCH SWITCHES
float touchMotorSpeed = 0;
boolean doublePressed = false;
boolean switchPressed = false;

// TIMING
unsigned long lastMillis = 0;
unsigned long nowMillis;

// SERIAL COMMUNICATION

char receivedString[serialMax] = "";
char receivedChar;
byte serialCount;
boolean correctFormat = false;

// CONFIGURATION
char deviceID;
boolean configMode = false;
boolean ledToggle = false;
boolean configPrint;
int statusLEDintensity = 1;
int homingState = 0;

// SENSORS

boolean sensorDebug = false;
long sensorValue = 0;
long lastSensorValue = 0;
long sensorThresholdL = 0;
long sensorThresholdR = 0;
long sensorValueT = 0;

void setup() {

  configRead();
  EEPROM.get(address_homingState, homingState);

  delay(100);

  ADCPowerOptions(0x0B);

  Serial.begin(57600);
  pinMode (LEDpin, OUTPUT);
  pinMode (sensorPowerL, OUTPUT);
  pinMode (sensorPowerR, OUTPUT);
  pinMode (switchL, INPUT);
  pinMode (switchR, INPUT);
  pinMode (sensorL, INPUT);
  pinMode (sensorR, INPUT);
  pinMode (sensorT, INPUT);
  pinMode (motorEN, OUTPUT);
  pinMode (motorVIO, OUTPUT);
  pinMode (motorDIAG, INPUT);
  digitalWriteFast (motorEN, LOW);
  digitalWriteFast (motorVIO, HIGH);
  digitalWriteFast (sensorPowerL, LOW);
  digitalWriteFast (sensorPowerR, LOW);

  driver.beginSerial(57600);     // SW UART drivers
  driver.I_scale_analog(false); //TMC2300, default 0
  driver.microsteps(microStepValue);
  driver.pwm_freq(0);
  driver.pwm_autoscale(true);     // Needed for stealthChop
  driver.irun(31);
  driver.index_step(true); //diag step output enabled

  attachInterrupt(motorDIAG, stepCount, CHANGE);

  EEPROM.put(address_homingState, 0);

  analogWrite(LEDpin, map(statusLEDintensity, 1, 100, 250, 0));

}


void loop() {

  motorMove();

  if (sensorDebug) {

    nowMillis = millis();
    if (nowMillis - lastMillis >= 100) {
      Serial.print(measureSensorL());
      Serial.print(",");
      Serial.println(measureSensorR());
      ledToggle = !ledToggle;
      digitalWrite(LEDpin, ledToggle);
      lastMillis = nowMillis;
    }
  }

  if (backlash == false) {

    if (doublePressed == false && stallState >= 0 && digitalReadFast(switchL) == HIGH) {
      switchPressed = true;
      targetSpeed = (touchMotorSpeed) * -1  * speedCoefficient;
      if (touchMotorSpeed < 15) {
        touchMotorSpeed = touchMotorSpeed + 0.5;
      }
      delay(50);
    }

    if (doublePressed == false && stallState <= 0 && digitalReadFast(switchR) == HIGH) {
      switchPressed = true;
      targetSpeed = (touchMotorSpeed)  * speedCoefficient;
      if (touchMotorSpeed < 15) {
        touchMotorSpeed = touchMotorSpeed + 0.5;
      }
      delay(50);
    }

    if (switchPressed == true && digitalReadFast(switchL) == LOW && digitalReadFast(switchR) == LOW) {
      switchPressed = false;
      doublePressed = false;
      targetSpeed = 0;
      touchMotorSpeed = 0;
    }

    if (doublePressed == false && digitalReadFast(switchR) == HIGH && digitalReadFast(switchL) == HIGH) {

      doublePressed = true;
      targetSpeed = 0;
      driver.VACTUAL(0);
      digitalWrite(LEDpin, HIGH);
      lastMillis = millis();
      while (millis() - lastMillis < 1500) {
        if (digitalReadFast(switchR) == LOW || digitalReadFast(switchL) == LOW) {
          analogWrite(LEDpin, map(statusLEDintensity, 1, 100, 250, 0));
          break;
        }
      }

      if (digitalReadFast(switchR) == HIGH && digitalReadFast(switchL) == HIGH) {
        configControl();
      }
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
