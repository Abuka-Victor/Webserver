#include "Server.h"
#include <stdio.h>
#include <stdlib.h>

struct Server server_constructor(int service, int protocol, int domain, int port, int backlog, u_long interface, void (*launch)(struct Server *server)){
  struct Server server;

  server.service = service;
  server.protocol = protocol;
  server.domain = domain;
  server.port = port;
  server.backlog = backlog;
  server.interface = interface;


  
  server.socket = socket(domain, service, protocol);
  
  if (server.socket == -1){
    perror("Failed to connect to socket...\n");
    exit(1);
  }

  server.address.sin_family = domain;
  server.address.sin_port = htons(port);
  server.address.sin_addr.s_addr = htonl(interface);

  if ((bind(server.socket, (struct sockaddr *) &server.address, sizeof(server.address))) != 0){
    perror("Failed to bind socket...\n");
    exit(1);
  };

  if ((listen(server.socket, server.backlog)) != 0){
    perror("Failed to start listening...\n");
    exit(1);
  };

  server.launch = launch;

  return server;
}

