void configRead() {

  EEPROM.get(address_deviceID, deviceID);
  EEPROM.get(address_statusLEDintensity, statusLEDintensity);
  EEPROM.get(address_smoothStop, smoothStop);
  EEPROM.get(address_lastDirection, lastDirection);
  EEPROM.get(address_distance_per_step, distance_per_step);
  EEPROM.get(address_backlashValue, backlashValue);
  EEPROM.get(address_stepNumber, stepNumber);
  EEPROM.get(address_sensorThresholdL, sensorThresholdL);
  EEPROM.get(address_sensorThresholdR, sensorThresholdR);


  if (configPrint) {

    Serial.println("");
    Serial.print("//CONFIGURATION// "); Serial.println(firmware);
    Serial.println("0 Exit");
    Serial.print("1 Device ID:"); Serial.println(deviceID);
    Serial.print("2 Smooth stop (0 or 1):"); Serial.println(smoothStop);
    Serial.print("3 Backlash value (steps):"); Serial.println(backlashValue);
    Serial.println("//CALIBRATION//");
    Serial.println("9 Remove any obstacles and confirm");
    configPrint = false;

  }

}

void configControl() {

  configMode = !configMode;
  if (!configMode) {
    delay(100);
    configRead();
    checkStall = true;
    analogWrite(LEDpin, map(statusLEDintensity, 1, 100, 250, 0));
    targetSpeed = 0;
    Serial.println("Done!");
  }

  else {
    EEPROM.put(address_stepNumber, stepNumber);
    EEPROM.put(address_lastDirection, lastDirection);
    EEPROM.put(address_statusLEDintensity, statusLEDintensity);
    configPrint = true;
    checkStall = false;
    configRead();
  }
}
