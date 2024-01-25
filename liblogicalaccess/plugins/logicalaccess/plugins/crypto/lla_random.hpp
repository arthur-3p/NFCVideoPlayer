//
// Created by xaqq on 7/2/15.
//

#ifndef LIBLOGICALACCESS_LLA_RANDOM_HPP
#define LIBLOGICALACCESS_LLA_RANDOM_HPP

#include <random>
#include <mutex>
#include "logicalaccess/plugins/crypto/lla_crypto_api.hpp"
#include <logicalaccess/lla_fwd.hpp>

namespace logicalaccess
{
/**
 * An helper to generate random number.
 *
 * This is a wrapper around OpenSSL cryptographically secure random
 * number generator.
 */
class LLA_CRYPTO_API RandomHelper
{
  public:
    /**
     * Generate 1 random byte.
     */
    static uint8_t byte();

    /**
     * Generate `size` random bytes.
     */
    static ByteVector bytes(size_t size);

  private:
    /**
     * OpenSSL's random number generation is not thread-safe.
     */
    static std::mutex mutex_;
};
}

#endif // LIBLOGICALACCESS_LLA_RANDOM_HPP
