/**
 * Update the DPad Butons
 */
bool updateDPad() {
  // Read the new values
  bool newDPadUp = !digitalRead(PIN_BTN_D_UP);
  bool newDPadDown = !digitalRead(PIN_BTN_D_DOWN);
  bool newDPadLeft = !digitalRead(PIN_BTN_D_LEFT);
  bool newDPadRight = !digitalRead(PIN_BTN_D_RIGHT);

  // Any changes?
  if (
    (newDPadUp != dPadUp) ||
    (newDPadDown != dPadDown) ||
    (newDPadLeft != dPadLeft) ||
    (newDPadRight != dPadRight)
    ){
    dPadUp = newDPadUp;
    dPadDown = newDPadDown;
    dPadLeft = newDPadLeft;
    dPadRight = newDPadRight;
    return true;
  }

  return false;
}
