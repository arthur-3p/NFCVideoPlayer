#pragma once

#include <JuceHeader.h>

#include "../serialib/lib/serialib.h"
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
    char openDevice();
    serialib serial;
//    juce::String currentSerialDevice{""};
    void updateSelectedSerialDevice();
//    std::unique_ptr<SerialDevice> serialDevice;
    void readSerial(juce::String& readerName, juce::String& UID);
    
    VideoHolder videoHolder;
    ReaderInfoDisplay readerInfoDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

