 #include "SerialDevice.h"

#define kBPS 9600
const auto kNumberOfDecimalPlaces { 4 };


const int kMaxPayloadSize = 20;


SerialDevice::SerialDevice (juce::String newSerialPortName)
{
    serialPortName = newSerialPortName;
    openSerialPort();
    updated.store(false);
//    startTimer (5);
}

SerialDevice::~SerialDevice ()
{
//    stopTimer();
    closeSerialPort ();
}

juce::String SerialDevice::getCurrentUID()
{
    juce::ScopedLock lock(cs);
    return uid;
}

bool SerialDevice::openSerialPort ()
{
    serialPort = std::make_unique<SerialPort> ([] (juce::String, juce::String) {});
    bool opened = serialPort->open (serialPortName);

    if (opened)
    {
        SerialPortConfig serialPortConfig;
        serialPort->getConfig (serialPortConfig);
        serialPortConfig.bps = kBPS;
        serialPortConfig.databits = 8;
        serialPortConfig.parity = SerialPortConfig::SERIALPORT_PARITY_NONE;
        serialPortConfig.stopbits = SerialPortConfig::STOPBITS_1;
        serialPort->setConfig (serialPortConfig);

        serialPortInput = std::make_unique<SerialPortInputStream> (serialPort.get());
        serialPortOutput = std::make_unique<SerialPortOutputStream> (serialPort.get ());
        serialPortInput->addChangeListener(this);
        serialPortInput->setNotify(SerialPortInputStream::NOTIFY_ON_CHAR, '\n');
        juce::Logger::outputDebugString ("Serial port: " + serialPortName + " opened");
    }
    else
    {
        // report error
        juce::Logger::outputDebugString ("Unable to open serial port:" + serialPortName);
    }

    return opened;
}

void SerialDevice::closeSerialPort ()
{
    serialPortOutput = nullptr;
    serialPortInput = nullptr;
    if (serialPort != nullptr)
    {
        serialPort->close ();
        serialPort = nullptr;
    }
}


#define kSerialPortBufferLen 256
void SerialDevice::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    juce::ScopedLock lock(cs);
    // handle reading from the serial port
    //or, read line by line:
    juce::String string;
    while(serialPortInput->canReadLine())
    {
        string = serialPortInput->readNextLine();
    }
    
    DBG(string);
    uid = string;
    
    updated.store(true);
}

