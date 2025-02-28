/*
  ==============================================================================

    VideoHolder.cpp
    Created: 30 Jan 2024 4:26:13pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#include "VideoHolder.h"
#include "../MainComponent.h"

VideoHolder::VideoHolder(MainComponent& mc) : mainComp(mc)
{
}

VideoHolder::~VideoHolder()
{
    currentVideo = nullptr;
}

void VideoHolder::resized()
{
    auto bounds = getLocalBounds();
    
    for (auto* v : videos)
        v->setBounds(bounds);
}

void VideoHolder::hideVideos()
{
    for (auto* v : videos)
        v->stopAndHide();
}

Video* VideoHolder::UIDtoVideo(juce::String UID)
{
    for (auto* v : videos)
    {
        if(v->UID == UID)
            return v;
    }
    
    if (UID == "fallback")  // We can't find fallback video... Uh oh.
    {
        mainComp.updateErrorMessage("Missing video called \"fallback\"", false);
        jassertfalse;
        return nullptr;
    }
    else  // returning fallback video
        return UIDtoVideo("fallback");
}

void VideoHolder::resumeLoop()
{
    setTagUID("loop");
}

void VideoHolder::loadVideos()
{
    juce::File desktop = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory);
    juce::File videoFolder = desktop.getChildFile("NFCVideos");
    int flag = juce::File::TypesOfFileToFind::findFiles;
    auto childFiles = videoFolder.findChildFiles(flag, false);
    
    // remove hidden files.
    for (auto& file : childFiles)
    {
        if (file.isHidden())
            childFiles.remove(&file);
    }

    // At least 2 videos needed in the videos folder
    if (childFiles.size() < 2)
    {
        mainComp.updateErrorMessage("At least 2 videos need to be in a folder called \"NFCVideos\"", true);
        jassertfalse;
    }

    for (auto f : childFiles)
    {        
        videos.add(new Video(f));
        videos.getLast()->addChangeListener(this);
    }
    
    for (auto* v : videos)
        addChildComponent(v);
    
    resized();
}

void VideoHolder::setTagUID(juce::String UID)
{
    if (UID == "-")
        return;
    
    if (currentVideo && UID == currentVideo->UID)
        return;
    
    Video* video = UIDtoVideo(UID);
    
    if (video == nullptr)
        return;
    
    if (video == currentVideo)
        return;
    
    if(currentVideo)
        currentVideo->stopAndHide();
    
    video->startAndMakeVisible();
    
    currentVideo = video;
}

void VideoHolder::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    // Receiving this from a video that has finished, and is not looped.
    Video* video = dynamic_cast<Video*>(source);
    if (video)
    {
        // Video is the current video, and it's finished. Resume looped video
        if (video == currentVideo)
        {
            if (currentVideo)
                currentVideo->stopAndHide();
            
            resumeLoop();
        }
    }
    
}

