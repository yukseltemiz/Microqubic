long measureSensorL() {

  long sensorAvg = 0;
  for (byte i = 0; i < measureAvg; i++) {
    sensorAvg = sensorAvg + analogReadEnh(sensorL, 12,0); //analogReadDiff(sensorL, sensorR, 16, 0);
  }
  return sensorAvg / measureAvg;
}

long measureSensorR() {

  long sensorAvg = 0;
  for (byte i = 0; i < measureAvg; i++) {
    sensorAvg = sensorAvg + analogReadEnh(sensorR, 12,0); //analogReadDiff(sensorL, sensorR, 16, 0);
  }
  return sensorAvg / measureAvg;
}

long measureSensorT() {

  long sensorAvg = 0;
  for (byte i = 0; i < measureAvg; i++) {
    sensorAvg = sensorAvg + analogReadEnh(sensorT, 10,0); 
  }
  return sensorAvg / measureAvg;
}
