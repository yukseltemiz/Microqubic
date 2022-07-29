void configRead() {

  EEPROM.get(address_deviceID, deviceID);
  EEPROM.get(address_statusLEDintensity, statusLEDintensity);
  EEPROM.get(address_smoothStop, smoothStop);
  EEPROM.get(address_lastDirection, lastDirection);
  EEPROM.get(address_backlashValue, backlashValue);
  EEPROM.get(address_sensor_0deg, sensor_0deg);
  EEPROM.get(address_sensor_neg90deg, sensor_neg90deg);
  EEPROM.get(address_sensor_pos90deg, sensor_pos90deg);

  if (configPrint) {

    Serial.println("");
    Serial.print("//CONFIGURATION// "); Serial.println(firmware);
    Serial.println("0 Exit");
    Serial.print("1 Device ID:"); Serial.println(deviceID);
    Serial.print("2 Smooth stop (0 or 1):"); Serial.println(smoothStop);
    Serial.print("3 Backlash value (steps):"); Serial.println(backlashValue);
    Serial.println("//CALIBRATION//");
    Serial.print("7 Move to -90deg and confirm:"); Serial.println(sensor_neg90deg);
    Serial.print("8 Move to 0deg and confirm:"); Serial.println(sensor_0deg);
    Serial.print("9 Move to 90deg and confirm:"); Serial.println(sensor_pos90deg);
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
    Serial.println("Done!");
    targetSpeed = 0;
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
