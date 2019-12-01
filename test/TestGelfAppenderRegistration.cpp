#include <log4cplus_gelf/GelfAppender.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "log4cplus/initializer.h"
#include <log4cplus/spi/factory.h>
#include <log4cplus/spi/loggerfactory.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>

using namespace log4cplus;

void printAppenders() {
    spi::AppenderFactoryRegistry& reg = spi::getAppenderFactoryRegistry();
    std::cout << "Appenders: " << std::endl;
    for (auto& name : reg.getAllNames()) {
        std::cout << "Name: " << name << std::endl;
    }
}

int main(int argc, char **argv) {
    log4cplus::Initializer initializer;

    spi::AppenderFactoryRegistry& reg = spi::getAppenderFactoryRegistry();
    LOG4CPLUS_REG_APPENDER (reg, GelfAppender);

    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestGelfAppenderRegistration, Register)
{
    //printAppenders();

    spi::AppenderFactoryRegistry& reg = spi::getAppenderFactoryRegistry();
    auto appender = reg.get("log4cplus::GelfAppender");
    EXPECT_NE(nullptr, appender);
    auto& name = appender->getTypeName();
    EXPECT_EQ(name, "log4cplus::GelfAppender");
}

TEST(TestGelfAppenderRegistration, Props)
{
    tistringstream propsStream (
            LOG4CPLUS_TEXT("log4cplus.rootLogger=DEBUG, GRAYLOG\n")
            LOG4CPLUS_TEXT("log4cplus.appender.GRAYLOG=log4cplus::GelfAppender\n")
            LOG4CPLUS_TEXT("log4cplus.appender.GRAYLOG.serverHost=graylog\n")
            LOG4CPLUS_TEXT("log4cplus.appender.GRAYLOG.serverPort=12201\n")
            LOG4CPLUS_TEXT("log4cplus.appender.GRAYLOG.transport=udp\n")
            LOG4CPLUS_TEXT("log4cplus.appender.GRAYLOG.host=pss-home\n")
            LOG4CPLUS_TEXT("log4cplus.appender.GRAYLOG.facility=Relay\n")
            LOG4CPLUS_TEXT("log4cplus.appender.GRAYLOG.includeLocationInformation=true\n")
            LOG4CPLUS_TEXT("log4cplus.appender.GRAYLOG.additionalField.environment=DEV\n"));
    helpers::Properties props(propsStream);

    PropertyConfigurator configurator(props);
    configurator.configure();

    // Log message
    Logger logger = Logger::getRoot();
    LOG4CPLUS_DEBUG(logger, "One");
    LOG4CPLUS_INFO(logger, "Two");
    LOG4CPLUS_ERROR(logger, "Three");
}
