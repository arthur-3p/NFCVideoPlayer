#pragma once

#include <logicalaccess/plugins/readers/pcsc/readers/cardprobes/pcsccardprobe.hpp>

namespace logicalaccess
{
class LLA_READERS_PCSC_API CL1356CardProbe : public PCSCCardProbe
{
  public:
    explicit CL1356CardProbe(ReaderUnit *ru);

    bool maybe_mifare_classic() override;
};
}
