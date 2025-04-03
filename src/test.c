#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Server.h"

void launch(struct Server *server){
  struct sockaddr_in client_addr;
  char buffer[30000];
  char *hello= "HTTP/1.1 200 OK\nDate: Wed, 3rd April, 2025 13:24:42 GMT+1\nServer: Abuka/0.0.1(Darwin)\nLast-Modified: Wed, 3rd April, 2025 13:24:42 GMT+1\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>Hello, World!</h1></body></html>";

  int client_addr_len = sizeof(client_addr);
  int new_socket;

  while (1) {
    printf("=========  Waiting for Connection ============\n");
    new_socket = accept(server->socket, (struct sockaddr *) &client_addr, &client_addr_len);
    printf("Client connected\n");
  
    read(new_socket, buffer, 30000);
    printf("%s\n", buffer);
  
    write(new_socket, hello, strlen(hello));
    close(new_socket);
  }
}

int main(){
  struct Server server = server_constructor(SOCK_STREAM, 0, AF_INET, 80, 10, INADDR_ANY, launch);

  server.launch(&server);
}