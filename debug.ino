#ifdef DEBUG_SERIAL

/**
 * @description
 * Prints out the initial column headers for the serial console
 */
void printInputDebugColumnHeaders() {
  Serial.print("BAT");
  Serial.print("\t");
  Serial.print("SEL");
  Serial.print("\t");
  Serial.print("T");
  Serial.print("\t");
  Serial.print("A");
  Serial.print("\t");
  Serial.print("B");
  Serial.print("\t");
  Serial.print("C");
  Serial.print("\t");
  Serial.print("X");
  Serial.print("\t");
  Serial.print("Y");
  Serial.print("\t");
  Serial.print("D-UP");
  Serial.print("\t");
  Serial.print("D-DN");
  Serial.print("\t");
  Serial.print("D-L");
  Serial.print("\t");
  Serial.print("D-R");
  Serial.print("\t");
  Serial.print("Z");
  Serial.println("");
}

/**
 * @description
 * Simply prints out the state of the inputs to the Serial Buffer
 */
void printInputDebug() {
  Serial.print(batteryLevel);
  Serial.print("\t");
  Serial.print(btnSelect);
  Serial.print("\t");
  Serial.print(btnToggle);
  Serial.print("\t");
  Serial.print(btnA);
  Serial.print("\t");
  Serial.print(btnB);
  Serial.print("\t");
  Serial.print(btnC);
  Serial.print("\t");
  Serial.print(joyX);
  Serial.print("\t");
  Serial.print(joyY);
  Serial.print("\t");
  Serial.print(dPadUp);
  Serial.print("\t");
  Serial.print(dPadDown);
  Serial.print("\t");
  Serial.print(dPadLeft);
  Serial.print("\t");
  Serial.print(dPadRight);
  Serial.print("\t");
  Serial.print(potZ);
  Serial.println("");
}


/**
 * @description
 * Initialise the Serial Comms
 */
void initSerial() {
  Serial.begin(115200);
  Serial.println(APP_NAME);
  Serial.println(VERSION);
}

#endif
