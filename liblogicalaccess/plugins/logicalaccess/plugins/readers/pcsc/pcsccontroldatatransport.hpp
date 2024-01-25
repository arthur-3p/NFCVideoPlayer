//
// Created by xaqq on 7/31/15.
//

#ifndef LIBLOGICALACCESS_PCSC_CTL_DATATRANSPORT_HPP
#define LIBLOGICALACCESS_PCSC_CTL_DATATRANSPORT_HPP


#include <logicalaccess/plugins/readers/pcsc/pcscdatatransport.hpp>

namespace logicalaccess
{

/**
 * A PCSC Datatransport that transmits command using the
 * SCardControl() function instead of the SCardTransmit().
 *
 * This data transport is useful when talking to the reader in direct mode.
 */
class LLA_READERS_PCSC_API PCSCControlDataTransport : public PCSCDataTransport
{

  public:
    /**
     * \brief Get the transport type of this instance.
     * \return The transport type.
     */
    std::string getTransportType() const override
    {
        return "PCSCControl";
    }

    void send(const ByteVector &data) override;
};
}


#endif // LIBLOGICALACCESS_PCSC_CTL_DATATRANSPORT_HPP
