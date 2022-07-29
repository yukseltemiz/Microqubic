long measureSensorL() {

  long sensorAvg = 0;
  for (byte i = 0; i < measureAvg; i++) {
    sensorAvg = sensorAvg + analogReadEnh(sensorL, 16,0); //analogReadDiff(sensorL, sensorR, 16, 0);
  }
  return sensorAvg / measureAvg;
}

long measureSensorR() {

  long sensorAvg = 0;
  for (byte i = 0; i < measureAvg; i++) {
    sensorAvg = sensorAvg + analogReadEnh(sensorR, 16,0); //analogReadDiff(sensorL, sensorR, 16, 0);
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
