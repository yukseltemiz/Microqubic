
void powerDown() {
  targetSpeed = 0;
  driver.VACTUAL(0);
  digitalWriteFast(motorEN, LOW);
  EEPROM.put(address_statusLEDintensity, statusLEDintensity);
}
