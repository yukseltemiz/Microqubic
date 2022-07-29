void interpreter(char instruction[], int instructionSize) {
  char configValue[8];

  for (int i = 0; i < 8; i++) {
    configValue[i] = 0;
  }


  if (configMode) {

    if (instruction[2] == ':') {
      for (int i = 3; i < 10; i++) {
        configValue[i - 3] = instruction[i];
      }
      configSet(instruction[1], configValue);
    }

  }

}

void resetReceived() {
  for (byte i = 0; i < serialMax; i++) {
    receivedString[i] = 0;
    serialCount = 0;
  }
  correctFormat = false;
}
