#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080



/*refaktoroin koodin siten että tästä tulee baseclass jonka ServerSocket ja ClientSocket perii*/
class TCPSocket {
  private:
    int socket_fd;
    int new_socket;
    int valread;
    struct sockaddr_in address;
    char buffer[1024] = { 0 };
    
  public:


};

class TCPServerSocket {
  private:
    int server_fd;
    int new_socket;
    int valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = (char*)"Response from server: TCP connection established";
    
    

  public:
    TCPServerSocket(int domain, int type, int protocol, char* ip, int port);

    void setServerFd(int domain, int type, int protocol);
    void setAddress(int type, char* ip, int port);
    void setValread();


    int getServerFd();
    int getNewSocket();
    char* getBuffer();

    void bindAndListenToSocket();
    void closeSocket();
    void shutdownServer();


};

class TCPClientSocket {
  private:
    int client_socket = 0; 
    int valread; 
    int client_fd;
    struct sockaddr_in serv_addr;
    char* hello = (char*)"Hello from client";
    char buffer[1024] = { 0 };

  public:
    TCPClientSocket(int domain, int type, int protocol, char* ip, int port);
    void setClientSocket(int domain, int type, int protocol);
    void setValread();
    void setClientFd(int client_sock);
    void setServerAddress(int type, char* ip, int port);

    int getClientSocket();
    int getClientFd();
    char* getBuffer();

};

#endif