#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

int connectToServer(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address = {
		AF_INET,
		htons(9999),
		address.sin_addr.s_addr = inet_addr("50.116.49.93"),
	};

	if (connect(sockfd, &address, sizeof(address)) != 0){ exit(15); }
	
	return sockfd;
}
	
char *sendAndRecive(int x, int y, int sockfd){

	struct pollfd fds[1] = {
		{
			sockfd,
			POLLIN,
			0,
		}
	};

	char *buffer = malloc(256);

	if (fds[0].revents & POLLIN){
		char *toSend = malloc(256);
		snprintf(toSend, 256, "%d:%d", x,y);
		send(sockfd, toSend, 255, 0); 

	}

	recv(sockfd, buffer, 255, 0);
	
	return buffer;
}

