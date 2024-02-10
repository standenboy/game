#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address = {
		AF_INET,
		htons(9999),
		0,
	};

	if (connect(sockfd, &address, sizeof(address)) != 0){ printf("failed to connect\n"); }

	
	struct pollfd fds[1] = { 
		{
			sockfd,
			POLLIN,
			0
		},
	};

	for (;;){
		poll(fds, 1, 50000);
	
		char buffer[256] = {0};
	
		if (fds[0].revents & POLLIN){
			recv(sockfd, buffer, 255, 0);
			send(sockfd, "stuff", 255, 0); 
			printf("server sent: %s\n", buffer);
		}
	}
	return 0;
}
