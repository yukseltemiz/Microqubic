void configRead() {

  EEPROM.get(address_powerStatus, powerStatus);
  EEPROM.get(address_statusLEDintensity , statusLEDintensity);
  EEPROM.get(address_PWMvalue, PWMvalue);
  EEPROM.get(address_LEDstatus, LEDstatus);

}
