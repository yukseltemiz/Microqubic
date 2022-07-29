void motorMove() {

  if (targetSpeedSingle[0] != lastTargetSpeedSingle[0] || targetSpeedSingle[1] != lastTargetSpeedSingle[1] ) {

    targetSpeed = (targetSpeedSingle[1] << 16) + targetSpeedSingle[0];
/*
    if (lastTargetSpeedSingle[0] * targetSpeedSingle[0] < 0) {
      digitalWriteFast(motorEN, LOW);
      delay(200);
      digitalWriteFast(motorEN, HIGH);
    }*/


    if (targetSpeed == 0) {
      driver.VACTUAL(0);
      digitalWriteFast(motorEN, LOW);
    }

    if (targetSpeed != 0) {
      digitalWriteFast(motorEN, HIGH);
      driver.VACTUAL(targetSpeed * -1);
/*
      if (targetSpeedSingle[0] > 0) {
        lastDirection[0] = 1;
      }
      else {
        lastDirection[0] = -1;
      }

      if (targetSpeedSingle[1] > 0) {
        lastDirection[1] = 1;
      }
      else {
        lastDirection[1] = -1;
      }*/
    }
    lastTargetSpeedSingle[0] = targetSpeedSingle[0];
    lastTargetSpeedSingle[1] = targetSpeedSingle[1];
  }

  if (targetSpeedSingle[0] != 0) {
    setAngle(0);
  }

  if (targetSpeedSingle[1] !=0){
    setAngle(1);
    stallStop();
  }

}
