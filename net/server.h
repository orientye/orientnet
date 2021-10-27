#ifndef NET_SERVER_H_
#define NET_SERVER_H_

#include <cstdint>
#include <string>
#include <unordered_map>

#include "google/protobuf/service.h"

class Server {
 public:
  struct Options {
    std::string service_name;
    std::size_t max_concurrent_requests = 100000;
    std::size_t max_concurrent_connections = 100000;
  };
  enum class ServerState { UNINITIALIZED, READY, RUNNING, STOPPING };

 public:
  Server();
  ~Server();

  int start(const std::string& host, std::uint16_t port);
  int stop();
  int join();

  int add_service();
  int remove_service();
  int clear_services();

 private:
  Options options_;
  ServerState state_{ServerState::UNINITIALIZED};
  std::unordered_map<std::string, google::protobuf::Service*> services_;
};

#endif  // NET_SERVER_H_
