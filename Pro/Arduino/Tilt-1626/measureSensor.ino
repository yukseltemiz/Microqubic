long measureSensor (int ID) {

  long sensorAvg = 0;

  if (ID == 0) {
    for (byte i = 0; i < measureAvg; i++) {
      sensorAvg = sensorAvg + analogReadEnh(sensorArm, 10, 0);
    }
  }
  if (ID == 1) {
    for (byte i = 0; i < measureAvg; i++) {
      sensorAvg = sensorAvg + analogReadEnh(sensorBoom, 10, 0);
    }
  }
  return sensorAvg / measureAvg;
}

long measureSensorT() {

  long sensorAvg = 0;
  for (byte i = 0; i < measureAvg; i++) {
    sensorAvg = sensorAvg + analogReadEnh(sensorT, 10, 0);
  }
  return sensorAvg / measureAvg;
}

float calculateAngle(int ID) {

  sensorValue[ID] = measureSensor(ID);

  if (sensorValue[ID] >= sensor_0deg[ID]) {
    return (sensor_0deg[ID]-sensorValue[ID]) * 90.0 / (sensor_neg90deg[ID] - sensor_0deg[ID]) ;
  }

  if (sensorValue[ID] < sensor_0deg[ID]) {
    return (sensor_0deg[ID] - sensorValue[ID]) * 90.0 / (sensor_0deg[ID] - sensor_pos90deg[ID]) ;
  }
}


long calculateTargetValue(int ID) {

  if (targetAngle[ID] >= 0 && targetAngle[ID] <= (160-(ID*70))) { // limit boom to 90deg
    serialAngle[ID] = true;
    return sensor_0deg[ID] + (targetAngle[ID] * (sensor_pos90deg[ID] - sensor_0deg[ID]) / 90);
  }
  if (targetAngle[ID] < 0 && targetAngle[ID] >= (-160+(ID*70))) { //limit boom to -90deg
    serialAngle[ID] = true;
    return sensor_0deg[ID] + (targetAngle[ID] * (sensor_0deg[ID] - sensor_neg90deg[ID]) / 90);
  }

  else {
    serialTargetSpeed[ID] = 0;
  }

}
