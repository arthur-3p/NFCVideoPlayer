/**
 * \file samiso7816resultchecker.hpp
 * \author Arnaud H. <arnaud-dev@islog.com>
 * \brief SAM ISO 7816 Result checker.
 */

#ifndef LOGICALACCESS_SAMISO7816RESULTCHECKER_HPP
#define LOGICALACCESS_SAMISO7816RESULTCHECKER_HPP

#include <logicalaccess/plugins/readers/iso7816/iso7816resultchecker.hpp>

namespace logicalaccess
{
/**
 * \brief The SAM ISO 7816 result checker.
 */
class LLA_READERS_ISO7816_API SAMISO7816ResultChecker : public ISO7816ResultChecker
{
  public:
    SAMISO7816ResultChecker();

    virtual ~SAMISO7816ResultChecker();
};
}

#endif