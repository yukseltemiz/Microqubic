long measureSensor() {

  long sensorAvg = 0;
  for (byte i = 0; i < measureAvg; i++) {
    sensorAvg = sensorAvg + analogReadEnh(sensorAngle, 10, 0);
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

float calculateAngle() {

  sensorValue = measureSensor();

  if (sensorValue >= sensor_0deg) {
    return (sensorValue - sensor_0deg) * 90.0 / (sensor_pos90deg - sensor_0deg) ;
  }

  if (sensorValue < sensor_0deg) {
    return (sensorValue - sensor_0deg) * 90.0 / (sensor_0deg - sensor_neg90deg) ;
  }
}

long calculateTargetValue() {

  if (targetAngle >= 0 && targetAngle <= 160) {
    serialAngle = true;
    return sensor_0deg + (targetAngle * (sensor_pos90deg - sensor_0deg) / 90);
  }
  if (targetAngle < 0 && targetAngle >= -160 ) {
    serialAngle = true;
    return sensor_0deg + (targetAngle * (sensor_0deg - sensor_neg90deg) / 90);
  }

  else {
    serialTargetSpeed = 0;  
  }

}
