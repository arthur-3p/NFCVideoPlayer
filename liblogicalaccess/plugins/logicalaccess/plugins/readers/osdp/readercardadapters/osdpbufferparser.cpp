/**
 * \file osdpbufferparser.cpp
 * \author Adrien J. <adrien.jund@islog.com>
 * \brief OSDP buffer parser.
 */

#include <logicalaccess/plugins/llacommon/logs.hpp>
#include <logicalaccess/plugins/readers/osdp/readercardadapters/osdpbufferparser.hpp>

namespace logicalaccess
{
ByteVector
OSDPBufferParser::getValidBuffer(boost::circular_buffer<unsigned char> &circular_buffer)
{
    ByteVector result;

    int removeCount = 0;
    for (auto it = circular_buffer.begin(); it != circular_buffer.end() && (*it != 0x53);
         ++it)
    {
        ++removeCount;
    }
    if (removeCount != 0)
        LOG(LogLevel::DEBUGS) << "Remove noise length: " << removeCount;
    circular_buffer.erase(circular_buffer.begin(), circular_buffer.begin() + removeCount);
    // we expect that is start by 0x53 - everything else is noise

    if (circular_buffer.size() >= 6)
    {
        short packetLength = ((circular_buffer[2 + 1] << 8) + circular_buffer[2]);
        LOG(LogLevel::DEBUGS) << "packetLength requested: " << packetLength;
        if (static_cast<short>(circular_buffer.size()) >= packetLength)
        {
            result.assign(circular_buffer.begin(),
                          circular_buffer.begin() + packetLength);
            circular_buffer.erase(circular_buffer.begin(),
                                  circular_buffer.begin() + packetLength);
        }
    }
    return result;
}
}
