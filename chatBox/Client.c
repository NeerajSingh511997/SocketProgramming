// Global Header Files;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Socket Header Files;
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

/*
| # HeaderFile(stdio.h) is basic input and output file.
| 
| # HeaderFile(stdlib.h) is used for performing general functions
| 	like, exit(), rand_max, abort(), atof(), atoi(), atol();
| 
| # HeaderFile(string.h) is used for accessing the string functions
| 	like, strncmp(), strcmp()
| 
| # HeaderFile(sys/types.h) is used for accessing the system calls
| 	for allowing socket to access network protocols;
| 
| # HeaderFile(sys/socket.h) is used for accessing the socket related 
| 	methodologies in the socket programming like, socket();
|
| # HeaderFile(netinet/in.h) is used for accessing the internet address family macros
|	like, INADDR_ANY for IPv4 local host address, INADDR_BROADCAST for IPv4 broadcast address;
|
| # HeaderFile(netdb.h) is used for accessing the host related 
|	methods of structure hostent;
|
| # HeaderFile(unistd.h) is used for accessing the methods like,
|	read(), write() ;
*/

void error(char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]) {

	char buffer[1024];
	int sockfd, status, portno, serv_len;

	struct sockaddr_in serv_addr;
	/*	
	|	struct hostent {
	|		char *h_name; 
	|		char **h_aliases;	
	|		int h_addrtype;
	|		char **h_addr_list;
	|		#define h_addr h_addr_list[0];
	|	}
	*/
	struct hostent *server;	

	// configuring client side as server side;
	if(argc < 3) {
		fprintf(stderr, "Usage %s hostname post\n", argv[0]);
		exit(0);
	}

	// fetching port;
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		error("Exception occured creating socket");
		exit(1);
	}

	// fetching host name;
	server = gethostbyname(argv[1]);
	if(server == NULL) {
		fprintf(stderr, "Error, no such host\n");
		exit(1);
	}

	// reset the size of serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

	// connecting to the server;
	serv_len = sizeof(serv_addr);
	if(connect(sockfd, (struct sockaddr *) &serv_addr, serv_len) < 0 ) {
		error("Error in connecting to the server");
	}

	while(1) {
		printf("Client: ");
		bzero(buffer, 1024); 
		fgets(buffer, 1024, stdin);
		status = write(sockfd, buffer, strlen(buffer));
		if(status < 0) {
			error("Error in writing to socket");
		}

		bzero(buffer, 1024);
		status = read(sockfd, buffer, 1024);
		if(status < 0) {
			error("Error in writing to socket");
		}
		printf("Server: %s \n", buffer);	

		// terminating the loop;
		int i = strncmp("Bye", buffer, 3);
		if(i == 0) { 
			break;
		}

	}
	close(sockfd);
	return 0;

}

