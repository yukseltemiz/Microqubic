void interpreter(char instruction[], int instructionSize) {
  byte k = 0; byte l = 0;
  char tempValue1[8];
  char tempValue2[8];
  char configValue[8];
  char function;
  boolean IDfound = false;
  boolean searchParameter1 = false; //speed
  boolean searchParameter2 = false; //distance
  float mappedSpeed;

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

      if (instruction[1] == deviceID && instruction[2] == '6') {
        printStatus();
      }

      if (instruction[1] == deviceID && instruction[2] == '7') {
        configControl();
      }

    }

    if (instruction[1] == '*' && instruction[2] == '8') {
      k = 1;
      IDfound = true;
    }

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
        searchParameter1 = true; //speed
      }


      if (searchParameter1) {

        for (int i = k + 3; i < k + 10; i++) {
          if (instruction[i] == ',') {
            l = i;
            searchParameter2 = true; //position
            break;
          }
          tempValue1[i - (k + 3)] = instruction[i];

        }

        if (abs(atof(tempValue1)) <= 100) {
          mappedSpeed = atof(tempValue1) / 100.0 * maxTargetSpeed;
          if (atof(tempValue1) >= 0) { 
            serialTargetSpeed = int(mappedSpeed+0.5);
          }
          if (atof(tempValue1) < 0) {
            serialTargetSpeed = int(mappedSpeed-0.5);
          }
//          Serial.println(serialTargetSpeed);
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

        if (function == '2') {
          targetStepNumber = (1000 * atof(tempValue2) / distance_per_step) + stepNumber ;
        }

        if (function == '3' && atof(tempValue2) >= 0 && homingState == 1) {
          targetStepNumber = 1000 * atof(tempValue2) / distance_per_step ;
        }

        if (function == '4') {
          targetStepNumber = atoi(tempValue2);
        }


      }

      actions(function);
    }
  }

  if (configMode) {

    if (instruction[2] == ':') {
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
