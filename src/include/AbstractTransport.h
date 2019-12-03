#ifndef LOG4CPLUS_GELF_ABSTRACTTRANSPORT_H
#define LOG4CPLUS_GELF_ABSTRACTTRANSPORT_H

#include <string>

namespace log4cplus
{

class AbstractTransport {
public:
    virtual ~AbstractTransport() = default;

    virtual void send(std::string payload) = 0;
};

}


#endif //LOG4CPLUS_GELF_ABSTRACTTRANSPORT_H
