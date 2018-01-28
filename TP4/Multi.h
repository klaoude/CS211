#ifndef MULTI_H
#define MULTI_H

#include "Menu.h"

#ifdef WIN32

#include <winsock2.h> 

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define h_addr h_addr_list[0]

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

typedef struct NetworkData
{
	unsigned char imServer;
	unsigned char myTurn;
} NetworkData;

int CreateServer(NetworkData* data);
int JoinServer(NetworkData* data);

SOCKET clientSocket;
SOCKET serverSocket;

#endif