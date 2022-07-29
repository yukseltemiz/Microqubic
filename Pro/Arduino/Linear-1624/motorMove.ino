void motorMove() {

  if (!configMode) {
    backlashFunction();
  }


  if (targetSpeed != lastTargetSpeed) {

    if (backlash == false) {

      if (targetSpeed == 0) {
        driver.VACTUAL(0);
        digitalWriteFast(motorEN, LOW);
      }

      if (targetSpeed > 0 && stallState <= 0 ) {

        digitalWriteFast(motorEN, HIGH);
        driver.VACTUAL(targetSpeed);
        lastDirection = 1;
        stallState = 0;
      }

      if (targetSpeed < 0 && stallState >= 0 ) {

        digitalWriteFast(motorEN, HIGH);
        driver.VACTUAL(targetSpeed);
        lastDirection = -1;
        stallState = 0;
      }

      lastTargetSpeed = targetSpeed;

    }
  }

  if (serialMove) {

    if (targetSpeed > 0) {

      if (smoothStop) {

        if ((targetStepNumber - stepNumber < 50) && abs(serialTargetSpeed) >= (5 * speedCoefficient)) {
          targetSpeed = (targetStepNumber - stepNumber) / 10 * speedCoefficient ;
        }
      }

      if (stepNumber >= targetStepNumber) {
        targetSpeed = 0;
        serialMove = false;
      }
    }

    if (targetSpeed < 0) {

      if (smoothStop) {

        if ((stepNumber - targetStepNumber < 50) && abs(serialTargetSpeed) >= (5 * speedCoefficient)) {
          targetSpeed = (targetStepNumber - stepNumber) / 10 * speedCoefficient ;
        }
      }

      if (stepNumber <= targetStepNumber) {
        targetSpeed = 0;
        serialMove = false;
      }
    }
  }


  if (checkStall == true && backlash == false && targetSpeed != 0) {
    stallStop();
  }

}

void backlashFunction() {
  if (targetSpeed > 0 && lastDirection == -1) {
    if (backlash == false) {
      tempStepIncrement = 0;
      digitalWriteFast(motorEN, HIGH);
      driver.VACTUAL(backlashSpeed);
      backlash = true;
    }
  }

  if (targetSpeed < 0 && lastDirection == 1) {
    if (backlash == false) {
      tempStepIncrement = 0;
      digitalWriteFast(motorEN, HIGH);
      driver.VACTUAL(backlashSpeed * -1);
      backlash = true;
    }
  }

  if (backlash == true && tempStepIncrement >= backlashValue) {
    backlash = false;
    lastDirection = 0;
  }

}
