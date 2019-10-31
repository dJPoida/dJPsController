/**
 * This unit contains the RF Transmit code
 * @see: https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
 */

// Initialise the radio
RF24 radio(PIN_RF_CE, PIN_RF_CSN);


/**
 * @description
 * Transmit the whole control state as a string
 */
void transmitControlState() {
  char transmitBuffer[DATA_PACKET_SIZE];

  // Example Transmit:
  // PPTABCXXXYYYZZUNLR (18 Bytes)
  // 990000127127000000 (18 bytes)
  sprintf(transmitBuffer, "%02d%d%d%d%d%03d%03d%02d%d%d%d%d", batteryLevel, btnToggle, btnA, btnB, btnC, joyX, joyY, potZ, dPadUp, dPadDown, dPadLeft, dPadRight);

  #ifdef DEBUG_SERIAL
  Serial.print("Transmit: "); 
  Serial.println(transmitBuffer);
  #endif

  // Actually transmit
  radio.write(&transmitBuffer, sizeof(transmitBuffer));

  lastStateTransmit = millis();
}


/**
 * @description
 * Set the current radio address based on the current mode
 * 
 * @todo: change this from a horriffic switch into an array of addresses
 */
void setRadioAddress(byte forMode) {
  // Transmitter adddresses
  byte address[5] = {'d', 'J', 'P', '0', forMode};

  #ifdef DEBUG_SERIAL
  Serial.print("ADDR: ");
  for(int i = 0; i < 5; i++) {
    Serial.print(address[i], HEX);
  }
  Serial.println("");
  #endif
  
  radio.openWritingPipe(address);
  radio.stopListening();

  // Transmit the initial control state for the receiver
  delay(10); // TODO: determine if this is necessary
  transmitControlState();
}

/**
 * @descripion init the RF channel
 */
void initRadio() {
  radio.begin();
  radio.setDataRate(RADIO_DATA_RATE);
  radio.setRetries(1,5); // delay, count
  radio.setPALevel(RADIO_POWER);
  setRadioAddress(mode);
}
