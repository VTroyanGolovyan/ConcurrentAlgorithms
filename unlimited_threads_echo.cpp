#include <iostream>
#include <memory>

#include <boost/asio.hpp>
#include "synchronize/scheduler/ThreadPool.hpp"

using boost::asio::ip::tcp;

void handle_client(tcp::socket& socket) {
    while (true) {
        char data[1024];
        std::size_t length = socket.read_some(boost::asio::buffer(data));
        boost::asio::write(socket, boost::asio::buffer(data, length));
    }
}

int main() {

    synchronize::tp::ThreadPool scheduler(4);

    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12346));
    std::vector<std::thread> workers;
    while (true) {
        std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
        acceptor.accept(*socket);
        workers.emplace_back([socket](){
            try {
                handle_client(*socket);
            } catch(std::exception& e) {

            }
            
        });
    }
    
    
    return 0;
}