/*
  ==============================================================================

    VideoHolder.h
    Created: 30 Jan 2024 4:26:13pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../ffmpeg/FFmpegVideoComponent.h"

class  MainComponent;

class VideoHolder
: public juce::Component
{
public:
    VideoHolder(MainComponent& mc);
    ~VideoHolder();
    
    void setTagUID(juce::String UID);
    
private:
    MainComponent& mainComp;
    
    std::unique_ptr<FFmpegVideoComponent> currentVideo = nullptr;
    juce::Array<juce::File> files;
    juce::String currentUID;
    
    void findFiles();
    std::optional<juce::File> fileFromUID(juce::String UID);
    void removeCurrentVideo();
    void createNewVideo(juce::File file);
    void createAndStartNewVideo(juce::String UID);
    void resumeLoop();
    void playbackStopped();
    void errorOccured(juce::String);
    void videoAborted();
};
