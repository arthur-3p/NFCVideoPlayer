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

inline std::string bytes2hexstr(const pcsc_cpp::byte_vector& bytes)
{
    std::ostringstream hexStringBuilder;

    hexStringBuilder << std::setfill('0') << std::hex;

    for (const auto byte : bytes)
        hexStringBuilder << std::setw(2) << short(byte);

    return hexStringBuilder.str();
}

void MainComponent::timerCallback()
{
    auto readers = pcsc_cpp::listReaders();
    for (const auto& reader : readers)
    {
        DBG(reader.statusString());
        if (reader.isCardInserted())
        {
            // request UID from NFC
            auto uidCom = pcsc_cpp::CommandApdu(0xFF, 0xCA, 0x00, 0x00, {}, 0x00);
            auto card = reader.connectToCard();
            
            auto transactionGuard = card->beginTransaction();
            auto response = card->transmit(uidCom);
            
            if (response.isOK())
            {
                // print UID
                auto bytes = response.data;
                DBG(bytes2hexstr(bytes));
            }
        }
    }
}
