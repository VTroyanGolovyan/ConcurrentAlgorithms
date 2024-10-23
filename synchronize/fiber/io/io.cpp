#include "io.hpp"

#include "../Fiber.hpp"

namespace fiber {

IoService::IoService(short port) : acceptor_(io_service_, tcp::endpoint(tcp::v4(), port)), socket_(io_service_) {}

std::shared_ptr<tcp::socket> IoService::Accept() {
    Fiber* fiber = Fiber::Self();
    acceptor_.async_accept(socket_,
    [fiber](boost::system::error_code ec) {
        JumpBackToScheduler(fiber);
    });
    Suspend();
    return std::make_shared<tcp::socket>(std::move(socket_));
}

std::string IoService::ReadSome(tcp::socket& socket, size_t max_len) {
    Fiber* fiber = Fiber::Self();
    std::string data;
    data.resize(max_len);
    size_t len;
    socket.async_read_some(boost::asio::buffer(data, max_len),
    [&len, fiber](boost::system::error_code ec, std::size_t length) {
        len = length;
        JumpBackToScheduler(fiber);
    });
    Suspend();
    data.resize(len);
    return data;
}

void IoService::Write(tcp::socket& socket, const std::string& data) {
    Fiber* fiber = Fiber::Self();
    socket.async_send(boost::asio::buffer(data, data.size()),
    [fiber](boost::system::error_code ec, std::size_t length) {
        JumpBackToScheduler(fiber);
    });
    Suspend();
}

void IoService::KeepAlive(std::shared_ptr<boost::asio::steady_timer> timer) {
    timer->expires_at(timer->expires_at() + std::chrono::seconds(5));
    timer->async_wait([timer, this](const boost::system::error_code& ec) {
        KeepAlive(timer);
    });
}

void IoService::RunService() {
    std::shared_ptr<boost::asio::steady_timer> timer = std::make_shared<boost::asio::steady_timer>(io_service_, std::chrono::seconds(1));
    timer->async_wait([timer, this](const boost::system::error_code& ec) {
        KeepAlive(timer);
    });

    io_service_.run();
}

}
