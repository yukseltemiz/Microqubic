void configSet(char configNumber, char inputValue[]) {

  switch (configNumber) {

    case '0':
      configControl();
      break;

    case 'A':
      if (atoi(inputValue) == -1 || atoi(inputValue) == 1) {
        directionA = atoi(inputValue);
        EEPROM.put(address_directionA, directionA);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case 'B':
      if (atoi(inputValue) == -1 || atoi(inputValue) == 1) {
        directionB = atoi(inputValue);
        EEPROM.put(address_directionB, directionB);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case 'C':
      if (atoi(inputValue) == -1 || atoi(inputValue) == 1) {
        directionC = atoi(inputValue);
        EEPROM.put(address_directionC, directionC);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case 'X':
      if (atoi(inputValue) == -1 || atoi(inputValue) == 1) {
        directionX = atoi(inputValue);
        EEPROM.put(address_directionX, directionX);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case 'Y':
      if (atoi(inputValue) == -1 || atoi(inputValue) == 1) {
        directionY = atoi(inputValue);
        EEPROM.put(address_directionY, directionY);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case 'Z':
      if (atoi(inputValue) == -1 || atoi(inputValue) == 1) {
        directionZ = atoi(inputValue);
        EEPROM.put(address_directionZ, directionZ);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;

    case 'R':
      if (atoi(inputValue) == -1 || atoi(inputValue) == 1) {
        directionR = atoi(inputValue);
        EEPROM.put(address_directionR, directionR);
        delay(10);
        configPrint = true;
        configRead();
      }
      break;


  }

}
