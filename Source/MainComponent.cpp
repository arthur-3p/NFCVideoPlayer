#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
: videoComp(true)
{
    addAndMakeVisible(videoComp);
    
    juce::File videoFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("testVideo.mov");
    videoComp.load(videoFile);
    
    setSize (600, 400);
    
    startTimer(100);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    videoComp.setBounds(getLocalBounds());
}

void MainComponent::timerCallback()
{
    auto readers = pcsc_cpp::listReaders();
    for (const auto& reader : readers)
    {
        DBG(reader.statusString());
        if (reader.isCardInserted())
        {
            auto uidCom = pcsc_cpp::CommandApdu('\xFF', '\xCA', '\x00', '\x00');
            auto card = reader.connectToCard();
            
            auto transactionGuard = card->beginTransaction();
            auto response = card->transmit(uidCom);
        }
    }
}
