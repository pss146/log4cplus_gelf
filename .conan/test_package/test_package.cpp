#include <log4cplus_gelf/GelfAppender.h>

#include <log4cplus/initializer.h>
#include <log4cplus/spi/factory.h>
#include <log4cplus/spi/loggerfactory.h>

using namespace log4cplus;

int main()
{
    log4cplus::Initializer initializer;

    spi::AppenderFactoryRegistry& reg = spi::getAppenderFactoryRegistry();
    LOG4CPLUS_REG_APPENDER (reg, GelfAppender);
}
