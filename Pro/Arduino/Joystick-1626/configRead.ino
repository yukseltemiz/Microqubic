void configRead() {

  EEPROM.get(address_directionA, directionA);
  EEPROM.get(address_directionB, directionB);
  EEPROM.get(address_directionC, directionC);
  EEPROM.get(address_directionX, directionX);
  EEPROM.get(address_directionY, directionY);
  EEPROM.get(address_directionZ, directionZ);
  EEPROM.get(address_directionR, directionR);


  if (configPrint) {
    Serial.println("");
    Serial.print("//CONFIGURATION// "); Serial.println(firmware);
    Serial.println("0 Exit");
    Serial.print("A)rm direction (-1 or 1):"); Serial.println(directionA);
    Serial.print("(B)oom direction (-1 or 1):"); Serial.println(directionB);
    Serial.print("(C)amera direction (-1 or 1):"); Serial.println(directionC);
    Serial.print("(X) direction (-1 or 1):"); Serial.println(directionX);
    Serial.print("(Y) direction (-1 or 1):"); Serial.println(directionY);
    Serial.print("(Z) direction (-1 or 1):"); Serial.println(directionZ);
    Serial.print("(R)otation direction (-1 or 1):"); Serial.println(directionR);
    configPrint = false;

  }

}

void configControl() {

  configMode = !configMode;
  if (!configMode) {
    delay(100);
    configRead();
    switchPressed_XY = false;
    switchPressed_CR = false;
    switchPressed_AT = false;
    Serial.println("Done!");
  }

  else {
    configPrint = true;
    configRead();
  }
}
