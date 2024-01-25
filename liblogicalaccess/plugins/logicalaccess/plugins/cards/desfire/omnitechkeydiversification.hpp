#ifndef OMNITECHKEYDIVERSIFICATION_HPP__
#define OMNITECHKEYDIVERSIFICATION_HPP__

#include <logicalaccess/cards/keydiversification.hpp>
#include <logicalaccess/key.hpp>
#include <vector>

namespace logicalaccess
{
class LLA_CARDS_DESFIRE_API OmnitechKeyDiversification : public KeyDiversification
{
  public:
    void initDiversification(ByteVector identifier, unsigned int AID,
                             std::shared_ptr<Key> key, unsigned char keyno,
                             ByteVector &diversify) override;
    ByteVector getDiversifiedKey(std::shared_ptr<Key> key, ByteVector diversify) override;

    OmnitechKeyDiversification()
    {
    }
    ~OmnitechKeyDiversification()
    {
    }

    std::string getKeyDiversificationType() override
    {
        return "Omnitech";
    }

    void serialize(boost::property_tree::ptree &parentNode) override;
    void unSerialize(boost::property_tree::ptree &node) override;
    std::string getDefaultXmlNodeName() const override
    {
        return "OmnitechKeyDiversification";
    }
};
}

#endif