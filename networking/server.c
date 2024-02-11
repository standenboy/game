#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9999);
	address.sin_addr.s_addr = INADDR_ANY; 
	
	if(bind(sockfd, &address, sizeof(address)) != 0){ printf("failed to bind\n"); } 

	listen(sockfd, 10);

	int clientfd0 = accept(sockfd, 0, 0);
	printf("client 0 connected\n");
	int clientfd1 = accept(sockfd, 0, 0);
	printf("client 1 connected\n");
	printf("both clients connected\n");


//	send(clientfd0, "first", 255, 0);
//	send(clientfd1, "last", 255, 0);

	struct pollfd fds[2] = { 
		{
			clientfd0,
			POLLIN,
			0
		},
		{
			clientfd1,
			POLLIN,
			0
		},
	};

	send(clientfd0, "init", 255, 0);

	for (;;){
		poll(fds, 2, 50000);
	
		char buffer[256] = {0};
	
		if (fds[0].revents & POLLIN){
			recv(clientfd0, buffer, 255, 0);
			send(clientfd1, buffer, 255, 0); 
			printf("client 0 sent: %s\n", buffer);
		}else if (fds[1].revents & POLLIN){
			recv(clientfd1, buffer, 255, 0);
			send(clientfd0, buffer, 255, 0); 
			printf("client 1 sent: %s\n", buffer);
		}
	}
	return 0;
}
