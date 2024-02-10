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
		0,
	};

	if (connect(sockfd, &address, sizeof(address)) != 0){ exit(15); }
	
	return sockfd;
}
	
char *sendAndRecive(int x, int y, int sockfd){

	char *buffer = malloc(256);

	char *toSend = malloc(256);
	snprintf(toSend, 256, "%d:%d", x,y);

	recv(sockfd, buffer, 255, 0);
	send(sockfd, toSend, 255, 0); 
	
	return buffer;
}

void sendColor(char color[], int sockfd){
	send(sockfd, color, 255, 0);
}

char *recvColor(int sockfd){
	char *buffer = malloc(256);
	recv(sockfd, buffer, 255, 0);
	return buffer;
}
