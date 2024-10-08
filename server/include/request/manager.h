#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <boost/asio.hpp>

namespace request {

class IRequest;
class IResult;

class Manager {
public:
    Manager(boost::asio::ip::tcp::socket& socket);
    ~Manager();

    void Process(std::string const& request_json_as_string);

private:
    std::unique_ptr<IRequest> Prepare(std::string const& request_json_as_string);

    void SendResponce(std::string& responce);

    std::string GetErrorResult(std::string const& error_message);

    std::vector<std::shared_ptr<IRequest>> mSetRequestQueue;

    boost::asio::ip::tcp::socket& mSocketRef;
};

}  // namespace request
