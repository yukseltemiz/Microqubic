void setAngle() {

  if (serialAngle) {

    //    nowMillis = millis();

    //    if (nowMillis - lastMillis >= 20) {

    sensorValue = measureSensor();

    if (targetSpeed < 0) {

      if (smoothStop) {

        if ((targetSensorValue - sensorValue < 10) && abs(serialTargetSpeed) > (10 * speedCoefficient)) {
          targetSpeed = (sensorValue - targetSensorValue) * speedCoefficient;
        }
      }

      if (sensorValue >= targetSensorValue) {
        targetSpeed = 0;
        serialAngle = false;
      }
    }

    if (targetSpeed > 0) {

      if (smoothStop) {

        if ((sensorValue - targetSensorValue < 10) && abs(serialTargetSpeed) > (10 * speedCoefficient)) {
          targetSpeed = (sensorValue - targetSensorValue) * speedCoefficient;
        }
      }

      if (sensorValue <= targetSensorValue) {
        targetSpeed = 0;
        serialAngle = false;
      }
    }
    //    lastMillis = nowMillis;
    //   }

  }

}
