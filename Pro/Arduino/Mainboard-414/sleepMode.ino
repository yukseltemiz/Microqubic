
void powerdown() {

  digitalWriteFast(LEDpin, LOW);
  Serial.println("test-save settings");
  delay(1000);
  digitalWriteFast(LEDpin, LOW);
  digitalWriteFast(powerEN, LOW);
  sleep_enable();//Enabling sleep mode
  attachInterrupt(touchSwitch, powerup, RISING);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();//activating sleep mode

}

void powerup() {
  sleep_disable();//Disable sleep mode
  detachInterrupt(touchSwitch);
}
