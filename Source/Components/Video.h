/*
  ==============================================================================

    Video.h
    Created: 1 Feb 2025 1:18:26pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../ffmpeg/FFmpegVideoComponent.h"
//==============================================================================
/*
*/
class Video  : public juce::Component, public juce::ChangeBroadcaster
{
public:
    Video(juce::File f);
    ~Video();
        
    void resized() override;
    void startAndMakeVisible();
    void stopAndHide();
    void playbackStopped();
        
    juce::File file;
    FFmpegVideoComponent videoComponent;
    juce::String UID;
    bool loop = false;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Video)
};
