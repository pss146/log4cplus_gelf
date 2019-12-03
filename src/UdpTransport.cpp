#include "include/UdpTransport.h"

namespace log4cplus
{

UdpTransport::UdpTransport(const std::string &mHost, int mPort)
: mHost(mHost)
, mPort(mPort)
, mInitialized(false) {
    initSocket();

    // Run service thread
    mServiceThread = std::make_unique<boost::thread>(boost::bind(&boost::asio::io_context::run, &mIOContext));
}

UdpTransport::~UdpTransport() {
    if (mSocket) {
        boost::system::error_code ec;
        mSocket->close(ec);
        mSocket.reset();
    }

    mIOContext.stop();
    mServiceThread->join();
    mServiceThread.reset();
}

void UdpTransport::send(std::string payload) {
    if (!mInitialized) return;
    // Make sure data survive until end of async operation
    auto data = std::make_shared<std::string>(std::move(payload));
    // Send the message to the UDP endpoint
    mSocket->async_send_to(boost::asio::buffer(*data), mRemoteEndpoint,
                           [data](const boost::system::error_code &error, std::size_t bytes_transferred) {
                                // do nothing
                           });
}

void UdpTransport::initSocket() {
    boost::system::error_code ec;

    boost::asio::ip::udp::resolver resolver(mIOContext);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), mHost, std::to_string(mPort));
    mRemoteEndpoint = *resolver.resolve(query);

    // Creates and opens a socket
    mSocket = std::make_unique<boost::asio::ip::udp::socket>(mIOContext, mRemoteEndpoint.protocol());

    mInitialized = true;
}

}