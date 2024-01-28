#pragma once

#include <JuceHeader.h>

#include "../libpcsc/pcsc-cpp.hpp"

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
    void timerCallback() override;

private:
    void loadVideos();
    void cardInserted(pcsc_cpp::Reader reader);
    juce::String getNFCUID(pcsc_cpp::SmartCard::ptr card);
    void UIDtoVideo(juce::String UID);
    
    pcsc_cpp::CommandApdu UIDcommand{0xFF, 0xCA, 0x00, 0x00, {}, 0x00};
    
    juce::VideoComponent videoComp;
    juce::String currentUID = "";
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
