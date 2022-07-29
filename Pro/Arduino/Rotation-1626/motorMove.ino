void motorMove() {

  if (targetSpeed != lastTargetSpeed) {

    if (!configMode) {
      backlashFunction();
    }

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
      if ((stepNumber - lastStepNumber) >= targetStepNumber) {
        targetSpeed = 0;
        serialMove = false;
      }
    }

    if (targetSpeed < 0) {
      if ((stepNumber - lastStepNumber) <= targetStepNumber) {
        targetSpeed = 0;
        serialMove = false;
      }
    }
  }

  /*
    if (checkStall == true && backlash == false && targetSpeed != 0) {
      stallStop();
    }*/

  if (backlash == false && targetSpeed != 0) {
    setAngle();
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
