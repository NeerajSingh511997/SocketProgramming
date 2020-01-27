#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>	
#include <arpa/inet.h>

// handling error 
void error(char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]) {

	// Step 0: Requirements;
	if(argc < 2) {
		fprintf(stderr, "Error: Server port not found. \n");
		exit(1);
	}

	// Step 1: Declaration of Variables;
	char buffer[256];
	socklen_t addr_size;
	int value_1, value_2, choice, result;
	int sockfd, newsockfd, bind_status, status, port_no, socket_size;	
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len;	
	
	// Step 2: Creating Socket;
	port_no = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		error("Error: Socket failed");
	}

	// Step 3: Setup Socket Credentials;
	memset(&server_addr, '\0', sizeof(&server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_no);
	// server_addr.sin_addr.s_addr = inet_addr(127.0.0.1);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Step 4: Setup Socket Communication;
	bind_status = bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
	if(bind_status < 0) {
		error("Error: Binding failed \n");
		exit(1);
	}
	listen(sockfd, 5);
	socket_size = sizeof(server_addr);
	newsockfd = accept(sockfd, (struct sockaddr*) &client_addr, &socket_size);
	if(newsockfd < 0) {
		error("Error: Client Socket creation failed \n");
		exit(0);
	}
	
	// Step 5: Working Modules;
	while(1) {
		// Menu Of the Calculator;
		status = write(newsockfd, "Welcome Back, \n1. Addition \n2. Subtraction \n3.Multiplication \n4.Divide \n5.Exit \nEnter Your choice: ", sizeof("Welcome Back, \n1. Addition \n2. Subtraction \n3.Multiplication \n4.Divide \n5.Exit \nEnter Your choice: "));
		if(status < 0) {
			error("Error: Socket write failed\n");
			exit(1);
		}
		status = read(newsockfd, &choice, sizeof(int));
		if(status < 0) {
			error("Error: Socket read failed;");
			exit(1);
		}
		
		if(choice != 5) {
			// Enter the value_1;
			status = write(newsockfd, "Enter Number 1: ", strlen("Enter Number 1: "));
			if(status < 0) {
				error("Error: Socket write failed;");
				exit(1);
			}
			status = read(newsockfd, &value_1, sizeof(int));
			if(status < 0) {
				error("Error: Socket read failed;");
				exit(1);
			}
			printf("Client: Number 1 is %d \n", value_1);

			// Enter the value_2;
			status = write(newsockfd, "Enter Number 2: ", sizeof("Enter Number 2: "));
			if(status < 0) {
				error("Error: Socket write failed;");
				exit(1);
			}
			status = read(newsockfd, &value_2, sizeof(int));
			if(status < 0) {
				error("Error: Socket read failed;");
				exit(1);
			}	
			printf("Client: Number 2 is %d \n", value_2);

			switch(choice) {
				case 1: 
						result = value_1 + value_2;
						break;
				case 2:
						result = value_1 - value_2;
						break;
				case 3:
						result = value_1 * value_2;
						break;
				case 4:
						if( value_1 == 0 || value_2 == 0 ) {
							result = 0;
							break;
						}
				default: 
						break;
			}

			status = write(newsockfd, &result, sizeof(result));
			if(status < 0) {
				error("Error: Socket write failed;");
				exit(1);
			}

		}else {
			printf("Bye...\n");
			break;
		}

	}

	close(newsockfd);
	return 0;

}