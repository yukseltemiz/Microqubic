void configRead() {

  EEPROM.get(address_powerStatus, powerStatus);
  EEPROM.get(address_LEDstatus, LEDstatus);
  EEPROM.get(address_PWMvalue, PWMvalue);


}
