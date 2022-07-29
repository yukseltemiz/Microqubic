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
      if (atoi(inputValue) >= 0 || atoi(inputValue) <= 50) {
        backlashValue = atoi(inputValue);
        EEPROM.put(address_backlashValue, backlashValue);
        delay(100);
        configPrint = true;
        configRead();
      }
      break;


    case '7':
      sensor_neg90deg = measureSensor();
      EEPROM.put(address_sensor_neg90deg, sensor_neg90deg);
      delay(100);
      configPrint = true;
      configRead();
      break;

    case '8':
      sensor_0deg = measureSensor();
      EEPROM.put(address_sensor_0deg, sensor_0deg);
      delay(100);
      configPrint = true;
      configRead();
      break;

    case '9':
      sensor_pos90deg = measureSensor();
      EEPROM.put(address_sensor_pos90deg, sensor_pos90deg);
      delay(100);
      configPrint = true;
      configRead();
      break;

  }

}
