#include "Multi.h"

int CreateServer(NetworkData* data)
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = {0};
	sin.sin_family = AF_INET;
	sin.sin_port = 1337;

	bind(sock, (SOCKADDR*)&sin, sizeof sin);

	puts("Waiting for someone to connect ...");

	listen(sock, 1);

	SOCKADDR_IN csin = {0};

	int sinsize = sizeof csin;
	clientSocket = accept(sock, (SOCKADDR*)&csin, &sinsize);

	puts("Client found !");

	data->imServer = 1;
	data->myTurn = 1;
}

int JoinServer(NetworkData* data)
{
	printf("Enter IP :");
	char ip[255];
	scanf("%s", ip);
	printf("Connecting to %s\n", ip);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	struct hostent *host = NULL;
	host = gethostbyname(ip);
	if(host == NULL)
	{
		printf("Unknown host %s\n", ip);
		exit(1);
	}

	SOCKADDR_IN sin = {0};

	sin.sin_addr = *(IN_ADDR*) host->h_addr;
	sin.sin_port = 1337;
	sin.sin_family = AF_INET;

	while(connect(serverSocket, (SOCKADDR*)&sin, sizeof(SOCKADDR)) == -1) ;

	printf("Connected to %s\n", ip);

	data->imServer = 0;
	data->myTurn = 0;
}