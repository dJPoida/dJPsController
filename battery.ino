/**
 * @description
 * Update the Battery Level (0 - 99)
 * 
 * TODO: At some point keep a running list of battery levels and average the list instead of
 *       simply taking the average of the new and previous value
 */
bool updateBatteryLevel(long currentMillis) {
  // Only update the battery level once every 1 second
  if ((lastBatteryReadTime + 1000) > currentMillis) {
    return false;
  }

  lastBatteryReadTime = currentMillis;

  // Read the new value
  int newBatteryLevel = constrain(map(analogRead(PIN_BATTERY_LEVEL), BATTERY_MIN, BATTERY_MAX, 0, 99), 0, 99);
  newBatteryLevel = (batteryLevel + newBatteryLevel) / 2;
  
  // Any changes?
  if (newBatteryLevel != batteryLevel) {
    batteryLevel = newBatteryLevel;
    return true;
  }
  
  return false;
}
