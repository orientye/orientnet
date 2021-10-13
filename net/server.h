#ifndef NET_SERVER_H_
#define NET_SERVER_H_

class Server {
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
  int status = 0;
};

#endif  // NET_SERVER_H_
