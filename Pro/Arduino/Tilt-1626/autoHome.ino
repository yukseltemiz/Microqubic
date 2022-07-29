void autoHome() {

  for (int i = 0; i < 2; i++) {

    currentAngle[i] = calculateAngle(i);
    targetAngle[i] = 0;
    targetSensorValue[i] = calculateTargetValue(i);

    if ( targetAngle[i] > currentAngle[i] ) {
      targetSpeedSingle[i] = -150;
    }

    if (targetAngle[i] < currentAngle[i]) {
      targetSpeedSingle[i] = 150;
    }
  }

}
