/*
  ==============================================================================

    ReaderInfoDisplay.h
    Created: 30 Jan 2024 2:37:37pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ReaderInfoDisplay : public juce::Component
{
public:
    ReaderInfoDisplay();
    
    void resized() override;
    
    void updateInfo(juce::String name, juce::String tagUID);
    
private:
    juce::String readerName, tagUID;
    juce::Label readerLabel, readerNameLabel, tagLabel, tagUIDLabel;
};
