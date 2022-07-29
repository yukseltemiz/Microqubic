
void powerDown() {

  targetSpeed = 0;
  driver.VACTUAL(0);
  digitalWriteFast(motorEN, LOW);
  EEPROM.put(address_stepNumber, stepNumber);
  EEPROM.put(address_lastDirection, lastDirection);
  EEPROM.put(address_homingState, 1);
  EEPROM.put(address_statusLEDintensity, statusLEDintensity);


  /*
    sleep_enable();//Enabling sleep mode
    attachInterrupt(PIN_PA0, powerup, RISING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_cpu();//activating sleep mode*/
}

/*
  void powerup() {
  sleep_disable();//Disable sleep mode
  detachInterrupt(PIN_PA0);
  configRead();
  }
*/
