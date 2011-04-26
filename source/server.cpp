#include "../headers/includes.h"
#include "../headers/server.h"

server::server(int Port){
	port = Port;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
}

server::~server(){
	close(newsockfd);
	close(sockfd);
}

bool server::_acceptCon(){
    clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0){
          error("ERROR on accept connection");
          return 0;
    }
	return 1;
};

char* server::_readSock(){
	bzero(buffer,256);
	sockReturn = read(newsockfd,buffer,255);
	if (sockReturn < 0){
		error("ERROR reading from socket");
		return NULL;
	}
	return buffer;
};

bool server::_writeSock(char* msg){
	sockReturn = write(newsockfd,msg,18);
	if (sockReturn < 0){
		error("ERROR writing to socket");
		return 0;
	}
	return 1;
}

void server::_conHandler(int sock){
	int n;
	char buffer[256];
	char msg[32] = {"I've got your message\n\0"};
	printf("message: %s\n",_readSock());
	_writeSock(msg);
}

bool server::_fork(){
	pid = fork();
	if (pid < 0){
		error("ERROR on fork");
		return 0;
	}
	if (pid == 0){
		close(sockfd);
		_conHandler(newsockfd);
		exit(0);
	}
	else close(newsockfd);
	return 1;
}

bool server::openSocket(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
	    error("ERROR opening socket");
	    return 0;
	}
	else return 1;
}

bool server::bindAndListen(){
	char msg[32] = {"I've got your message\n\0"};
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		error("ERROR on binding");
		return 0;
	}
	
	listen(sockfd,5);
	while(true){
		_acceptCon();
		_fork();
	}
	return 1;
}
