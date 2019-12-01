#ifndef LOG4CPLUS_GELF_TRANSPORTFACTORY_H
#define LOG4CPLUS_GELF_TRANSPORTFACTORY_H

#include "UdpTransport.h"

#include <memory>
#include <boost/algorithm/string.hpp>

namespace log4cplus
{

class TransportFactory {
public:
    static std::unique_ptr<AbstractTransport> create(const std::string& kind, const std::string& host, int port) {
        if (boost::iequals("udp", kind)) {
            return std::make_unique<UdpTransport>(host, port);
        }
        throw std::invalid_argument("Unknown transport: " + kind);
    }
};

}


#endif //LOG4CPLUS_GELF_TRANSPORTFACTORY_H
