#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Server
{
  int service;
  int protocol;
  int domain;
  int port;
  int backlog;
  u_long interface;

  struct sockaddr_in address;

  int socket;

  void (*launch)(struct Server *server);
};

struct Server server_constructor(int service, int protocol, int domain, int port, int backlog, u_long interface, void (*launch)(struct Server *server));

#endif