#include <iostream>
#include <memory>

#include <boost/asio.hpp>
#include "synchronize/scheduler/ThreadPool.hpp"

using boost::asio::ip::tcp;

void handle_client(tcp::socket& socket) {
    while (true) {
        char data[1024];
        std::size_t length = socket.read_some(boost::asio::buffer(data));
        std::cout << data[0];
        boost::asio::write(socket, boost::asio::buffer(data, length));
    }
}

int main() {

    synchronize::tp::ThreadPool scheduler(4);

    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

    while (true) {
        std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
        acceptor.accept(*socket);
        scheduler.Submit([socket](){
            handle_client(*socket);
        });
    }
    
    
    return 0;
}