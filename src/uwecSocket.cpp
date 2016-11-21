#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include "fsnd.h"

 

 
int setupServerSocket(int portno){
    

  // Get a socket of the right type
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("ERROR opening socket");
    exit(1);
  }

  // server address structure
  struct sockaddr_in serv_addr;

  // Set all the values in the server address to 0
  memset(&serv_addr, '0', sizeof(serv_addr)); 

  // Setup the type of socket (internet vs filesystem)
  serv_addr.sin_family = AF_INET;

  // Basically the machine we are on...
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // Setup the port number
  // htons - is host to network byte order
  // network byte order is most sig bype first
  //   which might be host or might not be
  serv_addr.sin_port = htons(portno);

  // Bind the socket to the given port
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("ERROR on binding\n");
    exit(1);
  }

  // set it up to listen
  listen(sockfd,5);
  
  return sockfd;
}

int callServer(string host, int portno){
  const char* hostname = host.c_str();  
  // Socket pointer
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    fprintf(stderr,"ERROR opening socket\n");
    exit(0);
  }
  
  // server address structure
  struct sockaddr_in serv_addr;

  // Set all the values in the server address to 0
  memset(&serv_addr, '0', sizeof(serv_addr)); 

  // Setup the type of socket (internet vs filesystem)
  serv_addr.sin_family = AF_INET;

   // Setup the port number
  // htons - is host to network byte order
  // network byte order is most sig byte first
  //   which might be host or might not be
  serv_addr.sin_port = htons(portno);


  // Setup the server host address
  struct hostent *server;
  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);  /// dest, src, size

  // Connect to the server
  if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("ERROR connecting: Error Number: %d\n", errno);
    exit(0);
  }
  
  return sockfd;
}

  
int serverSocketAccept(int serverSocket){
  //this method should accept an incoming call.
  int newsockfd;
  struct sockaddr_in cli_addr;
  socklen_t clilen = sizeof(cli_addr);
  
  newsockfd = accept(serverSocket, (struct sockaddr *) &cli_addr, &clilen);
  printf("connected\n");
  if (newsockfd < 0) {
    printf("ERROR on accept: Error Number: %d\n", errno);
    exit(1);
  }
  
  return newsockfd;
}


int shutdownSocket(int socket, int flags){
    return shutdown(socket,flags);
}

void writeLong(long x, int socket){
    if (write(socket, &x, sizeof(long)) < 0) {
        printf("ERROR writing to socket: Error Number: %d\n", errno);
        exit(0);
    }
}


void writeLongInt(unsigned long int x, int socket){
    if (write(socket, &x, sizeof(unsigned long int)) < 0) {
        printf("ERROR writing to socket: Error Number: %d\n", errno);
        exit(0);
    }
}

long readLong(int socket){
    long readIn = 0;
    if (read(socket, &readIn, sizeof(long)) < 0) {
        printf("ERROR reading from socket: Error Number: %d\n", errno);
        exit(0);
    }
    return readIn;
}

unsigned long int readLongInt(int socket){
    unsigned long int readIn = 0;
    if (read(socket, &readIn, sizeof(unsigned long int)) < 0) {
        printf("ERROR reading from socket: Error Number: %d\n", errno);
        exit(0);
    }
    return readIn;
}

void writeByte(char* x, int socket){
    if (write(socket, x, 255) < 0){
        printf("ERROR writing to socket: Error Number: %d\n", errno);
        exit(0);
    }
}

char* readByte(int socket){
    char* readIn = new char[256];
    if (read(socket, readIn, 255) < 0){
        printf("ERROR reading from socket: Error Number: %d\n", errno);
        exit(0);
    }
    return readIn;
}

void writeInt(int x, int socket){
    if (write(socket, &x, sizeof(int)) < 0) {
        printf("ERROR writing to socket: Error Number: %d\n", errno);
        exit(0);
    }
}

int readInt(int socket){
    int readIn = 0;
    if (read(socket, &readIn, sizeof(int)) < 0) {
        printf("ERROR reading from socket: Error Number: %d\n", errno);
        exit(0);
    }

    return readIn;
}

string readString(int socket){
    string readIn;
    if(read(socket, &readIn,sizeof(string)) < 0){
        printf("ERROR reading from socket: Error Number: %d\n", errno);
        exit(0);
    }
    return readIn;
}

void writeString(string x,int socket){
    if(write(socket, &x, sizeof(x)) < 0){
        printf("ERROR reading from socket: Error Number: %d\n", errno);
        exit(0);
    }
}

