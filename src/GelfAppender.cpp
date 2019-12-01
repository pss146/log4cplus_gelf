#include "log4cplus_gelf/GelfAppender.h"

#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/helpers/property.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/timehelper.h>
#include <gelfcpp/GelfMessage.hpp>
#include "gelfcpp/output/GelfJSONOutput.hpp"

#include "include/TransportFactory.h"

#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

static const std::string fieldNameValidationExp = "^[\\w\\.\\-]*$";
static const std::vector<std::string> deprecatedFieldNames = {"_id"};

namespace log4cplus {

    GelfAppender::GelfAppender() {

    }

    GelfAppender::GelfAppender(const helpers::Properties &properties)
            : Appender(properties) {
        properties.getString(mTransportKind, LOG4CPLUS_TEXT("transport"));
        properties.getString(mServerHost, LOG4CPLUS_TEXT("serverHost"));
        properties.getUInt(mServerPort, LOG4CPLUS_TEXT("serverPort"));

        properties.getString(mHost, LOG4CPLUS_TEXT("host"));
        properties.getString(mFacility, LOG4CPLUS_TEXT("facility"));

        properties.getBool(mIncludeLocationInformation, LOG4CPLUS_TEXT("mIncludeLocationInformation"));

        // Get additional properties
        auto additionalProps = properties.getPropertySubset(LOG4CPLUS_TEXT("additionalField."));
        auto propKeys = additionalProps.propertyNames();
        helpers::getLogLog().debug(
                LOG4CPLUS_TEXT("Additional fields:"));
        for (auto &propKey : propKeys) {
            auto propValue = additionalProps.getProperty(propKey);
            helpers::getLogLog().debug(
                    LOG4CPLUS_STRING_TO_TSTRING(propKey + "=" + propValue));
            mAdditionalFields.emplace(std::make_pair(propKey, propValue));
        }

        // Init transport
        try {
            int port = boost::lexical_cast<int>(mServerPort);
            mTransport = std::move(TransportFactory::create(mTransportKind, mServerHost, port));
        } catch (const std::exception &ex) {
            helpers::getLogLog().error(
                    LOG4CPLUS_TEXT("Cannot create transport: ") + LOG4CPLUS_C_STR_TO_TSTRING(ex.what()));
            throw;
        }
    }

    GelfAppender::~GelfAppender() {
        destructorImpl();
    }

    void GelfAppender::close() {
        helpers::getLogLog().debug(
                LOG4CPLUS_TEXT("Entering GelfAppender::close()..."));

        mTransport.reset();
        closed = true;
    }

    void GelfAppender::append(const log4cplus::spi::InternalLoggingEvent &event) {
        auto gelfJson = createGelfJsonFromEvent(event);

        // Send GELF payload via UDP socket
        sendGelfPayload(gelfJson);
    }

    const std::string &GelfAppender::facility() const {
        return mFacility;
    }

    void GelfAppender::setFacility(const std::string &facility) {
        GelfAppender::mFacility = facility;
    }

    std::string GelfAppender::createGelfJsonFromEvent(const log4cplus::spi::InternalLoggingEvent &event) {

        gelfcpp::GelfMessage gelfMessage;

        // Prepare fields according to GELF Payload Specification
        gelfMessage.SetHost(mHost);
        gelfMessage.SetMessage(event.getMessage());

        auto &time = event.getTimestamp();
        auto sec = static_cast<unsigned int>(helpers::to_time_t(time));
        auto usec = static_cast<unsigned int>(helpers::microseconds_part(time));
        double timestamp = sec + (usec / 1000000.0);
        gelfMessage.SetTimestamp(timestamp);

        int level = SYSLOG_LEVEL.getSysLogLevel(event.getLogLevel());
        gelfMessage.SetField("level", level);

        gelfMessage.SetField("facility", mFacility);
        gelfMessage.SetField("file", event.getFile());
        gelfMessage.SetField("line", event.getLine());

        // Insert additional fields
        for (const auto&[key, value]: mAdditionalFields) {
            gelfMessage.SetField(key, value);
        }

        // Serialize GELF message
        std::ostringstream oss;
        gelfcpp::output::GelfJSONOutput json(oss);
        json.Write(gelfMessage);

        return oss.str();
    }

    void GelfAppender::sendGelfPayload(const std::string &payload) {
        helpers::getLogLog().debug(
                LOG4CPLUS_STRING_TO_TSTRING("Payload: " + payload));
        mTransport->send(payload);
    }

}