/*
  ==============================================================================

    Video.cpp
    Created: 1 Feb 2025 1:18:26pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Video.h"

Video::Video(juce::File f)
: file(f)
, UID(file.getFileNameWithoutExtension())
{
    loop = UID == "loop";
    
    videoComponent.onPlaybackStopped = [this] () {
        playbackStopped();
    };
    
    addAndMakeVisible(videoComponent);
}

Video::~Video()
{
    stopAndHide();
}

void Video::resized()
{
    videoComponent.setBounds(getLocalBounds());
}

void Video::startAndMakeVisible()
{
    videoComponent.load(file);
    setVisible(true);
    videoComponent.play();
}

void Video::stopAndHide()
{
    setVisible(false);
    videoComponent.closeVideo();
}

void Video::playbackStopped()
{
    if (loop && isVisible())
    {
        videoComponent.closeVideo();
        startAndMakeVisible();
    }
    else
    {
        sendChangeMessage();
    }
}
