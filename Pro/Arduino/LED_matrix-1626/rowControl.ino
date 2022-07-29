void rowControl() {

  pinMode (SDI, OUTPUT);
  delay(1);
  for (int i = 0; i < 16; i++) {
    digitalWrite(CLK, LOW);
    delay(1);
    digitalWrite(SDI, bitRead(columnDataMapped, i));
    delay(1);
    digitalWrite(CLK, HIGH);
    delay(1);
  }

  digitalWrite(LE, HIGH);
  delay(1);
  analogWrite(OE, map(PWMvalue, 0, 100, 255, 0));
  pinMode (SDI, INPUT);

}
