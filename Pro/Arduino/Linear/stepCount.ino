
void stepCount() {

  tempStepIncrement++;

  if (backlash == false) {

    if (lastTargetSpeed < 0) {
      stepNumber--;
    }

    if (lastTargetSpeed > 0) {
      stepNumber++;

    }

  }

}
