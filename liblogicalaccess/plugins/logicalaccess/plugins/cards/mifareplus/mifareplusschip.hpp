/**
 * \file mifareplusschip.hpp
 * \author Xavier S. <xavier.schmerber@gmail.com>
 * \brief MifarePlusS chip.
 */

#ifndef LOGICALACCESS_MIFAREPLUSSCHIP_HPP
#define LOGICALACCESS_MIFAREPLUSSCHIP_HPP

#include <logicalaccess/cards/chip.hpp>
#include <logicalaccess/plugins/cards/mifare/mifareaccessinfo.hpp>
#include <logicalaccess/plugins/cards/mifareplus/lla_cards_mifareplus_api.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace logicalaccess
{
#define CHIP_MIFAREPLUSS "MifarePlusS"

class LLA_CARDS_MIFAREPLUS_API MifarePlusSChip : public MifarePlusChip, public Chip
{
  public:
    ~MifarePlusSChip() = default;
    MifarePlusSChip()
        : Chip(CHIP_MIFAREPLUSS)
    {
    }

    const std::string &getCardType() const override
    {
        return Chip::getCardType();
    }

    std::string getGenericCardType() const override
    {
        return Chip::getGenericCardType();
    }

    std::shared_ptr<Commands> getCommands() const override
    {
        return Chip::getCommands();
    }

    ByteVector getChipIdentifier() const override
    {
        return Chip::getChipIdentifier();
    }

    std::shared_ptr<CardService> getService(CardServiceType serviceType) override
    {
        return Chip::getService(serviceType);
    }
};
}

#endif /* LOGICALACCESS_MIFAREPLUSSCHIP_HPP */