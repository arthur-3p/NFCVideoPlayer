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
    
    for (auto* v : videos)
        addChildComponent(v);
    
//    resumeLoop();
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

    // At least 2 videos needed in the videos folder
    jassert(childFiles.size() >= 2);

    for (auto f : childFiles)
    {
        if (f.isHidden())
            continue;
        
        videos.add(new Video(f));
        videos.getLast()->addChangeListener(this);
    }
}

void VideoHolder::setTagUID(juce::String UID)
{
    if (UID == "-")
        return;
    
    if (currentVideo && UID == currentVideo->UID)
        return;
    
    Video* video = UIDtoVideo(UID);
    
    if (video == currentVideo)
        return;
    
    if (video == nullptr)
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

