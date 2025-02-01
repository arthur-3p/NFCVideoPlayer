/*
  ==============================================================================

    VideoHolder.h
    Created: 30 Jan 2024 4:26:13pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Video.h"

class VideoHolder
: public juce::Component
, public juce::ChangeListener
{
public:
    VideoHolder();
    
    void resized() override;
    
    void setTagUID(juce::String UID);
    
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    
private:
    void loadVideos();
    void stopVideosPlaying();
    void hideVideos();
    Video* UIDtoVideo(juce::String UID);
    void resumeLoop();
    
    juce::OwnedArray<Video> videos;
    Video* currentVideo = nullptr;
};
