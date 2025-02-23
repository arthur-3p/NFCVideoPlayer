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
    #define SERIAL_PORT "/dev/tty.usbmodem101"
#endif


//==============================================================================
MainComponent::MainComponent() : videoHolder(*this)
{
    errorLabel.setJustificationType(juce::Justification::centred);
    addChildComponent(errorLabel);
    
    videoHolder.loadVideos();
    addAndMakeVisible(videoHolder);
    addChildComponent(readerInfoDisplay);

    quitButton.setButtonText("Quit");
    quitButton.onClick = [] { juce::JUCEApplicationBase::getInstance()->quit(); };
    addAndMakeVisible(quitButton);
    
    setWantsKeyboardFocus(true);
    
    int openingErrorCode = openDevice();
    if (openingErrorCode != 1)
    {
        showError("Failure opening device. Error: " + serialOpenErrorMessage(openingErrorCode), true);
    }
    
    startTimer(100);
    
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    serial.closeDevice();
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

    readerInfoDisplay.updateInfo(readerName, UID);
    
    if (showingError)
    {
        errorLabel.setVisible(true);
        
        if (errorIsCritical)
        {
            // do nothing.
        }
        else if (showErrorCounter < 100)
        {
            showErrorCounter++;
        }
        else
        {
            errorLabel.setVisible(false);
            showingError = false;
        }
    }
}

//==============================================================================
void MainComponent::readSerial(juce::String& readerName, juce::String& UID)
{
    if (!serial.isDeviceOpen())
        return;
    
    char buffer[9] = "r";

    // Write the string on the serial device.
    serial.writeString(buffer);

    // Read string that arduino writes to serial in response.
    int readError = serial.readString(buffer, '\r', 9, 1);
    if (readError > 0 )
    {
        UID = juce::String(buffer);        
        videoHolder.setTagUID(UID);
    }
    else if (readError == 0)
        return;  // do nothing
    else
        showError("Error Reading. Error code: " + juce::String(readError), false);
}

void MainComponent::showError(juce::String error, bool isCritical)
{
    errorLabel.setText("Error: "+error, juce::dontSendNotification);
    showingError = true;
    showErrorCounter = 0;
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
