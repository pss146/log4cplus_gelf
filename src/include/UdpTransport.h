#ifndef LOG4CPLUS_GELF_UDPTRANSPORT_H
#define LOG4CPLUS_GELF_UDPTRANSPORT_H

#include "AbstractTransport.h"

#include <memory>
#include <boost/thread/thread.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>

namespace log4cplus {

class UdpTransport : public AbstractTransport {
public:
    UdpTransport(const std::string &mHost, int mPort);

    ~UdpTransport() override;

    void send(std::string payload) override;

protected:
    void initSocket();

private:
    /// The io_context used to perform asynchronous operations.
    boost::asio::io_context mIOContext;
    boost::asio::ip::udp::endpoint mRemoteEndpoint;
    std::unique_ptr<boost::thread> mServiceThread;
    std::unique_ptr<boost::asio::ip::udp::socket> mSocket;

    std::string mHost;
    int mPort;

    bool mInitialized;
};

}


#endif //LOG4CPLUS_GELF_UDPTRANSPORT_H
