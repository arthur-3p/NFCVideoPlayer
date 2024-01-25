/**
 * \file elatecbufferparser.cpp
 * \author Adrien J. <adrien.jund@islog.com>
 * \brief Elatec buffer parser.
 */

#include <logicalaccess/plugins/readers/elatec/readercardadapters/elatecbufferparser.hpp>

namespace logicalaccess
{
ByteVector
ElatecBufferParser::getValidBuffer(boost::circular_buffer<unsigned char> &circular_buffer)
{
    ByteVector result;

    if (circular_buffer.size() >= 5)
    {
        unsigned char buflength = circular_buffer[0];
        if (circular_buffer.size() >= buflength)
        {
            result.assign(circular_buffer.begin(), circular_buffer.begin() + buflength);
            circular_buffer.erase(circular_buffer.begin(),
                                  circular_buffer.begin() + buflength);
        }
    }
    return result;
}
}