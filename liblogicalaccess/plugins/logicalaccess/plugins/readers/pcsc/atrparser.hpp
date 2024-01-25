#ifndef LIBLOGICALACCESS_ATRPARSER_HPP
#define LIBLOGICALACCESS_ATRPARSER_HPP


#include <logicalaccess/plugins/readers/pcsc/pcscreaderunitconfiguration.hpp>
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace logicalaccess
{
/**
 * An helper class that helps deducing the type of card
 * from its ATR.
 */
class LLA_READERS_PCSC_API ATRParser
{
  public:
    explicit ATRParser(const ByteVector &atr);

    /**
     * Guess the card type from an ATR for a specific reader.
     */
    static std::string guessCardType(const ByteVector &atr,
                                     PCSCReaderUnitType reader_type);
    static std::string guessCardType(uint8_t *atr, size_t atrlen,
                                     PCSCReaderUnitType reader_type);

    /**
     * Guess the card from an hexadecimal string representation
     * of the ATR.
     */
    static std::string guessCardType(const std::string &atr_str,
                                     PCSCReaderUnitType reader_type);

    /**
     * Guess the card type from an ATR that works for any reader type.
     */
    static std::string guessCardType(const ByteVector &atr);
    static std::string guessCardType(uint8_t *atr, size_t atrlen);

    /**
     * Guess the card from an hexadecimal string representation
     * of the ATR.
     */
    static std::string guessCardType(const std::string &atr_str);

  private:
    std::string parse(bool ignore_reader_type,
                      const PCSCReaderUnitType &reader_type) const;
    std::string check_hardcoded(bool ignore_reader_type,
                                const PCSCReaderUnitType &reader_type) const;

    std::string check_from_atr() const;
    std::string check_generic_from_atr() const;

    /**
     * Deduce the card type from one byte of the ATR.
     */
    static std::string atr_x_to_type(uint8_t code);

    /**
     * Register an hardcoded ATR.
     *
     * The ATR will be register for a unique type of PCSC Reader.
     */
    void register_hardcoded_atr(const std::string &atr, const std::string &card_type,
                                PCSCReaderUnitType reader_type);

    /**
     * Register an harcoded ATR acceptable for any reader.
     */
    void register_hardcoded_atr(const std::string &atr, const std::string &card_type);

    struct ATRInfo
    {
        std::string card_type;
        /**
         * If the reader is empty, works for all type
         * of reader.
         */
        std::vector<PCSCReaderUnitType> reader_type;
    };

    ByteVector atr_;

    /**
     * A map mapping ATR hexadecimal representation to the type of
     * card they represent.
     */
    std::map<ByteVector, ATRInfo> hardcoded_atr_to_type_;
};
}

#endif // LIBLOGICALACCESS_ATRPARSER_HPP
