/**
 * dJPoida's Universal Controller for Remote Applications
 * 
 * 2x Main Buttons (A / B Buttons)
 * 1x Joystick (X / Y Axis + C Button)
 * 1x D-Pad (Up / Down / Left / Right Buttons)
 * 1x Toggle Switch (D)
 * 1x Select Button (S)
 * 1x Potentiometer (Z)
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define APP_NAME "dJPoida's Universal Controller"
#define VERSION "v1.0"

// How many modes do we have
// (both `tone` and `transmit` units need to be updated to accommodate this value)
#define MAX_MODES 4

// Joystick Pins
#define PIN_JOY_X A7
#define PIN_JOY_Y A6
#define PIN_BTN_C 2

// Toggle Button Pin
#define PIN_TOGGLE 7

// AB Button Pins
#define PIN_BTN_A 5
#define PIN_BTN_B 4

// D-Pad Button Pins
#define PIN_BTN_D_UP A5
#define PIN_BTN_D_DOWN A3
#define PIN_BTN_D_LEFT A4
#define PIN_BTN_D_RIGHT A2

// Potentiometer Pin
#define PIN_POT_Z A1

// Select Button Pin
#define PIN_BTN_SELECT 3

// Other Peripheral Pins
#define PIN_SPEAKER 6
#define PIN_LED 10
#define PIN_BATTERY_LEVEL A0

// Radio Control
#define PIN_RF_CE 8
#define PIN_RF_CSN 9

// How much of the joystick shouldn't register
#define JOYSTICK_DEAD_ZONE 20

// What reading represents the min and max battery level voltages (give or take 3.5v = 1023 * 3.5 / 5 = 716)
#define BATTERY_MIN 700
#define BATTERY_MAX 850

// What level of the battery will trigger a flashing LED
#define LOW_BATTERY_PERCENT 10

// RF Transmit
#define DATA_PACKET_SIZE 18
#define RADIO_DATA_RATE RF24_1MBPS
#define RADIO_POWER RF24_PA_HIGH

// RF Heartbeat - how often to broadcast the control state even if nothing has changed
#define HEARTBEAT_INTERVAL 500 

// Comment out the lines below to negate their values for incremental building to prevent problems with code
// #define INVERT_JOYSTICK_Y
#define INVERT_JOYSTICK_X
// #define DEBUG_SERIAL

// State values
int joyX = 127;
int joyY = 127;
bool btnA = false;
bool btnB = false;
bool btnC = false;
bool btnToggle = false;
bool btnSelect = false;
bool dPadUp = false;
bool dPadDown = false;
bool dPadLeft = false;
bool dPadRight = false;
int potZ = 0;
int batteryLevel = 99;
int mode = 1;

// time delay params
long lastBatteryReadTime = 0;
long lastStateTransmit = 0;

/**
 * Setup
 */
void setup() {
  // Initialise the Serial Debug
  #ifdef DEBUG_SERIAL
  initSerial();
  #endif

  // Initialise the Joystick Inputs
  pinMode(PIN_JOY_X, INPUT);
  pinMode(PIN_JOY_Y, INPUT);

  // Initialise the Toggle Inputs
  pinMode(PIN_TOGGLE, INPUT_PULLUP);

  // Initilase the Button Inputs
  pinMode(PIN_BTN_A, INPUT_PULLUP);
  pinMode(PIN_BTN_B, INPUT_PULLUP);
  pinMode(PIN_BTN_C, INPUT_PULLUP); // Joystick Push In
  pinMode(PIN_BTN_SELECT, INPUT_PULLUP);

  // Initialise the D-Pad buttons
  pinMode(PIN_BTN_D_UP, INPUT_PULLUP);
  pinMode(PIN_BTN_D_DOWN, INPUT_PULLUP);
  pinMode(PIN_BTN_D_LEFT, INPUT_PULLUP);
  pinMode(PIN_BTN_D_RIGHT, INPUT_PULLUP);

  // Initialise the Potentiometer
  pinMode(PIN_POT_Z, INPUT);

  // Initialise the Battery Level Check Pin
  pinMode(PIN_BATTERY_LEVEL, INPUT);

  // Init the LED
  initLED();
  setLedMode_normal();
  updateLED(0);

  // Indicate what mode the controller is in
  playMelodyNumber(mode);

  // Print out some column headers so we know what the hell the data points are
  #ifdef DEBUG_SERIAL
  printInputDebugColumnHeaders();
  #endif

  // Init the Radio
  initRadio();
}


/**
 * Main Loop
 */
void loop() {
  long currentMillis = millis();

  bool controlStateChanged = false;
  controlStateChanged |= updateJoystick();
  controlStateChanged |= updateButtonToggle();
  controlStateChanged |= updateButtonA();
  controlStateChanged |= updateButtonB();
  controlStateChanged |= updateButtonC();
  controlStateChanged |= updateDPad();
  controlStateChanged |= updatePot();
  
  if (controlStateChanged) {
    // Transmit the control state
    transmitControlState();
    
    #ifdef DEBUG_SERIAL
    printInputDebug();
    #endif
  } else {
    // Heartbeat control state
    if (lastStateTransmit + HEARTBEAT_INTERVAL < currentMillis) {
      transmitControlState();
    }
  }

  // Check the Battery Level
  if (updateBatteryLevel(currentMillis)) {
    if (batteryLevel < LOW_BATTERY_PERCENT) {
      setLedMode_lowBattery();
    } else {
      setLedMode_normal();
    }
  }

  // Cycle through modes
  if (updateButtonSelect()) {
    if (btnSelect) {
      nextMode();
    }
  }

  // Update the LED
  updateLED(currentMillis);
}
