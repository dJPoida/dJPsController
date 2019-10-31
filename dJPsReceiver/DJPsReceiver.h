/**
 * dJP's Controller Receiver Library
 * Created by dJPoida (aka Peter Eldred)
 * 
 * For use with dJP's Controller
 */

#ifndef DJPsReceiver_h
#define DJPsReceiver_h

#include "Arduino.h"
#include <RF24.h>

// Data rate needs to match that in the dJPs Controller Transmit Code
#define RADIO_DATA_RATE RF24_1MBPS

// The data packet size that matches that of the transmitted packet
#define DATA_PACKET_SIZE 18

// How many milliseconds can elapse between receieving an instruction from the
// controller before declaring a disconnection.
// Typically the controller has a heartbeat of 500ms.
#define HEARTBEAT_TOLERANCE 750

typedef void (*byteValueChangedFunction)(byte);
typedef void (*boolValueChangedFunction)(bool);
typedef void (*generalEventFunction)();

class DJPsReceiver
{
  public:
    DJPsReceiver(byte pin_ce, byte pin_csn, byte channel);

    void begin();
    void run();

    float version = 1.0;

    bool connected = 0;

    byte batteryLevel = 99;
    bool btnToggle = 0;
    bool btnA = 0;
    bool btnB = 0;
    bool btnC = 0;
    byte joyX = 127;
    byte joyY = 127;
    byte potZ = 0;
    bool dPadUp = 0;
    bool dPadDown = 0;
    bool dPadLeft = 0;
    bool dPadRight = 0;
     
    byteValueChangedFunction onBatteryLevelChange;
    boolValueChangedFunction onBtnToggleChange;
    boolValueChangedFunction onBtnAChange;
    boolValueChangedFunction onBtnBChange;
    boolValueChangedFunction onBtnCChange;
    byteValueChangedFunction onJoyXChange;
    byteValueChangedFunction onJoyYChange;
    byteValueChangedFunction onPotZChange;
    boolValueChangedFunction onDPadUpChange;
    boolValueChangedFunction onDPadDownChange;
    boolValueChangedFunction onDPadLeftChange;
    boolValueChangedFunction onDPadRightChange;

    generalEventFunction onConnected;
    generalEventFunction onDisconnected;
    
  private:
    byte _pin_ce;
    byte _pin_csn;
    byte _channel;

    long _lastMessageRceivedMillis;

    char _dataReceived[DATA_PACKET_SIZE];

    void _setControlData_batteryLevel(byte value);
    void _setControlData_btnToggle(bool value);
    void _setControlData_btnA(bool value);
    void _setControlData_btnB(bool value);
    void _setControlData_btnC(bool value);
    void _setControlData_joyX(byte value);
    void _setControlData_joyY(byte value);
    void _setControlData_potZ(byte value);
    void _setControlData_dPadUp(bool value);
    void _setControlData_dPadDown(bool value);
    void _setControlData_dPadLeft(bool value);
    void _setControlData_dPadRight(bool value);

    void _setConnected(bool value);
    void _checkConnected(long currentMillis);
  
    RF24 *_radio;
};

#endif
