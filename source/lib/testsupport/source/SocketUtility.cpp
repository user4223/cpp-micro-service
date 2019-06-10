
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace TestSupport
{
  int getFreeTCPPort(std::string ipv4)
  {
    using namespace boost::asio;

    io_service service(0); ///< Avoid using many threads
    ip::tcp::socket socket(service);
    socket.open(ip::tcp::v4());
    socket.bind(ip::tcp::endpoint(ip::address::from_string(ipv4), 0));
    return socket.local_endpoint().port();
  }
} // namespace TestSupport
