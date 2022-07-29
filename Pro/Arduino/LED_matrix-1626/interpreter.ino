void interpreter(char instruction[], int instructionSize) {
  int k = 0;
  int columnValue;
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


  if (instruction[1] == 'a') {

    if (isDigit(instruction[2])) {
      function = instruction[2];

      if (function == '0') {
        switchPressed = true;
        powerStatus = false;
      }
      if (function == '1') {
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
          for (int i = 4; i < 12; i++) {
            if (instruction[i] == ',') {
              break;
            }
            tempValue[i - 4] = instruction[i];
            k = i;
          }
          if (instruction[k + 1] == ',' && isDigit(instruction[k + 2]) ) {
            columnValue = instruction[k + 2] - '0';
          }

           if (atoi(tempValue) >= 0 && atoi(tempValue) <= 10) {

            if (columnValue == 0) {
              bitClear(LEDstatus, atoi(tempValue) - 1);
              columnControl();
              switchPressed = true;
              powerStatus = true;
            }

            if (columnValue == 1) {
              bitSet(LEDstatus, atoi(tempValue) - 1);
              columnControl();
              switchPressed = true;
              powerStatus = true;
            }
          }

        }
      }

      if (function == '4') {
        LEDstatus = 1023;
        columnControl();
        switchPressed = true;
        powerStatus = true;
      }

      if (function == '5') {
        LEDstatus = 0;
        columnControl();
        switchPressed = true;
        powerStatus = false;
      }

      if (function == '6') {
        Serial.print("a:"); Serial.print(powerStatus);
        Serial.print(","); Serial.print(PWMvalue);
        Serial.print(","); Serial.println(LEDstatus);
      }

      if (function == '7') {
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
