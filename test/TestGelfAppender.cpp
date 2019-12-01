#include <log4cplus_gelf/GelfAppender.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include "log4cplus/logger.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/helpers/property.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/initializer.h"
#include <log4cplus/loggingmacros.h>

using namespace log4cplus;

int main(int argc, char **argv) {
    log4cplus::Initializer initializer;

    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

// The fixture for testing class
class TestGelfAppender : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
        Logger::getRoot().removeAllAppenders();
    }
};

TEST(TestGelfAppender, Create)
{
    GelfAppender appender;
    EXPECT_EQ(true, true);
}

TEST(TestGelfAppender, UnsupportedTransport)
{
    try {
        log4cplus::tistringstream propsStream(
                LOG4CPLUS_TEXT("transport=tcp\n"));
        log4cplus::helpers::Properties props(propsStream);
        log4cplus::helpers::SharedObjectPtr<GelfAppender> append(new log4cplus::GelfAppender(props));
        append->setName(LOG4CPLUS_TEXT ("Gelf"));
    }
    catch (std::invalid_argument const & e) {
        SUCCEED();
        return;
    }
    FAIL();
}

TEST(TestGelfAppender, AdditionalFields)
{
    try {
        helpers::LogLog::getLogLog()->setInternalDebugging(true);

        // Init appender
        tistringstream propsStream (
                LOG4CPLUS_TEXT("serverHost=graylog\n")
                LOG4CPLUS_TEXT("serverPort=12201\n")
                LOG4CPLUS_TEXT("transport=udp\n")
                LOG4CPLUS_TEXT("host=pss-home\n")
                LOG4CPLUS_TEXT("facility=Relay\n")
                LOG4CPLUS_TEXT("includeLocationInformation=true\n")
                LOG4CPLUS_TEXT("additionalField.environment=DEV\n"));
        helpers::Properties props(propsStream);

        // Init Appender/Logger
        SharedAppenderPtr append(new GelfAppender(props));
        append->setName(LOG4CPLUS_TEXT ("Gelf"));
        Logger::getRoot().addAppender(append);

        // Log message
        Logger logger = Logger::getRoot();
        LOG4CPLUS_DEBUG(logger, "Test from GelfAppender");
    }
    catch(std::exception const & e) {
        log4cplus::tcout << "**** Exception occured: " << e.what() << std::endl;
        FAIL();
    }
}