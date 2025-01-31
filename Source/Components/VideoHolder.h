/*
  ==============================================================================

    VideoHolder.h
    Created: 30 Jan 2024 4:26:13pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Video : public juce::Component, public juce::ChangeBroadcaster
{
public:
    
    Video(juce::File f)
    : file(f)
    , videoComponent(false)
    , UID(file.getFileNameWithoutExtension())
    {
        loop = UID == "loop";
        
        videoComponent.onPlaybackStopped = [this] () {
            playbackStopped();
        };
        
        addAndMakeVisible(videoComponent);
    }
    
    ~Video()
    {
        stopAndHide();
    }
    
    void resized() override
    {
        videoComponent.setBounds(getLocalBounds());
    }
    
    void startAndMakeVisible()
    {
        videoComponent.load(file);
        setVisible(true);
        videoComponent.play();
    }
    
    void stopAndHide()
    {
        setVisible(false);
        videoComponent.closeVideo();
    }
    
    void playbackStopped()
    {
        if (loop && isVisible())
        {
            videoComponent.setPlayPosition(0.0f);
            videoComponent.play();
        }
        else
        {
            sendChangeMessage();
        }
    }
    
    juce::File file;
    juce::VideoComponent videoComponent;
    juce::String UID;
    bool loop = false;
};

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
