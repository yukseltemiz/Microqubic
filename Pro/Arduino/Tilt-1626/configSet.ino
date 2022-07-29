void configSet(char configNumber, char inputValue[]) {

  switch (configNumber) {

    case '0':
      configControl();
      break;

    case '1':
      if (atoi(inputValue) == 0 || atoi(inputValue) == 1) {
        smoothStop = atoi(inputValue);
        EEPROM.put(address_smoothStop, smoothStop);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case '4':
      sensor_neg90deg[0] = measureSensor(0);
      EEPROM.put(address_sensor_neg90degA, sensor_neg90deg[0]);
      delay(10);
      configPrint = true;
      configRead();
      break;

    case '5':
      sensor_0deg[0] = measureSensor(0);
      EEPROM.put(address_sensor_0degA, sensor_0deg[0]);
      delay(10);
      configPrint = true;
      configRead();
      break;

    case '6':
      sensor_pos90deg[0] = measureSensor(0);
      EEPROM.put(address_sensor_pos90degA, sensor_pos90deg[0]);
      delay(10);
      configPrint = true;
      configRead();
      break;

    case '7':
      sensor_neg90deg[1] = measureSensor(1);
      EEPROM.put(address_sensor_neg90degB, sensor_neg90deg[1]);
      delay(10);
      configPrint = true;
      configRead();
      break;

    case '8':
      sensor_0deg[1] = measureSensor(1);
      EEPROM.put(address_sensor_0degB, sensor_0deg[1]);
      delay(10);
      configPrint = true;
      configRead();
      break;

    case '9':
      sensor_pos90deg[1] = measureSensor(1);
      EEPROM.put(address_sensor_pos90degB, sensor_pos90deg[1]);
      delay(10);
      configPrint = true;
      configRead();
      break;

  }
}
