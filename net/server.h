#ifndef NET_SERVER_H_
#define NET_SERVER_H_

#include <string>
#include <unordered_map>

class Server {
 public:
  enum class ServerState { UNINITIALIZED, READY, RUNNING, STOPPING };

 public:
  Server();
  ~Server();

  int start();
  int stop();
  int join();

  int add_service();
  int remove_service();
  int clear_services();

 private:
  ServerState state_{ServerState::UNINITIALIZED};
  std::unordered_map<std::string, google::protobuf::Service*> services_;
};

#endif  // NET_SERVER_H_
