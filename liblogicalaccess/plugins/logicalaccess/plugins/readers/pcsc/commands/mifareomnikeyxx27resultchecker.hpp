/**
 * \file mifareomnikeyxx27resultchecker.hpp
 * \author Arnaud H. <arnaud-dev@islog.com>
 * \brief DESFire ISO 7816 Result checker.
 */

#ifndef LOGICALACCESS_MIFAREOMNIKEYXX27RESULTCHECKER_HPP
#define LOGICALACCESS_MIFAREOMNIKEYXX27RESULTCHECKER_HPP

#include <logicalaccess/plugins/readers/iso7816/iso7816resultchecker.hpp>
#include <logicalaccess/plugins/readers/pcsc/lla_readers_pcsc_api.hpp>

namespace logicalaccess
{
/**
 * \brief The Omnikey xx27 mifare implementation result checker.
 */
class LLA_READERS_PCSC_API MifareOmnikeyXX27ResultChecker : public ISO7816ResultChecker
{
  public:
    MifareOmnikeyXX27ResultChecker();

    virtual ~MifareOmnikeyXX27ResultChecker();
};
}

#endif