#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
int main(){
	struct sockaddr_in serv_addr;
	int sket = 0, val;
	char *hello = "Message from client",buffer[1024] = {0};
	if ((sket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\nERROR in Socket creation!!\n");
		return -1;
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
	if (connect(sket,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
		printf("\nConnection Failed \n");
		return -1;
	}
	send(sket,hello,strlen(hello),0);
	printf("Hello message sent\n");
	val=read(sket,buffer,1024);
	printf("%s\n",buffer);
	return 0;
}
