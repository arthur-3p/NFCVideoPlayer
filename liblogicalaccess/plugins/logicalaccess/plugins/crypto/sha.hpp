/**
 * \file sha.hpp
 * \author Julien KAUFFMANN <julien.kauffmann@freelan.org>
 * \brief SHA hash functions.
 */

#ifndef SHA_HPP
#define SHA_HPP

#include <vector>
#include <cstdint>
#include <iostream>
#include <logicalaccess/lla_fwd.hpp>
#include "logicalaccess/plugins/crypto/lla_crypto_api.hpp"

namespace logicalaccess
{
namespace openssl
{
/**
 * \brief Get a SHA-256 hash.
 * \param buffer The buffer to get the hash from.
 * \return The hash.
 */
LLA_CRYPTO_API ByteVector SHA256Hash(const ByteVector &buffer);

/**
 * \brief Get a SHA-256 hash.
 * \param str The string to get the hash from.
 * \return The hash.
 */
LLA_CRYPTO_API ByteVector SHA256Hash(const std::string &str);

/**
 * Compute the sha1 hash of `in`.
 */
LLA_CRYPTO_API ByteVector SHA1Hash(const ByteVector &in);
}
}

#endif /* SHA_HPP */