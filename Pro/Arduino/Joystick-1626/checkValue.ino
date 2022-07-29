void checkValue() {

  if (!configMode) {

    nowMillis = millis();
    if (nowMillis - lastMillis >= 100) {

      pot1value = (analogReadEnh(pot1, 10, 0) - firstPot1value) / 10;
      speed1 = (abs(pot1value) * pot1value) / 30;
      if (lastSpeed1 != speed1) {
        if (state == 1 ) {
          Serial.print("$Y1,"); Serial.println(speed1 * directionY);
        }
        if (state == 2 ) {
          Serial.print("$C1,"); Serial.println(speed1 * directionC);
        }
        if (state == 3 ) {
          Serial.print("$B1,"); Serial.println(speed1 * directionB);
        }
        lastSpeed1 = speed1;
      }


      pot2value = (analogReadEnh(pot2, 10, 0) - firstPot2value) / 10;
      speed2 = (abs(pot2value) * pot2value) / 30;
      if (lastSpeed2 != speed2) {
        if (state == 1 ) {
          Serial.print("$X1,"); Serial.println(speed2 * -1 * directionX);
        }
        if (state == 2 ) {
          Serial.print("$R1,"); Serial.println((speed2 * -1 * directionR)/2);
        }
        if (state == 3 ) {
          Serial.print("$A1,"); Serial.println(speed2 * directionA);
        }
        lastSpeed2 = speed2;
      }


      pot3value = (analogReadEnh(pot3, 10, 0) - firstPot3value) / 10;
      speed3 = (abs(pot3value) * pot3value) / 30;
      if (lastSpeed3 != speed3) {
        Serial.print("$Z1,"); Serial.println(speed3 * -1 * directionZ);
        lastSpeed3 = speed3;
      }

      lastMillis = nowMillis;
    }
  }
}
