void printStatus() {


  float mapSensorT = ((((measureSensorT() * 5.0) / 1024) - 0.5) / 0.01); // MCP9700AT-E/TT, 10 mV/°C, 500 mV at 0°C

  currentAngle[0] = calculateAngle(0);
  currentAngle[1] = calculateAngle(1);

  Serial.println(currentAngle[0]);
  Serial.print("AB"); Serial.print(":");
  Serial.print(deviceType); Serial.print(",");
  Serial.print(mapSensorT, 2); Serial.print(",");
  Serial.print(currentAngle[0]); Serial.print(",");Serial.println(currentAngle[1]);

}
