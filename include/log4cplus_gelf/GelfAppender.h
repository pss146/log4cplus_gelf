#ifndef LOG4CPLUS_GELF_GELFAPPENDER_H
#define LOG4CPLUS_GELF_GELFAPPENDER_H

#include <log4cplus/appender.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace log4cplus {

class AbstractTransport;

class GelfAppender : public Appender {
public:
    GelfAppender();

    explicit GelfAppender(const helpers::Properties &properties);

    ~GelfAppender() override;

    void close() override;

protected:
    void append(const log4cplus::spi::InternalLoggingEvent &event) override;

    std::string createGelfJsonFromEvent(const log4cplus::spi::InternalLoggingEvent &event);
    void sendGelfPayload(const std::string& payload);

    int getSysLogLevel(const LogLevel& ll) const;

private:
    std::unique_ptr<AbstractTransport> mTransport;

    std::string mTransportKind;
    std::string mServerHost;
    unsigned int mServerPort;
    std::string mHost;
    std::string mFacility;

    bool mIncludeLocationInformation = false;
    std::unordered_map<std::string, std::string> mAdditionalFields;
};

}


#endif //LOG4CPLUS_GELF_GELFAPPENDER_H
