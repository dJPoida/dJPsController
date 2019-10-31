/**
 * Update the Button A
 */
bool updateButtonA() {
  // Read the new values
  bool newBtnA = !digitalRead(PIN_BTN_A);

  // Any changes?
  if (newBtnA != btnA){
    btnA = newBtnA;
    return true;
  }

  return false;
}


/**
 * Update the Button B
 */
bool updateButtonB() {
  // Read the new values
  bool newBtnB = !digitalRead(PIN_BTN_B);

  // Any changes?
  if (newBtnB != btnB){
    btnB = newBtnB;
    return true;
  }

  return false;
}


/**
 * Update the Button C
 */
bool updateButtonC() {
  // Read the new values
  bool newBtnC = !digitalRead(PIN_BTN_C);

  // Any changes?
  if (newBtnC != btnC){
    btnC = newBtnC;
    return true;
  }

  return false;
}


/**
 * Update the Select Button
 */
bool updateButtonSelect() {
  // Read the new values
  bool newBtnSelect = !digitalRead(PIN_BTN_SELECT);

  // Any changes?
  if (newBtnSelect != btnSelect){
    btnSelect = newBtnSelect;
    return true;
  }

  return false;
}


/**
 * Update the toggle button value
 */
bool updateButtonToggle() {
  bool newBtnToggle = !digitalRead(PIN_TOGGLE);

  if (newBtnToggle != btnToggle) {
    btnToggle = newBtnToggle;
    return true;
  }

  return false;
}
