/*
 * main.c
 *
 *  Created on: Jan 17, 2021
 *      Author: yujiehao
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	printf("server: Simple Socket Server\n");

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
//	int opt = 1;
	int addrlen = sizeof(address);
	int port_number = 8888;

	char buffer[1024] = {0};
	char *hello = "Hello from server";

	// Create server socket: Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}


	// init the server socket: Forcefully attaching socket to the port number
//	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
//		perror("setsockeopt");
//		exit(EXIT_FAILURE);
//	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port_number);
	// Forcefully attaching socket to the port number
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	// accept a client connection
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	// print the msg that client send
	valread = read(new_socket, buffer, 1024);
	printf("server: received - %s\n", buffer);

	send(new_socket, hello, strlen(hello), 0);
	printf("server: Hello msg sent to client\n");

	close(new_socket);

	return 0;
}
