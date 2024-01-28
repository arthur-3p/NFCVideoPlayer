#pragma once

#include <JuceHeader.h>

#include "../libpcsc/pcsc-cpp.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

private:
    void cardInserted(pcsc_cpp::Reader reader);
    juce::String getNFCUID(pcsc_cpp::SmartCard::ptr card);
    void UIDtoVideo(juce::String UID);
    
    juce::VideoComponent videoComp;
    juce::String currentUID = "";
    
    pcsc_cpp::CommandApdu UIDcommand{0xFF, 0xCA, 0x00, 0x00, {}, 0x00};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
