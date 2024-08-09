#include <boost/asio.hpp>
#include <iostream>

#include <server.h>

Server& Server::Instance() {
    static Server server;
    return server;
}

void Server::Run() {
    auto endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080);
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

    ListenSocket(endpoint, io_service, acceptor);
}

void Server::ListenSocket(boost::asio::ip::tcp::endpoint& endpoint,
                          boost::asio::io_service& io_service,
                          boost::asio::ip::tcp::acceptor& acceptor) {
    std::cout << "[SERVER::ListenSocket] Start listen on " << endpoint << std::endl;
    for (;;) {
        boost::asio::ip::tcp::socket socket(io_service);
        acceptor.accept(socket);
        std::cout << "[SERVER::ListenSocket] Сonnection established" << std::endl;

        auto request_data = ReadRequest(socket);

        socket.close();
        std::cout << "[SERVER::ListenSocket] Сlose connection" << std::endl;
    }
    std::cout << "[SERVER::ListenSocket] Stop listen on " << endpoint << std::endl;
}

std::string Server::ReadRequest(boost::asio::ip::tcp::socket& socket) {
    std::string request{};
    char temp_buffer[1024];
    boost::system::error_code error_code;

    auto len = socket.read_some(boost::asio::buffer(temp_buffer), error_code);
    if (error_code) {
        std::cout << "[SERVER::ReadRequest] Failed read request (ERROR_CODE: " << error_code << ")" << std::endl;
        return request;
    }

    request.append(temp_buffer, len);
    std::cout << "[SERVER::ReadRequest] " << request << std::endl;

    return request;
}