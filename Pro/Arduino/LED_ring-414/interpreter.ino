void interpreter(char instruction[], int instructionSize) {
  int LEDindex;
  int singleLEDstatus;
  byte k = 0; byte l = 0;
  char tempValue[8];
  char function;
  boolean searchParameters = false;
  boolean parametersFound = false;

  for (int i = 0; i < 8; i++) {
    tempValue[i] = 0;
  }


  if (instructionSize == 4) {
    if (instruction[1] == '*' && instruction[2] == '9') {
   powerDown();
    }
  }

  if (instruction[1] == 'c') {

    if (isDigit(instruction[2])) {
      function = instruction[2];

      if (function == '0') { // TURN OFF
        switchPressed = true;
        powerStatus = false;
      }

      if (function == '1') { // TURN ON
        switchPressed = true;
        powerStatus = true;
      }

      if (function == '2') { // ADJUST PWM (Overall)

        if (instruction[3] == ',' && isDigit(instruction[4])) {

          for (int i = 4; i < 12; i++) {
            if (instruction[i] == ' ' || instruction[i] == 0) {
              break;
            }
            tempValue[i - 4] = instruction[i];
          }
          if (atoi(tempValue) <= 100 && atoi(tempValue) >= 0) {
            PWMvalue = atoi(tempValue);
            switchPressed = true;
            if (PWMvalue == 0) {
              powerStatus = false;
            }
            else {
              powerStatus = true;
            }
          }
        }
      }

      if (function == '3') { //TURN ON/OFF individual column

        if (instruction[3] == ',' && isDigit(instruction[4])) {
          LEDindex = instruction[4] - '0';
          if (instruction[5] == ',' && isDigit(instruction[6]) ) {
            singleLEDstatus = instruction[6] - '0';
            if (singleLEDstatus == 0) {
              bitClear(LEDstatus, LEDindex-1);
              switchPressed = true;
              powerStatus = true;
            }
            if (singleLEDstatus == 1) {
              bitSet(LEDstatus, LEDindex-1);
              switchPressed = true;
              powerStatus = true;
            }
          }

        }
      }

      if (function == '4') { // RESET to full illumination
        LEDstatus = 255;
        switchPressed = true;
        powerStatus = true;
      }

      if (function == '5') { // RESET to zero illumination
        LEDstatus = 0;
        switchPressed = true;
        powerStatus = false;
      }

      if (function == '6') { // PRINT STATUS
        Serial.print("c:"); Serial.print(powerStatus);
        Serial.print(","); Serial.print(PWMvalue);
        Serial.print(","); Serial.println(LEDstatus);

      }

      if (function == '7') { // PRINT FIRMWARE
        Serial.println(firmware);
      }

    }

  }

}

void resetReceived() {
  for (byte i = 0; i < serialMax; i++) {
    receivedString[i] = 0;
    serialCount = 0;
  }
  correctFormat = false;
}
