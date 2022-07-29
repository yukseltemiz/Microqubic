
void printStatus() {

  float mapSensorT = ((((measureSensorT() * 5.0) / 1024) - 0.5) / 0.01); // MCP9700AT-E/TT, 10 mV/°C, 500 mV at 0°C

  currentAngle = calculateAngle();

  Serial.print(deviceID); Serial.print(":");
  Serial.print(deviceType); Serial.print(",");
  Serial.print(mapSensorT, 2);Serial.print(",");
  Serial.println(currentAngle, 2);

}
