#include <log4cplus_gelf/GelfAppender.h>
#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include <string>
#include "log4cplus/logger.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/helpers/property.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/initializer.h"
#include <log4cplus/loggingmacros.h>

using namespace log4cplus;

TEST(TestGelfAppender, Create)
{
    GelfAppender appender;
    EXPECT_EQ(true, true);
}


TEST(TestGelfAppender, Props)
{
    try {
        log4cplus::tistringstream propsStream(LOG4CPLUS_TEXT ("facility=Relay"));
        log4cplus::helpers::Properties props(propsStream);
        log4cplus::helpers::SharedObjectPtr<GelfAppender> append(new log4cplus::GelfAppender(props));
        append->setName(LOG4CPLUS_TEXT ("Gelf"));

        EXPECT_EQ(append.get()->facility(), "Relay");
    }
    catch(std::exception const & e) {
        log4cplus::tcout << "**** Exception occured: " << e.what() << std::endl;
    }
}

TEST(TestGelfAppender, AdditionalFields)
{
    try {
        helpers::LogLog::getLogLog()->setInternalDebugging(true);

        // Init appender
        tistringstream propsStream (
                LOG4CPLUS_TEXT("facility=Relay\n")
                LOG4CPLUS_TEXT("includeLocationInformation=true\n")
                LOG4CPLUS_TEXT("additionalField.environment=DEV\n"));
        helpers::Properties props(propsStream);

        helpers::SharedObjectPtr<GelfAppender> append(new GelfAppender(props));
        append->setName(LOG4CPLUS_TEXT ("Gelf"));

        // Init Logger
        Logger logger = Logger::getRoot();
        logger.addAppender(SharedAppenderPtr(append.get()));

        LOG4CPLUS_DEBUG(logger, "Test from GelfAppender");
    }
    catch(std::exception const & e) {
        tcout << "**** Exception occured: " << e.what() << std::endl;
    }
}