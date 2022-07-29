void stallStop() {

  int interval;

  nowMillis2 = millis();

  if (nowMillis2 - lastMillis2 >= 100) {
    sensorValueB = measureSensor(1);
    if (targetSpeedSingle[1] > 0) {
      if (sensorValueB > sensor_neg90deg[1]) {
        targetSpeedSingle[1] = 0;
    //    Serial.print("stop");
      }
    }

    if (targetSpeedSingle[1] < 0) {
      if (sensorValueB < sensor_pos90deg[1]) {
        targetSpeedSingle[1] = 0;
    //    Serial.print("stop");
      }
    }
  }



}
