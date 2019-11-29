#include <log4cplus_gelf/GelfAppender.h>
#include <gtest/gtest.h>

#include <exception>
#include <iostream>
#include <string>
#include "log4cplus/logger.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/helpers/property.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/initializer.h"

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