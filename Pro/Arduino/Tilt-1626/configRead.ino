void configRead() {


  EEPROM.get(address_statusLEDintensity, statusLEDintensity);
  EEPROM.get(address_sensor_0degA, sensor_0deg[0]);
  EEPROM.get(address_sensor_neg90degA, sensor_neg90deg[0]);
  EEPROM.get(address_sensor_pos90degA, sensor_pos90deg[0]);
  EEPROM.get(address_sensor_0degB, sensor_0deg[1]);
  EEPROM.get(address_sensor_neg90degB, sensor_neg90deg[1]);
  EEPROM.get(address_sensor_pos90degB, sensor_pos90deg[1]);

  if (configPrint) {

    Serial.println("");
    Serial.print("//CONFIGURATION//"); Serial.println(firmware);
    Serial.println("0 Exit");
    Serial.print("1 Smooth stop (0 or 1):"); Serial.println(smoothStop);
    Serial.println("//ARM CALIBRATION//");
    Serial.print("4 Move to -90deg and confirm:"); Serial.println(sensor_neg90deg[0]);
    Serial.print("5 Move to 0deg and confirm:"); Serial.println(sensor_0deg[0]);
    Serial.print("6 Move to 90deg and confirm:"); Serial.println(sensor_pos90deg[0]);
    Serial.println("//BOOM CALIBRATION//");
    Serial.print("7 Move to -90deg and confirm:"); Serial.println(sensor_neg90deg[1]);
    Serial.print("8 Move to 0deg and confirm:"); Serial.println(sensor_0deg[1]);
    Serial.print("9 Move to 90deg and confirm:"); Serial.println(sensor_pos90deg[1]);

    configPrint = false;

  }

}

void configControl() {

  configMode = !configMode;
  if (!configMode) {
    configRead();
    checkStall = true;
    analogWrite(LEDpin, map(statusLEDintensity, 1, 100, 250, 0));
    Serial.println("Done!");
    targetSpeedSingle[0] = 0;
    targetSpeedSingle[1] = 0;

  }

  else {
    EEPROM.put(address_statusLEDintensity, statusLEDintensity);
    configPrint = true;
    checkStall = false;
    configRead();
  }
}
