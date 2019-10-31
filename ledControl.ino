// Default State - steady power on.
#define LED_STATE_NORMAL 0

// Flashing Low Battery light
#define LED_STATE_LOW_BATTERY 1

// State Variables
int ledState = LED_STATE_NORMAL;
long lastLEDUpdate = 0;
bool ledOn = false;


/**
 * @description
 * Initialise the LED
 */
void initLED() {
  pinMode(PIN_LED, OUTPUT);
}


/**
 * Update the LED
 * 
 * @param {long} currentMillis the number of milliseconds since start up
 */
void updateLED(long currentMillis) {
  switch (ledState) {
    case LED_STATE_LOW_BATTERY:
      if (lastLEDUpdate + 1000 < currentMillis) {
        lastLEDUpdate = currentMillis;
        ledOn = !ledOn;
        digitalWrite(PIN_LED, ledOn);
      }
      break;
    
    case LED_STATE_NORMAL:
    default:
      ledOn = true;
      digitalWrite(PIN_LED, ledOn);
      break;
  }
}


/**
 * @description
 * Set the LED Mode to LED_STATE_NORMAL
 */
void setLedMode_normal() {
  ledState = LED_STATE_NORMAL;
}


/**
 * @description
 * Set the LED Mode to LED_STATE_NOT_CONNECTED
 */
void setLedMode_lowBattery() {
  ledState = LED_STATE_LOW_BATTERY;
}
