void columnControl() {
  digitalWrite(col1,  bitRead(~LEDstatus, 0));
  digitalWrite(col2,  bitRead(~LEDstatus, 1));
  digitalWrite(col3,  bitRead(~LEDstatus, 2));
  digitalWrite(col4,  bitRead(~LEDstatus, 3));
  digitalWrite(col5,  bitRead(~LEDstatus, 4));
  digitalWrite(col6,  bitRead(~LEDstatus, 5));
  digitalWrite(col7,  bitRead(~LEDstatus, 6));
  digitalWrite(col8,  bitRead(~LEDstatus, 7));
  digitalWrite(col9,  bitRead(~LEDstatus, 8));
  digitalWrite(col10, bitRead(~LEDstatus, 9));
}
