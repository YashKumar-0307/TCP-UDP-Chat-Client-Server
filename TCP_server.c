#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(){
	struct sockaddr_in address;
	int serfd, nsocket, val,o = 1,addrlen = sizeof(address);
	char buffer[1024] = {0},*hello = "Server message recieved";
	if((serfd=socket(AF_INET,SOCK_STREAM,0)) == 0){
		perror("Connection failed");
		exit(EXIT_FAILURE);
	}
	if(setsockopt(serfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&o,sizeof(o))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family =AF_INET;
	address.sin_addr.s_addr =INADDR_ANY;
	address.sin_port =htons(PORT);
	if (bind(serfd,(struct sockaddr *)&address,sizeof(address))<0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(serfd, 3) < 0){
		perror("Listening");
		exit(EXIT_FAILURE);
	}
	if ((nsocket=accept(serfd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0){
		perror("Accepted");
		exit(EXIT_FAILURE);
	}
	val=read(nsocket,buffer,1024);
	printf("%s\n",buffer);
	send(nsocket,hello,strlen(hello),0);
	printf("Message sent\n");
	return 0;
}

