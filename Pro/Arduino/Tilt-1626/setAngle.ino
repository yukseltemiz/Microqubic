void setAngle(int ID) {

  if (serialAngle[ID]) {

    nowMillis = millis();

    if (nowMillis - lastMillis >= 10) {


      sensorValue[ID] = measureSensor(ID);

      if (targetSpeedSingle[ID] < 0) {

        if (smoothStop) {

          if ((sensorValue[ID] - targetSensorValue[ID]) <= 10) {
            targetSpeedSingle[ID] = ((sensorValue[ID] - targetSensorValue[ID]) + 60) * -1 ;
          }
        }

        if (sensorValue[ID] <= targetSensorValue[ID]) {
          targetSpeedSingle[ID] = 0;
          serialAngle[ID] = false;
        }
      }

      if (targetSpeedSingle[ID] > 0) {

        if (smoothStop) {

          if ((targetSensorValue[ID] - sensorValue[ID]) <= 10) {
            targetSpeedSingle[ID] = ((targetSensorValue[ID] - sensorValue[ID]) + 60) ;
          }
        }

        if (sensorValue[ID] >= targetSensorValue[ID]) {
          targetSpeedSingle[ID] = 0;
          serialAngle[ID] = false;
        }
      }
      lastMillis = nowMillis;
    }

  }

}
