
void printStatus() {

  float mapSensorT = ((((measureSensorT() * 5.0) / 1024) - 0.5) / 0.01); // MCP9700AT-E/TT, 10 mV/°C, 500 mV at 0°C
  currentStagePosition = float(stepNumber) * distance_per_step / 1000.0;

  Serial.print(deviceID); Serial.print(":");
  Serial.print(deviceType); Serial.print(",");
  Serial.print(mapSensorT, 2);Serial.print(",");
  Serial.print(currentStagePosition, 2);Serial.print(",");
  Serial.print(stepNumber); Serial.print(",");
  Serial.println(homingState); 
 


}
