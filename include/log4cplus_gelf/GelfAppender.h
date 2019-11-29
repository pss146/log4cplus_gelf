#ifndef LOG4CPLUS_GELF_GELFAPPENDER_H
#define LOG4CPLUS_GELF_GELFAPPENDER_H

#include <log4cplus/appender.h>

#include <string>

namespace log4cplus {

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

private:
    std::string mFacility;
};

}


#endif //LOG4CPLUS_GELF_GELFAPPENDER_H
