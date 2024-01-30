#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
: videoComp(true)
{
    loadVideos();
    
    addAndMakeVisible(readerInfoDisplay);
    addAndMakeVisible(videoComp);
    
    startTimer(100);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    
    readerInfoDisplay.setBounds(bounds.removeFromTop(40));
    videoComp.setBounds(bounds);
}

//==============================================================================
void MainComponent::timerCallback()
{
    auto readers = pcsc_cpp::listReaders();
    juce::String readerName = "-";
    juce::String tagUID = "-";
    
    // For this application we just use the first reader returned.
    // Only 1 will be connected
    if (readers.size() > 0)
    {
        auto reader = readers[0];
        readerName = reader.name;
        
        if (reader.isCardInserted())
            tagUID = cardInserted(reader);
    }
    
    readerInfoDisplay.updateInfo(readerName, tagUID);
}

//==============================================================================
void MainComponent::loadVideos()
{
    juce::File videoFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("testVideo.mov");
    videoComp.load(videoFile);
}

//==============================================================================
inline std::string bytes2hexstr(const pcsc_cpp::byte_vector& bytes)
{
    std::ostringstream hexStringBuilder;

    hexStringBuilder << std::setfill('0') << std::hex;

    for (const auto byte : bytes)
        hexStringBuilder << std::setw(2) << short(byte);

    return hexStringBuilder.str();
}

juce::String MainComponent::cardInserted(pcsc_cpp::Reader reader)
{
    auto card = reader.connectToCard();
    juce::String uid = getNFCUID(std::move(card));
    
    try
    {
        UIDtoVideo(uid);
    }
    catch (...)
    {
        DBG("error with insertion");
    }
    
    return uid;
}

juce::String MainComponent::getNFCUID(pcsc_cpp::SmartCard::ptr card)
{
    juce::String uid = "-";
    
    try
    {
        auto transactionGuard = card->beginTransaction();
        auto response = card->transmit(UIDcommand);
        
        if (response.isOK())
        {
            auto bytes = response.data;
            uid = bytes2hexstr(bytes);
        }
    }
    catch (...)
    {
        DBG("Error in transmission");
    }
    
    return uid;
}

void MainComponent::UIDtoVideo(juce::String UID)
{
    if (UID == "") return;
    
    if (UID != currentUID)
    {
        videoComp.stop();
        currentUID = UID;
    }
    
    if (!videoComp.isPlaying())
    {
        videoComp.setPlayPosition(0.0f);
        videoComp.play();
    }
}
