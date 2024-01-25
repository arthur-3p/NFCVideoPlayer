#include <string>
#include <memory>
#include <logicalaccess/readerproviders/readerprovider.hpp>
#include <logicalaccess/plugins/readers/elatec/elatecreaderprovider.hpp>

extern "C" {
LLA_READERS_ELATEC_API char *getLibraryName()
{
    return (char *)"Elatec";
}

LLA_READERS_ELATEC_API void
getElatecReader(std::shared_ptr<logicalaccess::ReaderProvider> *rp)
{
    if (rp != nullptr)
    {
        *rp = logicalaccess::ElatecReaderProvider::getSingletonInstance();
    }
}

LLA_READERS_ELATEC_API bool getReaderInfoAt(unsigned int index, char *readername,
                                            size_t readernamelen, void **getterfct)
{
    bool ret = false;
    if (readername != nullptr && readernamelen == PLUGINOBJECT_MAXLEN &&
        getterfct != nullptr)
    {
        switch (index)
        {
        case 0:
        {
            *getterfct = (void *)&getElatecReader;
            sprintf(readername, READER_ELATEC);
            ret = true;
        }
        break;
        default:;
        }
    }

    return ret;
}
}