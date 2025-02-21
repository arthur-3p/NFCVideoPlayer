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
    
    void showError(juce::String, bool isCritical);

private:
    int openDevice();
    serialib serial;
    void readSerial(juce::String& readerName, juce::String& UID);
    
    VideoHolder videoHolder;
    ReaderInfoDisplay readerInfoDisplay;
    
    juce::Label errorLabel;
    bool showingError = false;
    int showErrorCounter = 0;
    bool errorIsCritical = false;
    
    juce::String serialOpenErrorMessage(int errorCode);
    juce::String serialReadErrorMessage(int errorCode);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

