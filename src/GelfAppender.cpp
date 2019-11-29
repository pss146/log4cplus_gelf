#include "log4cplus_gelf/GelfAppender.h"

#include <log4cplus/helpers/property.h>

namespace log4cplus
{
    GelfAppender::GelfAppender() {

    }

    GelfAppender::GelfAppender(const helpers::Properties &properties)
    : Appender(properties) {
        properties.getString(mFacility, LOG4CPLUS_TEXT("facility"));
    }

    GelfAppender::~GelfAppender() {
        destructorImpl();
    }

    void GelfAppender::close() {

    }

    void GelfAppender::append(const log4cplus::spi::InternalLoggingEvent &event) {

    }

    const std::string &GelfAppender::facility() const {
        return mFacility;
    }

    void GelfAppender::setFacility(const std::string &facility) {
        GelfAppender::mFacility = facility;
    }

}