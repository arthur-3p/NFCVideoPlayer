#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
: videoComp(true)
{
    addAndMakeVisible(videoComp);
    
    loadVideos();
    
    setSize (600, 400);
    startTimer(100);
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
    videoComp.setBounds(getLocalBounds());
}

//==============================================================================
void MainComponent::timerCallback()
{
    auto readers = pcsc_cpp::listReaders();
    for (const auto& reader : readers)
    {
        if (reader.isCardInserted())
            cardInserted(reader);
    }
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

void MainComponent::cardInserted(pcsc_cpp::Reader reader)
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
}

juce::String MainComponent::getNFCUID(pcsc_cpp::SmartCard::ptr card)
{
    juce::String uid = "";
    
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
