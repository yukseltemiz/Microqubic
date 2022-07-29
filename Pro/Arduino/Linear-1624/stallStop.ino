void stallStop() {

  long slope;

  if (tempStepIncrement >= 10) {

    if (targetSpeed < 0) {

      sensorValue = measureSensorL();
      slope = (sensorValue - lastSensorValue) * 1000 / (stepNumber - lastStepNumber2);
      if (fabs(slope) < 1000 && sensorValue > (sensorThresholdL - 200) && sensorValue < (sensorThresholdL + 200) ) { //800 for Si7211
        /*   targetSpeed = 0;
           stepNumber = 1;
           stallState = -1;
           homingState = 1;*/
      }

    }

    if (targetSpeed > 0) {

      sensorValue = measureSensorR();
      slope = (sensorValue - lastSensorValue) * 1000 / (stepNumber - lastStepNumber2);
      Serial.print(slope); Serial.print(","); Serial.println(sensorValue);
      if (fabs(slope) < 1000 && sensorValue > (sensorThresholdR - 200) && sensorValue < (sensorThresholdR + 200) ) {
   /*     targetSpeed = 0;
        if (!configMode) {
          stepNumber = maxStagePosition / (distance_per_step);
        }
        stallState = 1;
        homingState = 1;*/
      }

    }

    lastSensorValue = sensorValue;
    lastStepNumber2 = stepNumber;
    tempStepIncrement = 0;
  }

}
