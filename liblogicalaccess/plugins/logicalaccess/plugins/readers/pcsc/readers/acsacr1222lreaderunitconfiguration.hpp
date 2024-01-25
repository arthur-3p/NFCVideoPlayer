#pragma once

#include <logicalaccess/plugins/readers/pcsc/pcscreaderunitconfiguration.hpp>

namespace logicalaccess
{
/**
 * Configuration class for ACSACR1222L.
 */
class LLA_READERS_PCSC_API ACSACR1222LReaderUnitConfiguration
    : public PCSCReaderUnitConfiguration
{

  public:
    ACSACR1222LReaderUnitConfiguration();

    void resetConfiguration() override;

    void serialize(boost::property_tree::ptree &parentNode) override;

    void unSerialize(boost::property_tree::ptree &node) override;

    PCSCReaderUnitType getPCSCType() const override;

    const std::string &getUserFeedbackReader() const;

    void setUserFeedbackReader(const std::string &);

  private:
    /**
     * Name of the ReaderUnit that we use as a "feedback" reader.
     *
     * The idea is that the ACSACR1222L as 4 chip: while the main chip
     * will interact with the card, we can connect to one of the 3 chips
     * and use them to drive the LCD display or the LEDs.
     */
    std::string user_feedback_reader_;
};
}
