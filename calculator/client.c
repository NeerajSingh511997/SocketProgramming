#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void error() {
	perror("Fatal Error: Something went wrong \n");
	exit(1);
}

int main(int argc ,char *argv[]) {
	// Step 0: Requirements;
	if(argc < 3) {
		error("Error: Command line argument missing;");
		exit(1);
	}

	// Step 1: Declaraing Variables;
	char buffer[1024];
	int value_1, value_2, result, choice;
	int sockfd, port_no, connect_status, status;
	struct sockaddr_in server_addr;
	struct hostent * host;

	// Step 2: Creating Socket (default);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		error("Error: Socket creation failed;");
		exit(1);
	}

	// Step 3: Setting up Socket credentials;
	port_no = atoi(argv[2]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_no);
	bcopy((char *) host->h_addr, (char *) &server_addr.sin_addr.s_addr, host->h_length);
	connect_status = connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
	if(connect_status < 0) {
		error("Error: Socket connection failure;");
		exit(1);
	}

	// Step 4: Working modules;
	while(1) {
		// memset(buffer, '/0', sizeof(buffer));
		bzero(buffer, 1024);
		status = read(sockfd, &buffer, 1024);
		if(status < 0) {
			error("Error: Socket read failed;");
			exit(1);
		}
		printf("%s", buffer);
		scanf("%d", &choice);
		status = write(sockfd, &choice, sizeof(choice));
		if(status < 0) {
			error("Error: Socket write failed;");
			exit(1);
		}

		if(choice !=5 ) {
			// Enter the value_1;
			// memset(buffer, '/0', 1024);
			bzero(buffer, 1024);
			status = read(sockfd, &buffer, sizeof(buffer));
			if(status < 0) {
				error("Error: Socket read failed;");
				exit(1);
			}
			printf("%s", buffer);
			scanf("%d", &value_1);
			status = write(sockfd, &value_1, sizeof(value_1));
			if(status < 0) {
				error("Error: Socket write failed;");
				exit(1);
			}
			printf("You selected option is %d", choice);

			// Enter the value_2;
			// memset(buffer, '/0', 1024);
			bzero(buffer, 1024);
			status = read(sockfd, &buffer, sizeof(buffer));
			if(status < 0) {
				error("Error: Socket read failed;");
				exit(1);
			}
			printf("%s", buffer);
			scanf("%d", &value_2);
			status = write(sockfd, &value_2, sizeof(int));
			if(status < 0) {
				error("Error: Socket write Failed;");
				exit(1);
			}

			// Output the result;
			status = read(sockfd, &result, sizeof(int));
			if(status < 0) {
				error("Error: Socket read Failed;");
				exit(1);
			}


		}else {
			printf("Bye...\n");
			break;
		}

	}

}