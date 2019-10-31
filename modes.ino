/**
 * @description
 * Switch to a new control mode
 */
void switchMode(int newMode) {
  mode = constrain(newMode, 1, MAX_MODES);
  setRadioAddress(mode);
  playMelodyNumber(mode);
}


/**
 * @description
 * Cycle through the availble modes
 */
void nextMode() {
  int newMode = mode + 1;
  if (newMode >= MAX_MODES) {
    newMode = 0;
  }
  switchMode(newMode);
}
