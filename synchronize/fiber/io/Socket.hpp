#include <boost/asio.hpp>
#include "../Fiber.hpp"
using boost::asio::ip::tcp;
// TODO
namespace fiber {

class IoService {

public:
    IoService(boost::asio::io_context& io_context, short port) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), socket_(io_context) {}


    tcp::socket Accept() {

    }

private:
    tcp::acceptor acceptor_;
	tcp::socket socket_;

};

}