/*
  ==============================================================================

    VideoHolder.cpp
    Created: 30 Jan 2024 4:26:13pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#include "VideoHolder.h"

VideoHolder::VideoHolder()
{
    loadVideos();
    
    for (auto v : videoComponents)
        addChildComponent(v);
}

void VideoHolder::resized()
{
    auto bounds = getLocalBounds();
    
    for (auto v : videoComponents)
        v->setBounds(bounds);
}

void VideoHolder::stopVideosPlaying()
{
    for (auto v : videoComponents)
    {
        v->stop();
    }
}

void VideoHolder::hideVideos()
{
    for (auto v : videoComponents)
        v->setVisible(false);
}

juce::VideoComponent* VideoHolder::UIDtoVideo(juce::String UID)
{
    if (UID == "190e9f9f")
        return videoComponents[0];
    else
        return videoComponents[1];
}

void VideoHolder::loadVideos()
{
    juce::File desktop = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory);
    juce::File videoFolder = desktop.getChildFile("NFCVideos");
    int flag = juce::File::TypesOfFileToFind::findFiles;
    auto childFiles = videoFolder.findChildFiles(flag, false);

    // At least 2 videos needed in the videos folder
    jassert(childFiles.size() >= 2);

    for (auto f : childFiles)
    {
        juce::VideoComponent* newVideoComponent = new juce::VideoComponent(false);
        newVideoComponent->load(f);
        videoComponents.add(std::move(newVideoComponent));
    }
}

void VideoHolder::setTagUID(juce::String UID)
{
    if (UID == currentUID || UID == "-")
        return;
    
    stopVideosPlaying();
    hideVideos();
    
    currentUID = UID;
    
    juce::VideoComponent* video = UIDtoVideo(currentUID);
    video->setPlayPosition(0.0f);
    video->setVisible(true);
    video->play();
}

