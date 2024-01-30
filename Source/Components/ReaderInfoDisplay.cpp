/*
  ==============================================================================

    ReaderInfoDisplay.cpp
    Created: 30 Jan 2024 2:37:37pm
    Author:  Arthur Wilson

  ==============================================================================
*/

#include "ReaderInfoDisplay.h"

ReaderInfoDisplay::ReaderInfoDisplay()
{
    readerLabel.setText("Reader: ", juce::dontSendNotification);
    addAndMakeVisible(readerLabel);
    
    readerNameLabel.setText("-", juce::dontSendNotification);
    addAndMakeVisible(readerNameLabel);
    
    tagLabel.setText("Tag: ", juce::dontSendNotification);
    addAndMakeVisible(tagLabel);
    
    tagUIDLabel.setText("-", juce::dontSendNotification);
    addAndMakeVisible(tagUIDLabel);
    
}

void ReaderInfoDisplay::resized()
{
    auto bounds = getLocalBounds();
    
    auto readerInfoBounds = bounds.removeFromTop(20);
    readerLabel.setBounds(readerInfoBounds.removeFromLeft(100));
    readerNameLabel.setBounds(readerInfoBounds);
    
    auto tagInfoBounds = bounds.removeFromTop(20);
    tagLabel.setBounds(tagInfoBounds.removeFromLeft(100));
    tagUIDLabel.setBounds(tagInfoBounds);
}

void ReaderInfoDisplay::updateInfo(juce::String name, juce::String tagUID)
{
    readerNameLabel.setText(name, juce::dontSendNotification);
    tagUIDLabel.setText(tagUID, juce::dontSendNotification);
}
