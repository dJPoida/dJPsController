/**
 * @description
 * Update the Pot
 */
bool updatePot() {
  // Read the new value
  int newPotZ = map(analogRead(PIN_POT_Z), 0, 1023, 0, 99);

  // Any changes?
  if (newPotZ != potZ) {
    potZ = newPotZ;
    return true;
  }

  return false;
}
