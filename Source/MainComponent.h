#pragma once

#include <JuceHeader.h>

#if USING_PCSC
#include "libpcsc/pcsc-cpp.hpp"
#elif USING_ARDUINO
#include "./Serial/SerialPortListMonitor.h"
#include "./Serial/SerialDevice.h"
#endif

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
#if USING_PCSC
    juce::String cardInserted(pcsc_cpp::Reader reader);
    juce::String getNFCUID(pcsc_cpp::SmartCard::ptr card);
    void readPCSC(juce::String& readerName, juce::String& UID);
    
    pcsc_cpp::CommandApdu UIDcommand{0xFF, 0xCA, 0x00, 0x00, {}, 0x00};
#elif USING_ARDUINO
    SerialPortListMonitor serialPortListMonitor;
    juce::String currentSerialDevice{""};
    void updateSelectedSerialDevice();
    std::unique_ptr<SerialDevice> serialDevice;
    void readArduino(juce::String& readerName, juce::String& UID);
#endif
    
    VideoHolder videoHolder;
    ReaderInfoDisplay readerInfoDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

