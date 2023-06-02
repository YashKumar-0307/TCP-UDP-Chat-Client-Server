#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct saddr
void func(int sfd)
{
	char bufferr[MAX];
	int n;
	for (;;) {
		bzero(bufferr, sizeof(bufferr));
		printf("Enter string : ");
		n = 0;
		while ((bufferr[n++] = getchar()) != '\n');
		write(sfd, bufferr, sizeof(bufferr));
		bzero(bufferr, sizeof(bufferr));
		read(sfd, bufferr, sizeof(bufferr));
		printf("From Server : %s", bufferr);
		if ((strncmp(bufferr, "exit", 4)) == 0) 
		{
			printf("Client Exit!\n");
			break;
		}
	}
}

int main()
{
	int sfd, cfd;
	struct sockaddr_in saddr, cli;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully created..\n");
	}
	bzero(&saddr, sizeof(saddr));

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(PORT);

	if (connect(sfd, (SA*)&saddr, sizeof(saddr)) != 0) 
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
	{
		printf("connected to the server..\n");
	}
	func(sfd);
	close(sfd);
}

