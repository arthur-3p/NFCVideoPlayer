#pragma once

#include "SerialPortListMonitor.h"

// NOTE: This class could be named for the name of the thing you are connecting to: LEDContllerDevice, DrumMachineDevice, SolarMonitorDevice, etc
class SerialDevice : private juce::ChangeListener
{
public:
    SerialDevice (juce::String newSerialPortName);
    ~SerialDevice ();

    juce::String getCurrentUID();
    juce::String getSerialPortName() { return serialPortName; }
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;
    
    bool hasUpdated()
    {
        bool state = updated.load();
        updated.store(false);
        return state;
    }
    
private:
    juce::String serialPortName;
    std::unique_ptr<SerialPort> serialPort;
    std::unique_ptr<SerialPortInputStream> serialPortInput;
    std::unique_ptr<SerialPortOutputStream> serialPortOutput;

    bool openSerialPort (void);
    void closeSerialPort (void);

    std::atomic<bool> updated;
    juce::CriticalSection cs;
    juce::String uid = "-";
};
