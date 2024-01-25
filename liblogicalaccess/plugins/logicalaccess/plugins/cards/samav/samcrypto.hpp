/**
 * \file samcrypto.hpp
 * \author Adrien J. <adrien.jund@islog.com>
 * \brief SAMDESfireCrypto header.
 */

#ifndef SAMCRYPTO_HPP
#define SAMCRYPTO_HPP


#include <logicalaccess/plugins/crypto/des_cipher.hpp>
#include <logicalaccess/plugins/crypto/aes_cipher.hpp>
#include <logicalaccess/plugins/cards/desfire/desfirecrypto.hpp>
#include <logicalaccess/plugins/cards/samav/lla_cards_samav_api.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace logicalaccess
{
/**
 * \brief SAM cryptographic functions.
 */
class LLA_CARDS_SAMAV_API SAMDESfireCrypto : public DESFireCrypto
{
  public:
    /**
     * \brief Constructor
     */
    SAMDESfireCrypto();

    /**
     * \brief Destructor
     */
    virtual ~SAMDESfireCrypto();

    ByteVector authenticateHostP1(std::shared_ptr<DESFireKey> key, ByteVector encRndB,
                                  unsigned char keyno);

    void authenticateHostP2(unsigned char keyno, ByteVector encRndA1,
                            std::shared_ptr<DESFireKey> key);

    ByteVector sam_crc_encrypt(ByteVector d_sessionKey, ByteVector vectordata,
                               std::shared_ptr<DESFireKey> key) const;
};
}

#endif