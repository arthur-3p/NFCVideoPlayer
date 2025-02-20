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
MainComponent::MainComponent()
{
    addAndMakeVisible(videoHolder);
    addChildComponent(readerInfoDisplay);
    setWantsKeyboardFocus(true);
    
    char openingErrorCode = openDevice();
    
    if (openingErrorCode != 1)
    {
        DBG("Failure opening device. Error: " << juce::String(openingErrorCode));
    }
    
    startTimer(100);
    
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    serial.closeDevice();
}

char MainComponent::openDevice()
{
    // Connection to serial port
    // If connection fails, return the error code otherwise
    return serial.openDevice(SERIAL_PORT, 9600);
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
        DBG(UID);
        
        videoHolder.setTagUID(UID);
    }
    else if (readError == 0)
        return;  // do nothing
    else
        DBG("Error Reading. Error code: " << readError);
}

void MainComponent::updateSelectedSerialDevice()
{
//    juce::StringArray devices = serialPortListMonitor.getSerialPortList().getAllValues();
//    
//    if (devices.contains(BOARD_NAME) && currentSerialDevice.compare(BOARD_NAME))
//    {
//        currentSerialDevice = BOARD_NAME;
//        serialDevice = std::make_unique<SerialDevice>(currentSerialDevice);
//    }
//    else
//    {
//        currentSerialDevice.clear();
//    }
}
