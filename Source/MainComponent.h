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
    
    void updateErrorMessage(juce::String, bool isCritical);

private:
    int openDevice();
    serialib serial;
    void readSerial(juce::String& readerName, juce::String& UID);
    
    VideoHolder videoHolder;
    ReaderInfoDisplay readerInfoDisplay;
    
    juce::Label errorLabel;
    int showErrorCounter = 0;
    bool errorIsCritical = false;
    
    juce::String serialOpenErrorMessage(int errorCode);
    juce::String serialReadErrorMessage(int errorCode);
    
    juce::TextButton quitButton;
    juce::Label quitLabel;
    
    bool quitRequested = false;
    
    void requestQuit()
    {
        showErrorMessage(false);
        
        quitRequested = true;
        quitLabel.setVisible(true);
    }
    
    void showErrorMessage(bool show)
    {
        errorLabel.setVisible(show);
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

