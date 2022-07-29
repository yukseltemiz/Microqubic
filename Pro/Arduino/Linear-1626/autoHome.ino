void autoHome() {

  targetSpeed = -10 * speedCoefficient;

  while (targetSpeed != 0) {
    if (digitalReadFast(switchL) == HIGH || digitalReadFast(switchR) == HIGH) {
      break;
    }
    motorMove();
  }

}
