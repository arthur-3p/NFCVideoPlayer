#pragma once

#include <JuceHeader.h>
#include "libpcsc/pcsc-cpp.hpp"
#include "./Serial/SerialPortListMonitor.h"
#include "./Serial/SerialDevice.h"

#include "Components/ReaderInfoDisplay.h"
#include "Components/VideoHolder.h"

//==============================================================================
class MainComponent
: public juce::Component
, public juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //==============================================================================
    bool keyPressed(const juce::KeyPress &key) override;
    
    //==============================================================================
    void timerCallback() override;

private:
    juce::String cardInserted(pcsc_cpp::Reader reader);
    juce::String getNFCUID(pcsc_cpp::SmartCard::ptr card);
    
    void readPCSC(juce::String& readerName, juce::String& UID);
    void readArduino(juce::String& readerName, juce::String& UID);
    
    SerialPortListMonitor serialPortListMonitor;
    juce::String currentSerialDevice{""};
    void updateSelectedSerialDevice();

    std::unique_ptr<SerialDevice> serialDevice;
    
    pcsc_cpp::CommandApdu UIDcommand{0xFF, 0xCA, 0x00, 0x00, {}, 0x00};
    
    VideoHolder videoHolder;
    ReaderInfoDisplay readerInfoDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
