void interpreter(char instruction[], int instructionSize) {

  if (!configMode) {

    if (instructionSize == 4) {

      if (instruction[1] == '0' && instruction[2] == '*') {
        Serial.println("test2");
      }
    }

  }
}

void resetReceived() {
  for (byte i = 0; i < serialMax; i++) {
    receivedString[i] = 0;
    serialCount = 0;
  }
}
