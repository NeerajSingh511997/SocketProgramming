// Global Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Socker Header Files
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*
| # HeaderFile(stdio.h) is basic input and output file.
| 
| # HeaderFile(stdlib.h) is used for performing general functions
| 	like, exit(), rand_max, abort(), atof(), atoi(), atol();
| 
| # HeaderFile(string.h) is used for accessing the string functions
| 	like, strncmp(), strcmp();
|
| # HeaderFile(sys/types.h) is used for accessing the system calls
| 	for allowing socket to access network protocols;
| 
| # HeaderFile(sys/socket.h) is used for accessing the socket related 
| 	methodologies in the socket programming;
|
| # HeaderFile(netinet/in.h) is used for accessing the internet address family macros
|	like, INADDR_ANY for IPv4 local host address, INADDR_BROADCAST for IPv4 broadcast address;
|
| # HeaderFile(unistd.h) is used for accessing the methods like 
|	read and write functions;
*/

void error(const char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]) {

	if(argc < 2) {
		fprintf(stderr, "Port Number is not provided");
		exit(1);
	}

	char buffer[1024];
	int sockfd, newsockfd, portno, n, client_length;

	struct sockaddr_in server, client;

	if(argc < 2) {
		fprintf(stderr, "Exception occured: Less Argument is given \n");
		exit(1);
	}

	// Creating Socket and Sock File Descriptor;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0) {
		error("Error: Socket creation failed \n");
		exit(1);
	}

	// reset the buffer to zero;
	bzero((char *) &server, sizeof(server));

	// port number;
	portno = atoi(argv[1]);

	// Setting up the socket structure;
	server.sin_family = AF_INET;
	server.sin_port = htons(portno);
	server.sin_addr.s_addr = INADDR_ANY;	// ip address of host;

	// Binding the Socket to the current machine host;
	if(bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
		error("Fatal Error: Socket Bind Failure \n");
		exit(1);
	}

	// listen to the socket;
	listen(sockfd, 5);

	// Accepting the socket;
	client_length = sizeof(client);
	newsockfd = accept(sockfd, (struct sockaddr *) &client, &client_length);
	if(newsockfd < 0) {
		error("Exception occured while accepting client socket \n");
		exit(1);
	}

	while(1) {
		// reseting buffer to zero;
		bzero(buffer, 1024);

		// read the buffer from client;
		n = read(newsockfd, buffer, 1024);
		if(n < 0) {
			error("Error: reading from the socket");
		}
		printf("Client: %s \n", buffer);

		// write to the buffer from server;
		bzero(buffer, 1024);
		fgets(buffer, 1024, stdin);
		n = write(newsockfd, buffer, strlen(buffer));
		if(n < 0) {
			error("Error: writing to the socket");
		}

		int i = strncmp("Bye", buffer, 3);
		if(i == 0) {
			break;
		}
	
	}
	
	close(newsockfd);
	close(sockfd);
	return 0;
}