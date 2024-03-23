

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



void error(const char *std) 
{
	perror(std);
	exit(1);
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr , "Port number is not provided. Program terminated\n");
		exit(1);
	}
	
	int sockfd , newsockfd , portno, number; 
	char buffer[1024];
	
	struct sockaddr_in server_addr, client_addr;
	socklen_t clilen;
	
	
	// creation of the server socket
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	// the first parameter AF_NET  = network is IPv4 address
	// the second parameter SOCK_STREAM = TCP socket
	
	if( sockfd < 0)
	{
		error("Error opening Socket");
	}
	
	bzero((char *) &server_addr , sizeof(server_addr));
	// argv contain command line indexes for example argv[0] contains file name
	// argv[1] contains portnumber.
	portno = atoi(argv[1]);
	
	server_addr.sin_family = AF_INET;
	// the socket will be used for communication over the Internet Protocol(IPv4)
	
	server_addr.sin_addr.s_addr = INADDR_ANY;
	// the server socket should bind to all available network interfaces on hte host.
	
	
	server_addr.sin_port = htons(portno);
	//htons is the function to convert the port number from host byte order to network byte order.
	
	 if(bind(sockfd , (struct sockaddr *) &server_addr , sizeof(server_addr)) < 0)
	 	error("Binding Failed");
	 	// here the assigned port number failed to bind to the server's socket.
	
	
	
	listen(sockfd , 20);
	// number represents maximum limit of client who can connect to server at a time.
	
	
	clilen = sizeof(client_addr);
	
	
	newsockfd = accept(sockfd , (struct sockaddr *) &client_addr , &clilen);
	if(newsockfd < 0)
	error("Error in Acceptance");
	
	
	while(1)
	{
		bzero(buffer, 1024);
		number = read(newsockfd , buffer , 1024);
		if(number < 0)
			error("Error in reading");
		printf("Client: %s\n", buffer);
		bzero(buffer , 1024);
		fgets(buffer , 1024, stdin); 
		
		
		number = write(newsockfd , buffer , strlen(buffer));
		if(number < 0)
			error("Error on writing");
		int i = strncmp("end" , buffer , 3);
		if(i == 0)
			break;
	}
	
	close(newsockfd); 
	close(sockfd);	
	
return 0;	
}
