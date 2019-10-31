/**
 * Update the joystick values
 */
bool updateJoystick() {
  int newJoyX = round(analogRead(PIN_JOY_X) / 4 - 128);
  int newJoyY = round(analogRead(PIN_JOY_Y) / 4 - 128);

  #ifdef INVERT_JOYSTICK_X
  newJoyX = newJoyX * -1;
  #endif

  #ifdef INVERT_JOYSTICK_Y
  newJoyY = newJoyY * -1;
  #endif

  // Compensate for the dead zone;
  if ((newJoyX < JOYSTICK_DEAD_ZONE) && (-JOYSTICK_DEAD_ZONE < newJoyX)) {
    newJoyX = 0;
  }
  if ((newJoyY < JOYSTICK_DEAD_ZONE) && (-JOYSTICK_DEAD_ZONE < newJoyY)) {
    newJoyY = 0;
  }

  // Account for the dead zone
  if (newJoyX < 0) {
    newJoyX = map(newJoyX, -JOYSTICK_DEAD_ZONE, -127, -1, -255);
  } else if (newJoyX > 0) {
    newJoyX = map(newJoyX, JOYSTICK_DEAD_ZONE, 127, 1, 255);
  }

  if (newJoyY < 0) {
    newJoyY = map(newJoyY, -JOYSTICK_DEAD_ZONE, -127, -1, -255);
  } else if (newJoyY > 0) {
    newJoyY = map(newJoyY, JOYSTICK_DEAD_ZONE, 127, 1, 255);
  }

  newJoyX = constrain(map(newJoyX, -255, 255, 0, 255), 0, 255);
  newJoyY = constrain(map(newJoyY, -255, 255, 0, 255), 0, 255);

  // Any Changes?
  if (
    (newJoyX != joyX) ||
    (newJoyY != joyY)
  ) {
    joyX = newJoyX;
    joyY = newJoyY;
    return true;
  }

  return false;
}
