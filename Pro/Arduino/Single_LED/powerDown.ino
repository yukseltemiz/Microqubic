
void powerDown() {

 EEPROM.put(address_powerStatus, powerStatus);
 EEPROM.put(address_PWMvalue, PWMvalue);
 delay(100);
}
