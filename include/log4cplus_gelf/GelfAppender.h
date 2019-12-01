#ifndef LOG4CPLUS_GELF_GELFAPPENDER_H
#define LOG4CPLUS_GELF_GELFAPPENDER_H

#include <log4cplus/appender.h>
#include <log4cplus/syslogappender.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace log4cplus {

class AbstractTransport;

class GelfAppender : public Appender {
public:
    GelfAppender();

    GelfAppender(const helpers::Properties &properties);

    ~GelfAppender() override;

    void close() override;

    const std::string &facility() const;

    void setFacility(const std::string &facility);

protected:
    void append(const log4cplus::spi::InternalLoggingEvent &event) override;

    std::string createGelfJsonFromEvent(const log4cplus::spi::InternalLoggingEvent &event);
    void sendGelfPayload(const std::string& payload);

private:
    std::unique_ptr<AbstractTransport> mTransport;

    std::string mTransportKind;
    std::string mServerHost;
    unsigned int mServerPort;
    std::string mHost;
    std::string mFacility;

    bool mIncludeLocationInformation = false;
    std::unordered_map<std::string, std::string> mAdditionalFields;

    /**
     * Dummy class to give public access to the getSysLogLevel() method
     */
    class SysLogLevel : public log4cplus::SysLogAppender {
    public:
        SysLogLevel() : log4cplus::SysLogAppender("SysLogLevel") {}
        /**
         * We want to make getSysLogLevel() public.
         */
        using log4cplus::SysLogAppender::getSysLogLevel;
    };
    /**
     * Dummy constant to give static access to getSysLogLevel() method
     */
    const SysLogLevel SYSLOG_LEVEL;
};

}


#endif //LOG4CPLUS_GELF_GELFAPPENDER_H
