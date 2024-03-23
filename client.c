

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


void error(const char *std)
{
	perror(std);
	exit(1);
}

int main(int argc, char *argv[])
{ 
	int sockfd , portno , number;
	struct sockaddr_in server_addr;
	struct hostent *server;
	
	char buffer[1024];
	if(argc < 3){
		fprintf(stderr , "usage %s hostname port\n" , argv[0]);
		exit(0);
	}
	
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if(sockfd < 0)
		error("Error in socket opening");
		
		server = gethostbyname(argv[1]);
		if(server == NULL){
			fprintf(stderr , "Error , no such host");
		}
	server_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr , (char *) &server_addr.sin_addr.s_addr , server->h_length);
	server_addr.sin_port = htons(portno);
	
	if(connect(sockfd , (struct sockaddr *) &server_addr , sizeof(server_addr)) < 0)
		error("Coonect to fail");
		
	while(1){
		bzero(buffer , 1024);
		fgets(buffer , 1024 , stdin);
		number = write(sockfd , buffer , strlen(buffer));
		if(number < 0)
			error("Error on Writing");
		bzero(buffer , 1024);
		number = read(sockfd , buffer , 255);
		if(number < 0)
			error("Error on reading");
		printf("Server :%s", buffer);
		
		int i = strncmp("Bye" , buffer , 3);
		if(i == 0)
		break;
	}		
	
	close(sockfd);
return 0;
}











