void configSet(char configNumber, char inputValue[]) {

  switch (configNumber) {

    case '0':
      configControl();
      break;

    case '1':
      if (isUpperCase(inputValue[0])) {
        if (inputValue != 'A' && inputValue != 'B') {
          deviceID = inputValue[0];
          EEPROM.put(address_deviceID, deviceID);
          delay(10);
          configPrint = true;
          configRead();
        }
      }
      break;

    case '2':
      if (atoi(inputValue) == 0 || atoi(inputValue) == 1) {
        smoothStop = atoi(inputValue);
        EEPROM.put(address_smoothStop, smoothStop);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case '3':
      if (atoi(inputValue) >= 0 && atoi(inputValue) <= 50) {
        backlashValue = atoi(inputValue);
        EEPROM.put(address_backlashValue, backlashValue);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case 'l':
      sensorThresholdL = measureSensorL();
      EEPROM.put(address_sensorThresholdL, sensorThresholdL);
      delay(10);
      configPrint = true;
      configRead();
      break;

    case 'r':
      sensorThresholdR = measureSensorR();
      EEPROM.put(address_sensorThresholdR, sensorThresholdR);
      delay(10);
      configPrint = true;
      configRead();
      break;

    case 's':
      if (atof(inputValue) >= 5 && atoi(inputValue) <= 25) {
        distance_per_step = atof(inputValue);
        EEPROM.put(address_distance_per_step, distance_per_step);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;


    case '9':
      nowMillis = millis();
      targetSpeed = 1 * speedCoefficient;
      while (millis() - nowMillis < 1000) {
        motorMove();
      }
      checkStall = true;
      targetSpeed = -10 * speedCoefficient;
      while (targetSpeed != 0) {
        if (digitalReadFast(switchL) == HIGH || digitalReadFast(switchR) == HIGH) {
          break;
        }
        motorMove();
      }
      motorMove();
      sensorThresholdL = measureSensorL();
      EEPROM.put(address_sensorThresholdL, sensorThresholdL);
      delay(100);

      targetSpeed = 10 * speedCoefficient;

      while (targetSpeed != 0) {
        if (digitalReadFast(switchL) == HIGH || digitalReadFast(switchR) == HIGH) {
          break;
        }
        motorMove();
      }

      motorMove();
      sensorThresholdR = measureSensorR();
      EEPROM.put(address_sensorThresholdR, sensorThresholdR);
      delay(10);
      distance_per_step = float(maxStagePosition) / float(stepNumber - 10);
      EEPROM.put(address_distance_per_step, distance_per_step);
      delay(10);
      checkStall = false;
      Serial.print(sensorThresholdL); Serial.print(","); Serial.print(sensorThresholdR); Serial.print(","); Serial.println(distance_per_step);
      configPrint = true;
      configRead();
      break;
  }

}
