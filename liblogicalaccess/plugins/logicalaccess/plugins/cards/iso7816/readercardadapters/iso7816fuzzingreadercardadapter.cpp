/**
* \file iso7816readercardadapter.cpp
* \brief ISO7816 Fuzzing reader/card adapter.
*/

#include <logicalaccess/plugins/cards/iso7816/readercardadapters/iso7816fuzzingreadercardadapter.hpp>

#include <cstring>

namespace logicalaccess
{
int ISO7816FuzzingReaderCardAdapter::index = 1;

ISO7816FuzzingReaderCardAdapter::ISO7816FuzzingReaderCardAdapter()
    : currentIndex(0)
{
}

ByteVector ISO7816FuzzingReaderCardAdapter::sendCommand(const ByteVector &command,
                                                        long timeout)
{
    ++currentIndex;
    ByteVector result;
    try
    {
        result = ISO7816ReaderCardAdapter::sendCommand(command, timeout);
    }
    catch (...)
    {
        ++index;
        throw;
    }

    if (currentIndex == index)
    {
        if (result.size() > 2)
        {
            std::random_device rnd_device;
            std::mt19937 mersenne_engine(rnd_device());
            std::uniform_int_distribution<int> dist(0x00, 0xff);
            auto gen = std::bind(dist, mersenne_engine);

            generate(begin(result), end(result) - 2, gen);
        }
        ++index;
    }

    return result;
}
}