#include "DJPsReceiver.h"

/**
 * This is the test program for dJPsReceiver library
 * 
 * To use this code (or to update after code changes) copy the .cpp and .h into
 * your libraries subdirectory of your sketchbook
 */

#define PIN_CE 9
#define PIN_CSN 10
#define CHANNEL 1

// Create the receiver
DJPsReceiver receiver(PIN_CE, PIN_CSN, CHANNEL);

void setup() {
  Serial.begin(115200);
  Serial.println("dJPs Receiver Test App");

  receiver.onBatteryLevelChange = batteryLevelChanged;
  receiver.onBtnToggleChange = btnToggleChanged;
  receiver.onBtnAChange = btnAChanged;
  receiver.onBtnBChange = btnBChanged;
  receiver.onBtnCChange = btnCChanged;
  receiver.onDPadUpChange = dPadUpChanged;
  receiver.onDPadDownChange = dPadDownChanged;
  receiver.onDPadLeftChange = dPadLeftChanged;
  receiver.onDPadRightChange = dPadRightChanged;
  receiver.onJoyXChange = joyXChanged;
  receiver.onJoyYChange = joyYChanged;
  receiver.onPotZChange = potZChanged;
  receiver.onConnected = onConnected;
  receiver.onDisconnected = onDisconnected;
  receiver.begin();

  Serial.println("initialised.");
}

void loop() {
  // Check to see if the receiver has noticed any changes in the controller
  receiver.run();
}

void batteryLevelChanged(byte value) {
  Serial.print("Battery Level: ");
  Serial.println(value);
}

void btnAChanged(bool value) {
  Serial.print("A: ");
  Serial.println(value);
}

void btnBChanged(bool value) {
  Serial.print("B: ");
  Serial.println(value);
}

void btnCChanged(bool value) {
  Serial.print("C: ");
  Serial.println(value);
}

void btnToggleChanged(bool value) {
  Serial.print("Toggle: ");
  Serial.println(value);
}

void dPadUpChanged(bool value) {
  Serial.print("dPadUp: ");
  Serial.println(value);
}

void dPadDownChanged(bool value) {
  Serial.print("dPadDown: ");
  Serial.println(value);
}

void dPadLeftChanged(bool value) {
  Serial.print("dPadLeft: ");
  Serial.println(value);
}

void dPadRightChanged(bool value) {
  Serial.print("dPadRight: ");
  Serial.println(value);
}

void joyXChanged(byte value) {
  Serial.print("joyX: ");
  Serial.println(value);
}

void joyYChanged(byte value) {
  Serial.print("joyY: ");
  Serial.println(value);
}

void potZChanged(byte value) {
  Serial.print("potZ: ");
  Serial.println(value);
}

void onConnected() {
  Serial.print("Receiver Connected on channel");
  Serial.print(CHANNEL);
  Serial.println(".");
}

void onDisconnected() {
  Serial.println("!! Connection to the Controller Lost !!");
}
