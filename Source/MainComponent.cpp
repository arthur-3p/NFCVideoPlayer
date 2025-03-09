#include "MainComponent.h"

#if JUCE_WINDOWS
    //for serial ports above "COM9", we must use this extended syntax of "\\.\COMx".
    //also works for COM0 to COM9.
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea?redirectedfrom=MSDN#communications-resources
    #define SERIAL_PORT "\\\\.\\COM1"
#endif
#if JUCE_LINUX
    #define SERIAL_PORT "/dev/ttyACM0"
#endif
#if defined JUCE_MAC
    #define SERIAL_PORT "/dev/tty.usbmodem1101"
#endif


//==============================================================================
MainComponent::MainComponent() : videoHolder(*this)
{
//    videoHolder.loadFiles();
    addAndMakeVisible(videoHolder);
    addChildComponent(readerInfoDisplay);
    
    errorLabel.setJustificationType(juce::Justification::centred);
    addChildComponent(errorLabel);
    
    quitButton.setButtonText("Quit");
    quitButton.onClick = [this]
    {
        requestQuit();
        juce::Thread::launch([this] { serial.closeDevice(); });
    };
    addAndMakeVisible(quitButton);
    
    quitLabel.setText("Shutting Down...", juce::dontSendNotification);
    quitLabel.setJustificationType(juce::Justification::centred);
    quitLabel.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::grey.withAlpha(0.25f));
    addChildComponent(quitLabel);
    
    setWantsKeyboardFocus(true);
    
    int openingErrorCode = openDevice();
    if (openingErrorCode != 1)
    {
        updateErrorMessage("Failure opening device. Error: " + serialOpenErrorMessage(openingErrorCode), true);
    }
    
    startTimer(100);
    
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

int MainComponent::openDevice()
{
    // Connection to serial port
    // If connection fails, return the error code otherwise
    char response = serial.openDevice(SERIAL_PORT, 9600);
    return (int) response;
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();

    if (readerInfoDisplay.isVisible())
        readerInfoDisplay.setBounds(bounds.removeFromTop(40));
    
    videoHolder.setBounds(bounds);
    errorLabel.setBounds(bounds);
    quitLabel.setBounds(bounds);
    quitButton.setBounds(bounds.removeFromTop(20).removeFromLeft(30));
}

//==============================================================================
bool MainComponent::keyPressed(const juce::KeyPress &key)
{
    if (key.getTextCharacter() == 'd')
    {
        readerInfoDisplay.setVisible(!readerInfoDisplay.isVisible());
        resized();
        return true;
    }
    
    return false;
}

//==============================================================================
void MainComponent::timerCallback()
{
    juce::String readerName = "-";
    juce::String UID = "-";
    
    readSerial(readerName, UID);
    
    if (errorIsCritical)
    {
    }
    else if (showErrorCounter > 0)
    {
        showErrorCounter--;
    }
    else if (showErrorCounter == 0)
    {
        showErrorMessage(false);
        showErrorCounter--;
    }
    
    if (quitRequested && !serial.isDeviceOpen())
    {
        juce::JUCEApplicationBase::getInstance()->systemRequestedQuit();
    }
}

//==============================================================================
void MainComponent::readSerial(juce::String& readerName, juce::String& UID)
{
    if (!serial.isDeviceOpen())
        return;
    
    char buffer[15] = "r";

    // Write the string on the serial device.
    serial.writeString(buffer);

    // Read string that arduino writes to serial in response.
    int readError = serial.readString(buffer, '\r', 15, 1);
    if (readError > 0 )
    {
        UID = juce::String(buffer);
        readerInfoDisplay.updateInfo(readerName, UID);
        videoHolder.setTagUID(UID);
    }
    else if (readError == 0)
    {
        return;  // do nothing
    }
    else
    {
        updateErrorMessage("Error Reading. Error code: " + serialReadErrorMessage(readError), false);
    }
}

void MainComponent::updateErrorMessage(juce::String error, bool isCritical)
{
    errorLabel.setText("Error: "+error, juce::dontSendNotification);
    showErrorMessage(true);
    showErrorCounter = 100;
    errorIsCritical = isCritical;
}

juce::String MainComponent::serialOpenErrorMessage(int errorCode)
{
    switch (errorCode) {
        case -1:
            return "device not found";
        case -2:
            return "error while opening the device";
        case -3:
            return "error while getting port parameters";
        case -4:
            return "Speed (Bauds) not recognized";
        case -5:
            return "error while writing port parameters";
        case -6:
            return "error while writing timeout parameters";
        case -7:
            return "Databits not recognized";
        case -8:
            return "Stopbits not recognized";
        case -9:
            return "Parity not recognized";
        default:
            return "Unknown Error Code.";
    }
}

juce::String MainComponent::serialReadErrorMessage(int errorCode)
{
    switch (errorCode) {
        case 0 :
            return "timeout is reached";
        case -1 :
            return "error while setting the Timeout";
        case -2 :
            return "error while reading the character";
        case -3 :
            return "MaxNbBytes is reached";
        default:
            return "Unknown Error Code.";
    }
}
