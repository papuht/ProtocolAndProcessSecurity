#include "TCP.h"
#include <cstring>
#include <string>

/* TCP Server methods */

TCPServerSocket::TCPServerSocket(int domain, int type, int protocol, char* ip, int port) {
	setServerFd(domain, type, protocol);	
 
    // Forcefully attaching socket to the port 8080
    if (setsockopt(getServerFd(), SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
	setAddress(type, ip, port);    

 	bindAndListenToSocket();
    // Forcefully attaching socket to the port 8080
   
   	setValread(); 
    printf("%s\n", buffer);
    send(getNewSocket(), hello, strlen(hello), 0);
    printf("Hello message sent\n");
 
   
};

void TCPServerSocket::setServerFd(int domain, int type, int protocol) {
	 if ((server_fd = socket(domain, type, protocol)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
};

void TCPServerSocket::setAddress(int type, char* ip, int port) {
	address.sin_family = type;
    address.sin_port = htons(port);

    if (inet_pton(type, ip, &address.sin_addr)
        <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
};

void TCPServerSocket::setValread() {
	valread = read(getNewSocket(), getBuffer(), 1024);
};

int TCPServerSocket::getServerFd() {
	return server_fd;
};

int TCPServerSocket::getNewSocket() {
	return new_socket;
};

char* TCPServerSocket::getBuffer() {
	return buffer;
};



void TCPServerSocket::bindAndListenToSocket() {
	 if (bind(getServerFd(), (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(getServerFd(), 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(getServerFd(), (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
};

void TCPServerSocket::closeSocket() {
	close(getNewSocket());
};

void TCPServerSocket::shutdownServer() {
	shutdown(getServerFd(), SHUT_RDWR);
};




/*TCP Client methods*/

TCPClientSocket::TCPClientSocket(int domain, int type, int protocol, char* ip, int port) {
    setClientSocket(domain, type, protocol);
    setClientFd(getClientSocket());
    setServerAddress(type, ip, port);

}

void TCPClientSocket::setClientSocket(int domain, int type, int protocol) {
	if ((client_socket = socket(domain, type, protocol)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

void TCPClientSocket::setClientFd(int client_sock) {
	if ((client_fd = connect(client_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))< 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
}

void TCPClientSocket::setServerAddress(int type, char* ip, int port) {
    serv_addr.sin_family = type;
    serv_addr.sin_port = htons(port);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form and assign to serv_addr.sin_addr
    if (inet_pton(type, ip, &serv_addr.sin_addr)
        <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

}

int TCPClientSocket::getClientSocket() {
	return client_socket;
}

char* TCPClientSocket::getBuffer() {
	return buffer;
}


