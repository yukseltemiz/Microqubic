void interpreter(char instruction[], int instructionSize) {
  char deviceID;
  int k = 0; int l = 0;
  char tempValue1[8];
  char tempValue2[8];
  char configValue[8];
  char function;
  boolean IDfound = false;
  boolean searchParameter1 = false; //speed
  boolean searchParameter2 = false; //angle
  int mappedSpeed;

  for (int i = 0; i < 8; i++) {
    tempValue1[i] = 0;
    tempValue2[i] = 0;
    configValue[i] = 0;
  }


  if (!configMode) {

    if (instructionSize == 4) {

      if (instruction[1] == '*' && instruction[2] == '0') {
        targetSpeed = 0;
        driver.VACTUAL(0);
        digitalWrite(motorEN, LOW);
      }

      if (instruction[1] == '*' && instruction[2] == '9') {
        powerDown();
      }

      if (instruction[1] == '*' && instruction[2] == '5') {
        autoHome();
      }

      if (instruction[1] == 'A' && instruction[2] == '6') {
        printStatus();
      }

      if (instruction[1] == 'A' && instruction[2] == '7') {
        configControl();
      }


    }

    if (instruction[1] == '*' && instruction[2] == '8') {
      k = 1;
      IDfound = true;
    }

    deviceID = 'A';

    for (int ID = 0; ID < 2; ID++) {

      for (int i = 1; i < instructionSize - 1; i++) {
        if (instruction[i] == deviceID) {
          IDfound = true;
          k = i;
        }
      }

      if (IDfound) {

        if (isDigit(instruction[k + 1])) {
          function = instruction[k + 1];
        }

        if (instruction[k + 2] == ',') {
          searchParameter1 = true;
        }

        if (searchParameter1) {
          for (int i = k + 3; i < k + 10; i++) {
            if (instruction[i] == ',') {
              l = i;
              searchParameter2 = true;
              break;
            }
            tempValue1[i - (k + 3)] = instruction[i];
          }

          if (abs(atoi(tempValue1)) <= 100 && abs(atoi(tempValue1)) >= 0) {
            if (atoi(tempValue1) >= 0) {
              mappedSpeed = map(atoi(tempValue1), 0, 100, 60, 250);
            }
            if (atoi(tempValue1) < 0) {
              mappedSpeed = map(atoi(tempValue1), -100, 0, -250, -60);
            }

            if (atoi(tempValue1) == 0) {
              mappedSpeed = 0;
            }
            serialTargetSpeed[ID] =  mappedSpeed;

          }

          if (function == '8' && atoi(tempValue1) >= 1 && atoi(tempValue1) <= 100) {
            statusLEDintensity = atoi(tempValue1);
            analogWrite(LEDpin, map(statusLEDintensity, 1, 100, 250, 0));
          }



        }

        if (searchParameter2) {
          for (int i = l + 1; i < l + 8; i++) {
            if (instruction[i] == ' ' || instruction[i] == 0) {
              break;
            }
            tempValue2[i - (l + 1)] = instruction[i];
          }


          if (function == '2') { // relative move
            currentAngle[ID] = calculateAngle(ID);
            targetAngle[ID] = atof(tempValue2) + currentAngle[ID];
            targetSensorValue[ID] = calculateTargetValue(ID);
          }

          if (function == '3' ) { //absolute angle
            currentAngle[ID] = calculateAngle(ID);
            targetAngle[ID] = atof(tempValue2);
            targetSensorValue[ID] = calculateTargetValue(ID);
          }

        }

        actions(ID, function);
      }
      deviceID = 'B';
      searchParameter1 = false;
      searchParameter2 = false;
      IDfound = false;
      for (int i = 0; i < 8; i++) {
        tempValue1[i] = 0;
        tempValue2[i] = 0;
      }

    }

  }


  if (configMode) {

    if (isDigit(instruction[1]) && instruction[2] == ':') {
      for (int i = 3; i < 10; i++) {
        configValue[i - 3] = instruction[i];
      }
      configSet(instruction[1], configValue);

    }
    if (instruction[1] == 'P' && instruction[2] == ':') {
      sensorDebug = !sensorDebug;
      configPrint = true;
      configRead();
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
