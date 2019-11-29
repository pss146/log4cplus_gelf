#include "log4cplus_gelf/GelfAppender.h"

#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/helpers/property.h>
#include <gelfcpp/GelfMessageBuilder.hpp>
#include "gelfcpp/output/GelfJSONOutput.hpp"

#include <iostream>
#include <sstream>

static const std::string fieldNameValidationExp = "^[\\w\\.\\-]*$";
static const std::vector<std::string> deprecatedFieldNames = {"_id"};

const size_t SHORT_MESSAGE_LENGTH = 250;

namespace log4cplus
{
    GelfAppender::GelfAppender() {

    }

    GelfAppender::GelfAppender(const helpers::Properties &properties)
    : Appender(properties) {
        properties.getString(mServerHost, LOG4CPLUS_TEXT("serverHost"));
        properties.getUInt(mServerPort, LOG4CPLUS_TEXT("serverPort"));

        properties.getString(mHost, LOG4CPLUS_TEXT("host"));
        properties.getString(mFacility, LOG4CPLUS_TEXT("facility"));

        properties.getBool(mIncludeLocationInformation, LOG4CPLUS_TEXT("mIncludeLocationInformation"));

        // Get additional properties
        auto additionalProps = properties.getPropertySubset(LOG4CPLUS_TEXT("additionalField."));
        auto propKeys = additionalProps.propertyNames();
        std::cout << "Additional fields:" << std::endl;
        for (auto& propKey : propKeys) {
            auto propValue = additionalProps.getProperty(propKey);
            std::cout << propKey << "=" << propValue << std::endl;
            mAdditionalFields.emplace(std::make_pair(propKey, propValue));
        }
    }

    GelfAppender::~GelfAppender() {
        destructorImpl();
    }

    void GelfAppender::close() {

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
        const std::string& host = mHost;
        const std::string& fullMessage = event.getMessage();
        const std::string& short_message = fullMessage.substr(0, SHORT_MESSAGE_LENGTH - 1);
        const log4cplus::helpers::Time &time = event.getTimestamp();
        int level = event.getLogLevel();
        const std::string& facility = mFacility;
        int line = event.getLine();
        const std::string& file = event.getFile();



        // Insert additional fields
        for (const auto& [key, value]: mAdditionalFields) {
            gelfMessage.SetField(key, value);
        }

        // Serialize GELF message
        std::ostringstream oss;
        gelfcpp::output::GelfJSONOutput json(oss);
        json.Write(gelfMessage);

        return oss.str();
    }

    void GelfAppender::sendGelfPayload(const std::string &payload) {
        std::cout << "Payload: " << payload << std::endl;
    }

}