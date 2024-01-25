//
// Created by xaqq on 6/25/15.
//

#ifndef LIBLOGICALACCESS_MIFAREPLUS_PSCS_SL3_HPP
#define LIBLOGICALACCESS_MIFAREPLUS_PSCS_SL3_HPP


#include <logicalaccess/plugins/readers/pcsc/commands/mifarepcsccommands.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <logicalaccess/plugins/cards/mifareplus/mifareplussl3commands.hpp>

namespace logicalaccess
{
/**
 * MifarePlus in Security Level 3
 *
 */
class LLA_READERS_PCSC_API MifarePlusSL3PCSCCommands : public MifarePlusSL3Commands_NEW
{
};
}


#endif // LIBLOGICALACCESS_MIFAREPLUS_PSCS_SL3_HPP
