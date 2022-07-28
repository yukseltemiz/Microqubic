void actions (char function) {


  switch (function) {
    case '0':
      targetSpeed = 0;
      break;

    case '1':
      targetStepNumber = 0;
      targetSpeed = serialTargetSpeed;
      break;

    case '2':

checkDirection();

      break;

    case '3':

checkDirection();

      break;

    case '4':

checkDirection();

      break;

    case '5':
      autoHome();
      break;

  }

}

void checkDirection() {

  serialMove = true;

  if (targetStepNumber > stepNumber) {
    targetSpeed = abs(serialTargetSpeed);
  }

  if (targetStepNumber < stepNumber) {
    targetSpeed = abs(serialTargetSpeed) * -1;
  }

}
