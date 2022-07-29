/*
void stallStop() {

  long slope;

  if (tempStepIncrement >= 10) {

    sensorValue = measureSensor();
    slope = (lastSensorValue - sensorValue) * 1000 / (stepNumber - lastStepNumber2);
 //   Serial.print(sensorValue); Serial.print(","); Serial.println(slope);

    if (fabs(slope) < 500 && sensorValue > 100 && sensorValue < 4000 ) {
      targetSpeed = 0;
      if (targetSpeed < 0) {
        stallState = -1;
      }
      if (targetSpeed > 0) {
        stallState = 1;
      }
    }

    lastSensorValue = sensorValue;
    lastStepNumber2 = stepNumber;
    tempStepIncrement = 0;
  }

}

*/
