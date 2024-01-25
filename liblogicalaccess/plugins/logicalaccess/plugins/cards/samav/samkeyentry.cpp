/**
 * \file samkeyentry.hpp
 * \author Adrien J. <adrien.jund@islog.com>
 * \brief SAMKeyEntry source.
 */

#include <logicalaccess/plugins/cards/samav/samkeyentry.hpp>

namespace logicalaccess
{
// This declaration made SAMKeyEntry available for external link windows
template class SAMKeyEntry<KeyEntryAV2Information, SETAV2>;
template class SAMKeyEntry<KeyEntryAV1Information, SETAV1>;
}