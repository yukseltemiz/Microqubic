void actions (char function) {


  switch (function) {
    case '0':
      targetSpeed = 0;
      break;

    case '1':   
      targetSpeed = serialTargetSpeed;
      break;

    case '2':
      checkDirection();
      break;

    case '3':
      checkDirection();
      break;

    case '4':
      serialMove = true;

      if (targetStepNumber > 0) {
        targetSpeed = abs(serialTargetSpeed);
      }

      if (targetStepNumber < 0) {
        targetSpeed = abs(serialTargetSpeed) * -1;
      }
      lastStepNumber = stepNumber;
      break;

    case '5':
      autoHome();
      break;

  }

}

void checkDirection() {

  if ( targetAngle > currentAngle ) {
    targetSpeed = abs(serialTargetSpeed) * -1;
  }

  if (targetAngle < currentAngle) {
    targetSpeed = abs(serialTargetSpeed);
  }

  Serial.println(targetSpeed);


}
