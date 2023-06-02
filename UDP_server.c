#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
	char buff[MAX];
	int n;

	for (;;) {
		bzero(buff, MAX);

		read(sockfd, buff, sizeof(buff));

		printf("From client: %s\t To client : ", buff);
		bzero(buff, MAX);
		n = 0;

		while ((buff[n++] = getchar()) != '\n');

		write(sockfd, buff, sizeof(buff));

		if (strncmp("exit", buff, 4) == 0) 
		{
			printf("Server Exit!\n");
			break;
		}
	}
}


int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) 
	{
		printf("Socket Creation Failed...\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully created..\n");
	}
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Socket Bind Failed!\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");


	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed!\n");
		exit(0);
	}
	else
		printf("Server Listening!\n");
	len = sizeof(cli);


	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) 
	{
		printf("Server Acccept Failed!\n");
		exit(0);
	}
	else
	{
		printf("Server Acccepted Client...\n");
	}

	func(connfd);

	close(sockfd);
}

