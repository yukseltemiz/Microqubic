
void actions (int ID, char function) {

  switch (function) {

    case '0':
      targetSpeedSingle[ID] = 0;
      targetSpeed = (targetSpeedSingle[1] << 16) + targetSpeedSingle[0];
      break;

    case '1':
      targetSpeedSingle[ID] = serialTargetSpeed[ID]*-1;
      break;

    case '2':
      checkDirection(ID);
      break;

    case '3':
      checkDirection(ID);
      break;

  }

}


void checkDirection(int ID) {

  if ( targetAngle[ID] > currentAngle[ID] ) {
    targetSpeedSingle[ID] = abs(serialTargetSpeed[ID]) * -1;
  }

  if (targetAngle[ID] < currentAngle[ID]) {
    targetSpeedSingle[ID] = abs(serialTargetSpeed[ID]);
  }

}
