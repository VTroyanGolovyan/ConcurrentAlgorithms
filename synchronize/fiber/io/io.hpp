#ifndef IO_FIBER_HPP
#define IO_FIBER_HPP

#include <boost/asio.hpp>

#include <chrono>
#include <memory>

using boost::asio::ip::tcp;

namespace fiber {

class IoService {

public:
    IoService(short port);

    std::shared_ptr<tcp::socket> Accept();

    std::string ReadSome(tcp::socket& socket, size_t max_len = 124);

    void Write(tcp::socket& socket, const std::string& data);

    void RunService();
private:
    void KeepAlive(std::shared_ptr<boost::asio::steady_timer> timer);
    
    boost::asio::io_service io_service_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

}

#endif
