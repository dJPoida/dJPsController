/**
 * dJP's Controller Receiver Library
 * Created by dJPoida (aka Peter Eldred)
 * 
 * For use with dJP's Controller
 */

#include "Arduino.h"
#include "DJPsReceiver.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


/**
 * Constructor
 */
DJPsReceiver::DJPsReceiver(byte pin_ce, byte pin_csn, byte channel)
{
  _pin_ce = pin_ce;
  _pin_csn = pin_csn;
  _channel = channel;
  _lastMessageRceivedMillis = 0;

  _radio = new RF24(_pin_ce, _pin_csn);  
}


/**
 * Call this from your setup function to begin listening for dJPs controller
 */
void DJPsReceiver::begin() {
  const byte address[5] = {'d','J','P','0',_channel};
  _radio->begin();
  _radio->setDataRate(RADIO_DATA_RATE);
  _radio->openReadingPipe(1, address);
  _radio->startListening();  
}


/**
 * Call this from your loop to check the RF24's receive buffer and
 * Check for updates to the controller state
 */
void DJPsReceiver::run() {
  long currentMillis = millis();
  
  // Check to see if there is data on the radio receiver buffer
  if (_radio->available()) {
    // Let's keep track of the message receipt so we don't declare the controller disconnected
    _lastMessageRceivedMillis = currentMillis;
    
    _radio->read(&_dataReceived, DATA_PACKET_SIZE);

    // Debug Only
    // Serial.print("Data received ");
    // for (byte i = 0; i < DATA_PACKET_SIZE; i++) {
    //  Serial.print(_dataReceived[i]);
    // }
    // Serial.println("");

    // Example Receipt:
    // PPTABCXXXYYYZZUNLR (18 Bytes)
    // 990000127127000000 (18 bytes)

    // Announce a connection
    _setConnected(1);

    // Parse and action the string of data
    _setControlData_batteryLevel(((byte)_dataReceived[0]-48) * 10 + ((byte)_dataReceived[1]-48));
    _setControlData_btnToggle((byte)_dataReceived[2]-48);
    _setControlData_btnA((byte)_dataReceived[3]-48);
    _setControlData_btnB((byte)_dataReceived[4]-48);
    _setControlData_btnC((byte)_dataReceived[5]-48);
    _setControlData_joyX(((byte)_dataReceived[6]-48)*100 + ((byte)_dataReceived[7]-48)*10 + ((byte)_dataReceived[8]-48));
    _setControlData_joyY(((byte)_dataReceived[9]-48)*100 + ((byte)_dataReceived[10]-48)*10 + ((byte)_dataReceived[11]-48));
    _setControlData_potZ(((byte)_dataReceived[12]-48)*10 + ((byte)_dataReceived[13]-48));
    _setControlData_dPadUp((byte)_dataReceived[14]-48);
    _setControlData_dPadDown((byte)_dataReceived[15]-48);
    _setControlData_dPadLeft((byte)_dataReceived[16]-48);
    _setControlData_dPadRight((byte)_dataReceived[17]-48);
  } else {
    // Nothing in the receiver buffer? Let's check to see if we've been disconnected
    _checkConnected(currentMillis);
  }
}


/**
 * Set the battery level
 */
void DJPsReceiver::_setControlData_batteryLevel(byte value) {
  if (batteryLevel != value) {
    batteryLevel = value;
    if (onBatteryLevelChange) {
      onBatteryLevelChange(value);
    }
  }
}


/**
 * Set the Toggle Button Value
 */
void DJPsReceiver::_setControlData_btnToggle(bool value) {
  // TODO: debounce
  if (btnToggle != value) {
    btnToggle = value;
    if (onBtnToggleChange) {
      onBtnToggleChange(value);
    }
  }
}


/**
 * Set the Button A Value
 */
void DJPsReceiver::_setControlData_btnA(bool value) {
  // TODO: debounce
  if (btnA != value) {
    btnA = value;
    if (onBtnAChange) {
      onBtnAChange(value);
    }
  }
}


/**
 * Set the Button B Value
 */
void DJPsReceiver::_setControlData_btnB(bool value) {
  // TODO: debounce
  if (btnB != value) {
    btnB = value;
    if (onBtnBChange) {
      onBtnBChange(value);
    }
  }
}


/**
 * Set the Button C Value
 */
void DJPsReceiver::_setControlData_btnC(bool value) {
  // TODO: debounce
  if (btnC != value) {
    btnC = value;
    if (onBtnCChange) {
      onBtnCChange(value);
    }
  }
}


/**
 * Set the Joystick X value
 */
void DJPsReceiver::_setControlData_joyX(byte value) {
  // TODO: debounce
  if (joyX != value) {
    joyX = value;
    if (onJoyXChange) {
      onJoyXChange(value);
    }
  }
}


/**
 * Set the Joystick Y value
 */
void DJPsReceiver::_setControlData_joyY(byte value) {
  // TODO: debounce
  if (joyY != value) {
    joyY = value;
    if (onJoyYChange) {
      onJoyYChange(value);
    }
  }
}


/**
 * Set the Potentiometer Z value
 */
void DJPsReceiver::_setControlData_potZ(byte value) {
  // TODO: debounce
  if (potZ != value) {
    potZ = value;
    if (onPotZChange) {
      onPotZChange(value);
    }
  }
}


/**
 * Set the DPad Up value
 */
void DJPsReceiver::_setControlData_dPadUp(bool value) {
  // TODO: debounce
  if (dPadUp != value) {
    dPadUp = value;
    if (onDPadUpChange) {
      onDPadUpChange(value);
    }
  }
}


/**
 * Set the DPad Down Value
 */
void DJPsReceiver::_setControlData_dPadDown(bool value) {
  // TODO: debounce
  if (dPadDown != value) {
    dPadDown = value;
    if (onDPadDownChange) {
      onDPadDownChange(value);
    }
  }
}


/**
 * Set the DPad Left Value
 */
void DJPsReceiver::_setControlData_dPadLeft(bool value) {
  // TODO: debounce
  if (dPadLeft != value) {
    dPadLeft = value;
    if (onDPadLeftChange) {
      onDPadLeftChange(value);
    }
  }
}


/**
 * Set the DPad Right value
 */
void DJPsReceiver::_setControlData_dPadRight(bool value) {
  // TODO: debounce
  if (dPadRight != value) {
    dPadRight = value;
    if (onDPadRightChange) {
      onDPadRightChange(value);
    }
  }
}


/**
 * Fired when any message (including a heartbeat) is received.
 * If the previous connection state is false, the onConnected
 * event will fire.
 */
void DJPsReceiver::_setConnected(bool value) {
  if (value != connected) {
    connected = value;
    if (connected && onConnected) {
      onConnected();
    } else if (onDisconnected) {
      onDisconnected();
    }
  }
}


/**
 * Fired on every run loop to check that the last message received is
 * inside the threshold for declaring the receiver "disconnected".
 */
void DJPsReceiver::_checkConnected(long currentMillis) {
  if (currentMillis > (_lastMessageRceivedMillis + HEARTBEAT_TOLERANCE)) {
    // Exceeded the HEARTBEAT_TOLERANCE millisecond value since last contact with the controller
    _setConnected(0);
  }
}
