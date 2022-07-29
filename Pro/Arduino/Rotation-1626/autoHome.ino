void autoHome() {

  currentAngle = calculateAngle();
  targetAngle = 0;
  targetSensorValue = calculateTargetValue();
  stepNumber = 0;

  if ( targetAngle > currentAngle ) {
    targetSpeed = autoHomeSpeed * -1;
  }

  if (targetAngle < currentAngle) {
    targetSpeed = autoHomeSpeed;
  }

}
