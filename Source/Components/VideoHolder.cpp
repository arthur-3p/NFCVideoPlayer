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
    findFiles();
}

VideoHolder::~VideoHolder()
{
}

void VideoHolder::setTagUID(juce::String UID)
{
    if (UID == "-")
        return;
    
    if (currentVideo &&
        UID == currentUID &&
        UID != "loop")
        return;
    
    createAndStartNewVideo(UID);
}

void VideoHolder::findFiles()
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
        files.add(f);
    }
}

std::optional<juce::File> VideoHolder::fileFromUID(juce::String UID)
{
    for (auto f : files)
    {
        if(f.getFileNameWithoutExtension() == UID)
            return f;
    }
    
    if (UID == "fallback")  // We can't find fallback video... Uh oh.
    {
        mainComp.updateErrorMessage("Missing video called \"fallback\"", false);
        jassertfalse;
        return std::nullopt;
    }
    else
    {
        // returning fallback video
        return fileFromUID("fallback");
    }
    
}

void VideoHolder::removeCurrentVideo()
{
    if (currentVideo)
        removeChildComponent(currentVideo.get());
}

void VideoHolder::createNewVideo(juce::File file)
{
    currentVideo.reset(new FFmpegVideoComponent);
    currentVideo->setBounds(getLocalBounds());
    addAndMakeVisible(currentVideo.get());
    
    currentVideo->onPlaybackStopped = [this] { playbackStopped(); };
    currentVideo->onErrorOccurred = [this] (juce::String errorText) { errorOccured(errorText); };
    currentVideo->onVideoAborted = [this]  { videoAborted(); };
    currentVideo->load(file);
}

void VideoHolder::createAndStartNewVideo(juce::String UID)
{
    std::optional<juce::File> file = fileFromUID(UID);
    if (file.has_value())
    {
        removeCurrentVideo();
        createNewVideo(file.value());
        currentVideo->play();
        currentUID = UID;
    }
}

void VideoHolder::resumeLoop()
{
    setTagUID("loop");
}

void VideoHolder::playbackStopped()
{
    resumeLoop();
}

void VideoHolder::errorOccured(juce::String errorString)
{
    juce::MessageManager::callAsync([this, errorString] { mainComp.updateErrorMessage("VideoComponent Error: " + errorString, false); });
    DBG("errorOccured from video component...");
}

void VideoHolder::videoAborted()
{
    DBG("VideoHolder videoAborted");
    resumeLoop();
}
