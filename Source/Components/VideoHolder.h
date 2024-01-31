/*
  ==============================================================================

    VideoHolder.h
    Created: 30 Jan 2024 4:26:13pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VideoHolder
: public juce::Component
{
public:
    VideoHolder();
    
    void resized() override;
    
    void setTagUID(juce::String UID);
    
private:
    void loadVideos();
    void stopVideosPlaying();
    void hideVideos();
    juce::VideoComponent* UIDtoVideo(juce::String UID);
    
    juce::OwnedArray<juce::VideoComponent> videoComponents;
    juce::String currentUID = "-";
};
